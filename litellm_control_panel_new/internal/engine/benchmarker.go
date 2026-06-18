package engine

import (
	"bytes"
	"context"
	"database/sql"
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"regexp"
	"sort"
	"strconv"
	"os"
	"strings"
	"sync"
	"time"

	"github.com/robertpelloni/freellm/internal/db"
)

var SizePattern = regexp.MustCompile(`(\d+)[bB]`)

type ModelCandidate struct {
	ID              string    `json:"id"`
	Provider        string    `json:"provider"`
	Parameters      int       `json:"parameters"`
	ContextLength   int       `json:"context_length"`
	Latency         float64   `json:"latency"`
	Score           float64   `json:"score"`
	LastBenchmark   time.Time `json:"last_benchmark"`
	PromptPrice     float64   `json:"prompt_price"`
	CompletionPrice float64   `json:"completion_price"`
}

type Benchmarker struct {
	APIKeys    map[string]string
	BaseURLs   map[string]string
	MinParams  int
	Weights    map[string]float64
	Client     *http.Client
	smartCache map[string]ModelCandidate
	cacheMu    sync.RWMutex
	Logger     *EventLogger
}

func NewBenchmarker(apiKeys map[string]string, minParams int, logger *EventLogger) *Benchmarker {
	return &Benchmarker{
		APIKeys:  apiKeys,
		BaseURLs: make(map[string]string),
		Weights: map[string]float64{
			"size":    0.6,
			"context": 0.2,
			"latency": 0.2,
		},
		MinParams:  minParams,
		Client:     &http.Client{Timeout: 30 * time.Second},
		smartCache: make(map[string]ModelCandidate),
		Logger:     logger,
	}
}

func (b *Benchmarker) log(msg string) {
	if b.Logger != nil {
		b.Logger.Log(msg)
	} else {
		fmt.Println(msg)
	}
}

func (b *Benchmarker) ExtractParameters(modelID, name, description string) int {
	for _, text := range []string{modelID, name, description} {
		match := SizePattern.FindStringSubmatch(text)
		if len(match) > 1 {
			params, _ := strconv.Atoi(match[1])
			return params
		}
	}
	return 0
}

func (b *Benchmarker) CalculateScore(params int, latency float64, contextLength int) float64 {
	sizeScore := (float64(min(params, 405)) / 100.0) * b.Weights["size"]
	contextScore := (float64(min(contextLength, 128000)) / 128000.0) * b.Weights["context"]
	latencyPenalty := minF(latency, 5.0) * b.Weights["latency"]
	return sizeScore + contextScore - latencyPenalty
}

func (b *Benchmarker) FetchModels(ctx context.Context, database *sql.DB) []ModelCandidate {
	b.log("Starting model discovery...")
	var candidates []ModelCandidate
	var mu sync.Mutex
	var wg sync.WaitGroup

	providers := []string{"openrouter", "groq", "deepinfra", "cerebras", "github", "nvidia", "nvidia_nim", "ollama", "lm_studio", "mistral", "codestral", "cohere", "sambanova", "fireworks", "hyperbolic", "cloudflare", "opencode_zen"}

	for _, p := range providers {
		if IsDeadProvider(p) { continue }
		// Check if provider enabled in DB
		if database != nil {
			var enabled int
			err := database.QueryRow("SELECT is_free_provider FROM providers WHERE provider_name = ?", p).Scan(&enabled)
			if err != nil {
				enabled = 1 // No row = not in DB yet, treat as enabled
			}
			if enabled == 0 { continue }
		}

		wg.Add(1)
		go func(provider string) {
			defer wg.Done()
			models := b.fetchProviderModels(ctx, provider)
			mu.Lock()
			candidates = append(candidates, models...)
			mu.Unlock()
		}(p)
	}

	wg.Wait()
	candidates = b.FilterCandidates(candidates, database)
	existingIDs := make(map[string]bool)
	for _, c := range candidates { existingIDs[c.ID] = true }
	known := b.ForceInjectKnownModels(existingIDs)
	candidates = append(candidates, known...)
	return candidates
}

func (b *Benchmarker) fetchProviderModels(ctx context.Context, provider string) []ModelCandidate {
		if provider == "ollama" {
		return b.fetchOllamaModels(ctx)
	}
	if provider == "huggingface" {
		return b.fetchHuggingFaceModels(ctx)
	}

	url := b.getModelsURL(provider)
	if url == "" {
				return nil
	}

	req, err := http.NewRequestWithContext(ctx, "GET", url, nil)
	if err != nil {
		return nil
	}
	if apiKey := b.APIKeys[provider]; apiKey != "" {
		req.Header.Set("Authorization", "Bearer "+apiKey)
	}

	resp, err := b.Client.Do(req)
	if err != nil {
				return nil
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
				return nil
	}

	var data struct {
		Data []map[string]interface{} `json:"data"`
	}
	json.NewDecoder(resp.Body).Decode(&data)

	var models []ModelCandidate
	for _, m := range data.Data {
		id, _ := m["id"].(string)
		if id == "" {
			continue
		}

		params := b.ExtractParameters(id, "", "")
		if params < b.MinParams && params != 0 {
			continue
		}

		if IsExcluded(id) {
			continue
		}

		ctxLength := 4096
		if spec, ok := LookupKnownModel(id); ok {
			params = spec.Params
			ctxLength = spec.Ctx
		}

		promptPrice, _ := m["prompt_price"].(float64)
		completionPrice, _ := m["completion_price"].(float64)
		if pricing, ok := m["pricing"].(map[string]interface{}); ok {
			promptPrice, _ = pricing["prompt"].(float64)
			completionPrice, _ = pricing["completion"].(float64)
		}

		// Skip paid models from providers that list pricing (e.g. OpenRouter)
			// Free models have both prices = 0; paid models have non-zero prices.
			if promptPrice > 0 || completionPrice > 0 {
				continue
			}
			models = append(models, ModelCandidate{
			ID:              id,
			Provider:        provider,
			Parameters:      params,
			ContextLength:   ctxLength,
			PromptPrice:     promptPrice,
			CompletionPrice: completionPrice,
		})
	}
	return models
}

func (b *Benchmarker) MeasureLatency(ctx context.Context, modelID, provider string) (float64, error) {
	url := b.getCompletionsURL(provider)
	if url == "" {
		return 0, fmt.Errorf("unsupported provider: %s", provider)
	}

	apiKey := b.APIKeys[provider]
	// NVIDIA uses same key
	if provider == "nvidia" && apiKey == "" {
	if provider == "nvidia_nim" {
		if apiKey == "" {
			apiKey = b.APIKeys["nvidia"]
		}
		// Strip nvidia_nim/ prefix for API call
		modelID = strings.TrimPrefix(modelID, "nvidia_nim/")
	}
		apiKey = b.APIKeys["nvidia_nim"]
	}

	payload := map[string]interface{}{
		"model":    modelID,
		"messages": []map[string]string{{"role": "user", "content": "hi"}},
		"max_tokens": 1,
		"stream":   true,
	}

	body, _ := json.Marshal(payload)
	req, err := http.NewRequestWithContext(ctx, "POST", url, bytes.NewBuffer(body))
	if err != nil {
		return 0, err
	}

	req.Header.Set("Content-Type", "application/json")
	if apiKey != "" {
		req.Header.Set("Authorization", "Bearer "+apiKey)
	}

	startTime := time.Now()
	resp, err := b.Client.Do(req)
	if err != nil {
		return 0, err
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
		respBody, _ := io.ReadAll(resp.Body)
		return 0, fmt.Errorf("error %d: %s", resp.StatusCode, string(respBody))
	}

	// Wait for the first line of streaming response
	reader := io.Reader(resp.Body)
	buf := make([]byte, 1024)
	_, err = reader.Read(buf)
	if err != nil && err != io.EOF {
		return 0, err
	}

	ttft := time.Since(startTime).Seconds()
	return ttft, nil
}

func (b *Benchmarker) fetchHuggingFaceModels(ctx context.Context) []ModelCandidate {
	url := "https://huggingface.co/api/models?filter=text-generation&sort=trendingScore&limit=50"
	resp, err := b.Client.Get(url)
	if err != nil { return nil }
	defer resp.Body.Close()

	var data []map[string]interface{}
	json.NewDecoder(resp.Body).Decode(&data)

	var candidates []ModelCandidate
	for _, m := range data {
		id, _ := m["id"].(string)
		if id == "" { continue }

		params := b.ExtractParameters(id, "", "")
		if params < b.MinParams && params != 0 { continue }
		if IsExcluded(id) { continue }

		candidates = append(candidates, ModelCandidate{
			ID:         id,
			Provider:   "huggingface",
			Parameters: params,
		})
	}
	return candidates
}

func (b *Benchmarker) fetchOllamaModels(ctx context.Context) []ModelCandidate {
	url := b.BaseURLs["ollama"]
	if url == "" {
		url = "http://localhost:11434/api/tags"
	} else if !strings.HasSuffix(url, "/api/tags") {
		url += "/api/tags"
	}

	resp, err := b.Client.Get(url)
	if err != nil {
		return nil
	}
	defer resp.Body.Close()

	var data struct {
		Models []struct {
			Name string `json:"name"`
		} `json:"models"`
	}
	json.NewDecoder(resp.Body).Decode(&data)

	var candidates []ModelCandidate
	for _, m := range data.Models {
		params := b.ExtractParameters(m.Name, "", "")
		candidates = append(candidates, ModelCandidate{
			ID:         m.Name,
			Provider:   "ollama",
			Parameters: params,
		})
	}
	return candidates
}

func (b *Benchmarker) getModelsURL(provider string) string {
	if url, ok := b.BaseURLs[provider+"_models"]; ok && url != "" {
		return url
	}
	base := b.BaseURLs[provider]
	switch provider {
	case "openrouter":
		if base == "" { return "https://openrouter.ai/api/v1/models" }
		return base + "/models"
	case "groq":
		if base == "" { return "https://api.groq.com/openai/v1/models" }
		return base + "/models"
	case "deepinfra":
		if base == "" { return "https://api.deepinfra.com/v1/openai/models" }
		return base + "/openai/models"
	case "cerebras":
		if base == "" { return "https://api.cerebras.ai/v1/models" }
		return base + "/models"
	case "github":
		if base == "" { return "https://models.inference.ai.azure.com/models" }
		return base
	case "nvidia", "nvidia_nim":
		if base == "" { return "https://integrate.api.nvidia.com/v1/models" }
		return base + "/models"
	case "mistral":
		if base == "" { return "https://api.mistral.ai/v1/models" }
		return base + "/models"
	case "anthropic":
		return "https://api.anthropic.com/v1/models"
	case "opencode_zen":
		return "https://opencode.ai/zen/v1/models"
	case "codestral":
		if base == "" { return "https://codestral.mistral.ai/v1/models" }
		return base + "/models"
	case "cohere":
		return "https://api.cohere.ai/v1/models"
	case "sambanova":
		if base == "" { return "https://api.sambanova.ai/v1/models" }
		return base + "/models"
	case "fireworks":
		if base == "" { return "https://api.fireworks.ai/inference/v1/models" }
		return base + "/models"
	case "hyperbolic":
		if base == "" { return "https://api.hyperbolic.xyz/v1/models" }
		return base + "/models"
	case "cloudflare":
		return "https://api.cloudflare.com/client/v4/accounts/" + os.Getenv("CLOUDFLARE_ACCOUNT_ID") + "/ai/v1/models"
	case "bedrock":
		return "https://bedrock-runtime.us-east-1.amazonaws.com/model/list" // Simplified
	case "vertex_ai":
		return "https://us-central1-aiplatform.googleapis.com/v1/models"
	case "lm_studio":
		if base == "" { return "http://localhost:1234/v1/models" }
		return base + "/v1/models"
	}
	return ""
}

func (b *Benchmarker) getCompletionsURL(provider string) string {
	if url, ok := b.BaseURLs[provider+"_completions"]; ok && url != "" {
		return url
	}
	base := b.BaseURLs[provider]
	switch provider {
	case "openrouter":
		if base == "" { return "https://openrouter.ai/api/v1/chat/completions" }
		return base + "/chat/completions"
	case "groq":
		if base == "" { return "https://api.groq.com/openai/v1/chat/completions" }
		return base + "/chat/completions"
	case "deepinfra":
		if base == "" { return "https://api.deepinfra.com/v1/openai/chat/completions" }
		return base + "/openai/chat/completions"
	case "cerebras":
		if base == "" { return "https://api.cerebras.ai/v1/chat/completions" }
		return base + "/chat/completions"
	case "github":
		if base == "" { return "https://models.inference.ai.azure.com/chat/completions" }
		return base + "/chat/completions"
	case "nvidia", "nvidia_nim":
		if base == "" { return "https://integrate.api.nvidia.com/v1/chat/completions" }
		return base + "/chat/completions"
	case "gemini":
		if base == "" { return "https://generativelanguage.googleapis.com/v1beta/models" }
		return base
	case "anthropic":
		return "https://api.anthropic.com/v1/messages"
	case "opencode_zen":
		return "https://opencode.ai/zen/v1/chat/completions"
	case "codestral":
		return "https://codestral.mistral.ai/v1/chat/completions"
	case "cohere":
		return "https://api.cohere.ai/v2/chat"
	case "sambanova":
		return "https://api.sambanova.ai/v1/chat/completions"
	case "fireworks":
		return "https://api.fireworks.ai/inference/v1/chat/completions"
	case "hyperbolic":
		return "https://api.hyperbolic.xyz/v1/chat/completions"
	case "cloudflare":
		return "https://api.cloudflare.com/client/v4/accounts/" + os.Getenv("CLOUDFLARE_ACCOUNT_ID") + "/ai/v1/chat/completions"
	case "bedrock":
		return "https://bedrock-runtime.us-east-1.amazonaws.com/model/"
	case "vertex_ai":
		return "https://us-central1-aiplatform.googleapis.com/v1/projects/PROJECT_ID/locations/us-central1/publishers/google/models/"
	case "mistral":
		if base == "" { return "https://api.mistral.ai/v1/chat/completions" }
		return base + "/chat/completions"
	case "huggingface":
		// Hugging Face uses per-model endpoints
		return "https://api-inference.huggingface.co/models/"
	case "ollama":
		if base == "" { return "http://localhost:11434/v1/chat/completions" }
		return base + "/v1/chat/completions"
	case "lm_studio":
		if base == "" { return "http://localhost:1234/v1/chat/completions" }
		return base + "/v1/chat/completions"
	}
	return ""
}

func min(a, b int) int {
	if a < b { return a }
	return b
}

func minF(a, b float64) float64 {
	if a < b { return a }
	return b
}

type RankedModels []ModelCandidate


// FilterCandidates applies the full filtering pipeline.
func (b *Benchmarker) FilterCandidates(candidates []ModelCandidate, database *sql.DB) []ModelCandidate {
	var valid []ModelCandidate
	now := time.Now()
	for _, m := range candidates {
		if IsDeadModel(m.ID) || IsDeadModel(fmt.Sprintf("%s/%s", m.Provider, m.ID)) { continue }
		if IsDeadProvider(m.Provider) { continue }
		if IsExcluded(m.ID) { continue }
		if database != nil {
			var isBlacklisted bool
			var failureCount int
			var retryAfter sql.NullTime
			var manuallySkipped bool
			var skipExpiry sql.NullTime
			err := database.QueryRow("SELECT is_blacklisted, failure_count, retry_after, manually_skipped, skip_expiry FROM model_history WHERE model_id = ?", m.ID).
				Scan(&isBlacklisted, &failureCount, &retryAfter, &manuallySkipped, &skipExpiry)
			if err == nil {
				if isBlacklisted { continue }
				if manuallySkipped && skipExpiry.Valid && now.Before(skipExpiry.Time) { continue }
				if failureCount >= 3 && retryAfter.Valid && now.Before(retryAfter.Time) { continue }
			}
		}
		valid = append(valid, m)
	}
	b.log(fmt.Sprintf("Candidate filter: %d raw - %d valid", len(candidates), len(valid)))
	return valid
}

// FinalBenchmarkFilter catches models that bypass the main filter.
func (b *Benchmarker) FinalBenchmarkFilter(candidates []ModelCandidate) []ModelCandidate {
	var valid []ModelCandidate
	for _, m := range candidates {
		if IsDeadModel(m.ID) { continue }
		if IsExcluded(m.ID) { continue }
		valid = append(valid, m)
	}
	return valid
}

// ForceInjectKnownModels adds known good models not found in provider fetches.
func (b *Benchmarker) ForceInjectKnownModels(existingIDs map[string]bool) []ModelCandidate {
	var known []ModelCandidate
	for modelID, spec := range KnownModels {
		bareID := modelID
		if idx := strings.Index(modelID, "/"); idx >= 0 { bareID = modelID[idx+1:] }
		if existingIDs[bareID] || existingIDs[modelID] { continue }
		if IsDeadProvider(spec.Provider) { continue }
		if IsExcluded(modelID) || IsExcluded(bareID) { continue }
		if IsDeadModel(modelID) || IsDeadModel(bareID) { continue }
		effectiveProv := spec.Provider
		if effectiveProv == "nvidia_nim" {
			if _, ok := b.APIKeys["nvidia_nim"]; !ok {
				if _, ok2 := b.APIKeys["nvidia"]; ok2 { effectiveProv = "nvidia" } else { continue }
			}
		} else {
			if _, ok := b.APIKeys[effectiveProv]; !ok { continue }
		}
		known = append(known, ModelCandidate{ID: bareID, Provider: spec.Provider, Parameters: spec.Params, ContextLength: spec.Ctx})
		existingIDs[bareID] = true
	}
	if len(known) > 0 { b.log(fmt.Sprintf("Force-including %d known good models", len(known))) }
	return known
}

// QuickPulse re-benchmarks the top N models (Tier 1, every 10 min).
func (b *Benchmarker) QuickPulse(ctx context.Context, ranked RankedModels, topN int, database *sql.DB) (RankedModels, bool) {
	if len(ranked) == 0 { return ranked, false }
	if topN > len(ranked) { topN = len(ranked) }
	b.log(fmt.Sprintf("Quick pulse: re-checking top %d models...", topN))
	oldOrder := make([]string, topN)
	for i, m := range ranked[:topN] { oldOrder[i] = m.ID }
	sem := make(chan struct{}, 3)
	var wg sync.WaitGroup
	type result struct{ idx int; lat float64; err error }
	results := make(chan result, topN)
	for i, m := range ranked[:topN] {
		wg.Add(1)
		go func(idx int, m ModelCandidate) {
			defer wg.Done()
			sem <- struct{}{}
			defer func() { <-sem }()
			lat, err := b.MeasureLatency(ctx, m.ID, m.Provider)
			results <- result{idx, lat, err}
		}(i, m)
	}
	go func() { wg.Wait(); close(results) }()
	updated := false
	for r := range results {
		m := &ranked[r.idx]
		if r.err == nil {
			oldScore := m.Score
			newScore := b.CalculateScore(m.Parameters, r.lat, m.ContextLength)
			m.Latency = r.lat
			m.Score = newScore
			b.log(fmt.Sprintf("  Pulse: %s (%s): %.3fs score=%.1f", m.ID, m.Provider, r.lat, newScore))
			if absF(newScore-oldScore) > 0.3 { updated = true }
			RecordProbe(database, m.ID, m.Provider, r.lat, true, newScore, m.ContextLength, m.Parameters)
		} else {
			m.Latency = 99.0
			m.Score = -10.0
			updated = true
			b.log(fmt.Sprintf("  Pulse: %s (%s): FAILED", m.ID, m.Provider))
			RecordProbe(database, m.ID, m.Provider, 0, false, 0, m.ContextLength, m.Parameters)
		}
	}
	sort.Slice(ranked, func(i, j int) bool { return ranked[i].Score > ranked[j].Score })
	newOrder := make([]string, topN)
	for i, m := range ranked[:topN] { newOrder[i] = m.ID }
	for i := range oldOrder {
		if oldOrder[i] != newOrder[i] { updated = true; break }
	}
	if updated {
		b.log("  Pulse: rankings changed")
	} else {
		b.log("  Pulse: no changes")
	}
	return ranked, updated
}

// RecordProbe writes a probe result to the database.
func RecordProbe(database *sql.DB, modelID, provider string, latency float64, success bool, score float64, ctxLen, params int) {
	if database == nil { return }
	database.Exec("INSERT INTO probe_history (model_id, provider_name, timestamp, latency, success, score, context_length, parameters) VALUES (?, ?, ?, ?, ?, ?, ?, ?)",
		modelID, provider, time.Now(), latency, success, score, ctxLen, params)
}

func absF(a float64) float64 {
	if a < 0 { return -a }
	return a
}

func (b *Benchmarker) RunBenchmark(ctx context.Context, candidates []ModelCandidate, dbConn *sql.DB) RankedModels {
	candidates = b.FinalBenchmarkFilter(candidates)
	b.log(fmt.Sprintf("Benchmarking %d candidates...", len(candidates)))
	var wg sync.WaitGroup
	results := make(chan ModelCandidate, len(candidates))
	semaphore := make(chan struct{}, 5) // Limit concurrency

	for _, m := range candidates {
		// Smart Cache: Reuse local results for 15m
		if m.Provider == "ollama" || m.Provider == "lm_studio" {
			b.cacheMu.RLock()
			cached, ok := b.smartCache[m.ID]
			b.cacheMu.RUnlock()
			if ok && time.Since(cached.LastBenchmark) < 15*time.Minute {
				results <- cached
				continue
			}
		}

		wg.Add(1)
		go func(m ModelCandidate) {
			defer wg.Done()
			semaphore <- struct{}{}
			defer func() { <-semaphore }()

			lat, err := b.MeasureLatency(ctx, m.ID, m.Provider)
			success := err == nil
			errMsg := ""
			if err != nil {
				errMsg = err.Error()
				fmt.Printf("Benchmark failed for %s/%s: %v\n", m.Provider, m.ID, err)
			}

			if success {
				m.Latency = lat
				m.Score = b.CalculateScore(m.Parameters, lat, m.ContextLength)
				m.LastBenchmark = time.Now()

				if m.Provider == "ollama" || m.Provider == "lm_studio" {
					b.cacheMu.Lock()
					b.smartCache[m.ID] = m
					b.cacheMu.Unlock()
				}
				results <- m
			}

			if dbConn != nil {
				db.RecordProbe(dbConn, m.ID, m.Provider, lat, success, errMsg, m.Score, m.ContextLength, m.Parameters)
				// Auto-blacklist models with permanent errors (401, 402, 404)
				if !success {
					db.AutoBlacklistPermanentErrors(dbConn, m.ID, m.Provider, errMsg)
				}
			}
		}(m)
	}

	go func() {
		wg.Wait()
		close(results)
	}()

	var ranked RankedModels
	for r := range results {
		ranked = append(ranked, r)
	}

	sort.Slice(ranked, func(i, j int) bool {
		return ranked[i].Score > ranked[j].Score
	})

	return ranked
}
