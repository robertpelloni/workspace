package proxy

import (
	"bytes"
	"context"
	"database/sql"
	"encoding/json"
	"fmt"
	"io"
	"log"
	"net/http"
	"net/url"
	"os"
	"strings"
	"sync"
	"time"

	"github.com/redis/go-redis/v9"
	"github.com/xeipuuv/gojsonschema"
	"github.com/robertpelloni/litellm_control_panel/internal/db"
	"github.com/robertpelloni/litellm_control_panel/internal/engine"
)

type Gateway struct {
	RankedModels     engine.RankedModels
	mu               sync.RWMutex
	Queue            chan *RequestJob
	HighPriQueue     chan *RequestJob
	MaxActive        int
	DB               *sql.DB
	PrimaryCount     int
	Cache            map[string][]byte
	cacheMu          sync.RWMutex
	Redis            *redis.Client
	Client           *http.Client
	preflightCache   map[string]preflightEntry
	preflightCacheMu sync.RWMutex
	cbRecoveryMu     sync.Mutex
}

type preflightEntry struct {
	ok        bool
	checkedAt time.Time
}

type RequestJob struct {
	Request  *http.Request
	Response chan *ProxyResponse
	Ctx      context.Context
	DBID     int64
}

type ProxyResponse struct {
	Status  int
	Body    []byte
	Header  http.Header
	Err     error
	Stream  io.ReadCloser
	ModelID string
}

func NewGateway(maxActive int, database *sql.DB) *Gateway {
	g := &Gateway{
		Queue:          make(chan *RequestJob, 1000),
		HighPriQueue:   make(chan *RequestJob, 100),
		MaxActive:      maxActive,
		DB:             database,
		PrimaryCount:   10,
		Cache:          make(map[string][]byte),
		Client:         &http.Client{Timeout: 120 * time.Second},
		preflightCache: make(map[string]preflightEntry),
	}
	go g.workerLoop()
	return g
}

func (g *Gateway) UpdateModels(models engine.RankedModels) {
	g.mu.Lock()
	defer g.mu.Unlock()
	g.RankedModels = models
}

func (g *Gateway) GetModels() engine.RankedModels {
	g.mu.RLock()
	defer g.mu.RUnlock()
	return g.RankedModels
}

func (g *Gateway) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	authKey := os.Getenv("LITELLM_MASTER_KEY")
	if authKey != "" {
		token := r.Header.Get("Authorization")
		if token != "Bearer "+authKey {
			writeJSONError(w, 401, "Unauthorized", "invalid_api_key", "auth")
			return
		}
	}

	if r.URL.Path == "/health" || r.URL.Path == "/health/liveness" {
		w.Header().Set("Content-Type", "application/json")
		w.WriteHeader(http.StatusOK)
		w.Write([]byte(`{"status":"healthy"}`))
		return
	}
	if r.URL.Path == "/health/readiness" {
		g.mu.RLock()
		count := len(g.RankedModels)
		g.mu.RUnlock()
		if count > 0 {
			w.Header().Set("Content-Type", "application/json")
			w.WriteHeader(http.StatusOK)
			w.Write([]byte(`{"status":"ready"}`))
		} else {
			w.Header().Set("Content-Type", "application/json")
			w.WriteHeader(http.StatusServiceUnavailable)
			w.Write([]byte(`{"status":"not_ready"}`))
		}
		return
	}
	if r.URL.Path == "/v1/models" {
		g.handleModels(w, r)
		return
	}
	if r.URL.Path != "/v1/chat/completions" {
		http.NotFound(w, r)
		return
	}

	body, _ := io.ReadAll(r.Body)
	r.Body = io.NopCloser(bytes.NewBuffer(body))

	schema := gojsonschema.NewStringLoader(`{"type":"object","properties":{"model":{"type":"string"},"messages":{"type":"array"}},"required":["model","messages"]}`)
	result, err := gojsonschema.Validate(schema, gojsonschema.NewBytesLoader(body))
	if err == nil && !result.Valid() {
		writeJSONError(w, 400, "Invalid OpenAI Request Schema", "invalid_request_error", "request")
		return
	}

	ctx := r.Context()
	cacheKey := string(body)

	if g.Redis != nil {
		if val, err := g.Redis.Get(ctx, cacheKey).Bytes(); err == nil {
			w.Header().Set("Content-Type", "application/json")
			w.Header().Set("X-LiteLLM-Cache", "HIT (Redis)")
			w.Write(val)
			return
		}
	} else {
		g.cacheMu.RLock()
		if cached, ok := g.Cache[cacheKey]; ok {
			g.cacheMu.RUnlock()
			w.Header().Set("Content-Type", "application/json")
			w.Header().Set("X-LiteLLM-Cache", "HIT")
			w.Write(cached)
			return
		}
		g.cacheMu.RUnlock()
	}

	dbID := int64(0)
	if g.DB != nil {
		var headers strings.Builder
		for k, v := range r.Header {
			fmt.Fprintf(&headers, "%s: %s\n", k, strings.Join(v, ","))
		}
		dbID, _ = db.EnqueueRequest(g.DB, r.Method, r.URL.String(), headers.String(), body)
	}

	job := &RequestJob{Request: r, Response: make(chan *ProxyResponse, 1), Ctx: ctx, DBID: dbID}
	queue := g.Queue
	if r.Header.Get("X-LiteLLM-Priority") == "high" {
		queue = g.HighPriQueue
	}

	select {
	case queue <- job:
	case <-ctx.Done():
		if dbID > 0 {
			db.DequeueRequest(g.DB, dbID)
		}
		return
	}

	resp := <-job.Response
	if resp.Err != nil {
		writeJSONError(w, http.StatusBadGateway, resp.Err.Error(), "server_error", "proxy")
		return
	}

	for k, v := range resp.Header {
		w.Header()[k] = v
	}
	w.WriteHeader(resp.Status)

	if resp.Stream != nil {
		defer resp.Stream.Close()
		if flusher, ok := w.(http.Flusher); ok {
			buf := make([]byte, 4096)
			for {
				n, err := resp.Stream.Read(buf)
				if n > 0 {
					w.Write(buf[:n])
					flusher.Flush()
				}
				if err != nil {
					break
				}
			}
		} else {
			io.Copy(w, resp.Stream)
		}
		g.logUsage(resp.ModelID, nil, nil)
	} else {
		w.Write(resp.Body)
	}
}

func (g *Gateway) workerLoop() {
	if g.MaxActive <= 0 {
		return
	}
	sem := make(chan struct{}, g.MaxActive)
	for {
		var job *RequestJob
		select {
		case job = <-g.HighPriQueue:
		default:
			select {
			case job = <-g.HighPriQueue:
			case job = <-g.Queue:
			}
		}
		sem <- struct{}{}
		go func(j *RequestJob) {
			defer func() { <-sem }()
			g.processJob(j)
		}(job)
	}
}

// processJob: GUARANTEED DELIVERY routing engine
func (g *Gateway) processJob(job *RequestJob) {
	g.mu.RLock()
	allModels := g.RankedModels
	g.mu.RUnlock()

	if len(allModels) == 0 {
		job.Response <- &ProxyResponse{Err: fmt.Errorf("no models available")}
		return
	}

	body, err := io.ReadAll(job.Request.Body)
	if err != nil {
		job.Response <- &ProxyResponse{Err: fmt.Errorf("read body: %v", err)}
		return
	}

	hasTools, toolModels, plainModels := g.classifyRequest(body)
	models := g.filterCandidates(allModels)

	if len(models) == 0 {
		log.Println("[ROUTER] All models circuit-broken, auto-recovering...")
		g.autoRecoverCircuitBreakers()
		models = allModels
	}

	// Build ordered attempt list
	var attemptOrder []engine.ModelCandidate
	if hasTools && len(toolModels) > 0 {
		attemptOrder = append(attemptOrder, toolModels...)
		if len(attemptOrder) < 5 {
			attemptOrder = append(attemptOrder, plainModels...)
		}
	} else {
		attemptOrder = models
	}

	client := g.Client
	if client == nil {
		client = &http.Client{Timeout: 120 * time.Second}
	}

	// Phase 1: Try ALL candidates in order
	var lastErr error
	for i, model := range attemptOrder {
		sanitized := g.sanitizeRequestBody(model.Provider, body, hasTools)
		mc := &http.Client{Timeout: 60 * time.Second}
		if i < g.PrimaryCount {
			mc.Timeout = 45 * time.Second
		}
		proxyResp := g.forwardRequest(mc, job.Request, model, sanitized)
		if proxyResp.Err == nil && proxyResp.Status < 400 {
			g.onSuccess(job, model, proxyResp, body)
			return
		}
		if g.DB != nil {
			db.RecordFailure(g.DB, model.ID)
		}
		if proxyResp.Err != nil {
			lastErr = proxyResp.Err
		} else {
			lastErr = fmt.Errorf("%s: status %d", model.ID, proxyResp.Status)
		}
		if i < len(attemptOrder)-1 {
			time.Sleep(200 * time.Millisecond)
		}
	}

	// Phase 2: Auto-recover circuit breakers and retry top 5
	log.Println("[ROUTER] All models failed in phase 1, auto-recovering and retrying...")
	g.autoRecoverCircuitBreakers()
	retryModels := g.filterCandidates(allModels)
	if len(retryModels) == 0 {
		retryModels = allModels
	}
	maxRetry := minInt(len(retryModels), 5)
	for i := 0; i < maxRetry; i++ {
		model := retryModels[i]
		sanitized := g.sanitizeRequestBody(model.Provider, body, hasTools)
		proxyResp := g.forwardRequest(client, job.Request, model, sanitized)
		if proxyResp.Err == nil && proxyResp.Status < 400 {
			g.onSuccess(job, model, proxyResp, body)
			return
		}
		lastErr = proxyResp.Err
		if proxyResp.Err == nil {
			lastErr = fmt.Errorf("%s: status %d", model.ID, proxyResp.Status)
		}
	}

	if job.DBID > 0 {
		db.DequeueRequest(g.DB, job.DBID)
	}
	job.Response <- &ProxyResponse{Err: fmt.Errorf("all %d models failed: %v", len(attemptOrder)+maxRetry, lastErr)}
}

func (g *Gateway) onSuccess(job *RequestJob, model engine.ModelCandidate, proxyResp *ProxyResponse, body []byte) {
	if job.DBID > 0 {
		db.DequeueRequest(g.DB, job.DBID)
	}
	if g.DB != nil {
		db.RecordSuccess(g.DB, model.ID)
	}
	g.logUsage(model.ID, body, proxyResp.Body)
	if proxyResp.Stream == nil {
		if g.Redis != nil {
			g.Redis.Set(job.Ctx, string(body), proxyResp.Body, 1*time.Hour)
		} else {
			g.cacheMu.Lock()
			g.Cache[string(body)] = proxyResp.Body
			g.cacheMu.Unlock()
		}
	}
	job.Response <- proxyResp
}

// classifyRequest detects tool-call requests and splits models by tool compatibility
func (g *Gateway) classifyRequest(body []byte) (hasTools bool, toolModels []engine.ModelCandidate, plainModels []engine.ModelCandidate) {
	var payload map[string]interface{}
	if err := json.Unmarshal(body, &payload); err != nil {
		return false, nil, nil
	}
	if _, ok := payload["tools"]; ok {
		hasTools = true
	}
	if tc, ok := payload["tool_choice"]; ok && tc != nil && tc != "none" {
		hasTools = true
	}
	if msgs, ok := payload["messages"].([]interface{}); ok {
		for _, msg := range msgs {
			if m, ok := msg.(map[string]interface{}); ok {
				if r, ok := m["role"].(string); ok && r == "tool" {
					hasTools = true
				}
				if _, ok := m["tool_calls"]; ok {
					hasTools = true
				}
			}
		}
	}

	noTool := map[string]bool{
		"nvidia_nim": true,
		"nvidia":     true,
		"cerebras":   true,
		"cloudflare": true,
		"deepinfra":  true,
	}
	g.mu.RLock()
	for _, m := range g.RankedModels {
		if noTool[m.Provider] {
			plainModels = append(plainModels, m)
		} else {
			toolModels = append(toolModels, m)
		}
	}
	g.mu.RUnlock()
	return
}

// filterCandidates removes circuit-broken models
func (g *Gateway) filterCandidates(all engine.RankedModels) []engine.ModelCandidate {
	if g.DB == nil {
		return all
	}
	blocked, _ := db.GetCircuitBreakerList(g.DB)
	if len(blocked) == 0 {
		return all
	}
	var valid []engine.ModelCandidate
	for _, m := range all {
		if !blocked[m.ID] && !blocked[m.Provider+"/"+m.ID] {
			valid = append(valid, m)
		}
	}
	if len(valid) < len(all) {
		log.Printf("[ROUTER] Circuit breaker filtered %d/%d models", len(all)-len(valid), len(all))
	}
	return valid
}

// autoRecoverCircuitBreakers resets all circuit-broken models for a second chance
func (g *Gateway) autoRecoverCircuitBreakers() {
	if g.DB == nil {
		return
	}
	g.cbRecoveryMu.Lock()
	defer g.cbRecoveryMu.Unlock()
	g.DB.Exec("UPDATE model_history SET failure_count = 0, retry_after = NULL WHERE failure_count >= 3")
	log.Println("[ROUTER] Circuit breakers auto-recovered")
}

// sanitizeRequestBody cleans request body for provider compatibility:
// - ALWAYS strips reasoning_content from messages (DeepSeek adds this, breaks other providers)
// - ALWAYS strips unsupported params per provider
// - For no-tool providers: strips tools/tool_choice/tool messages/tool_calls
// - Sets null assistant content to ""
// - Sets default max_tokens if not provided
func (g *Gateway) sanitizeRequestBody(provider string, body []byte, hasTools bool) []byte {
	noTool := map[string]bool{
		"nvidia_nim": true,
		"nvidia":     true,
		"cerebras":   true,
		"cloudflare": true,
		"deepinfra":  true,
	}
	var payload map[string]interface{}
	if err := json.Unmarshal(body, &payload); err != nil {
		return body
	}

	// Clean messages: strip reasoning_content, fix null content, handle tool fields
	if msgs, ok := payload["messages"].([]interface{}); ok {
		var clean []interface{}
		for _, msg := range msgs {
			m, ok := msg.(map[string]interface{})
			if !ok {
				clean = append(clean, msg)
				continue
			}
			// ALWAYS strip reasoning_content - DeepSeek models add this and
			// other providers reject it with "Extra inputs are not permitted"
			delete(m, "reasoning_content")

			// Fix null assistant content -> ""
			if r, ok := m["role"].(string); ok && r == "assistant" {
				if content, exists := m["content"]; exists && content == nil {
					m["content"] = ""
				}
			}

			// For no-tool providers: strip tool-related fields
			if noTool[provider] && hasTools {
				if r, ok := m["role"].(string); ok && r == "tool" {
					continue // skip tool result messages entirely
				}
				delete(m, "tool_calls")
				delete(m, "tool_call_id")
			}
			clean = append(clean, m)
		}
		payload["messages"] = clean
	}

	// For no-tool providers: strip tools and tool_choice
	if noTool[provider] && hasTools {
		delete(payload, "tools")
		delete(payload, "tool_choice")
	}

	// Strip unsupported params per provider
	switch provider {
	case "mistral", "codestral":
		delete(payload, "frequency_penalty")
		delete(payload, "presence_penalty")
	case "nvidia", "nvidia_nim", "cerebras":
		delete(payload, "frequency_penalty")
		delete(payload, "presence_penalty")
		delete(payload, "logit_bias")
		delete(payload, "logprobs")
		delete(payload, "top_logprobs")
	case "cohere":
		delete(payload, "logit_bias")
		delete(payload, "logprobs")
	case "groq":
		delete(payload, "logit_bias")
		delete(payload, "logprobs")
		delete(payload, "top_logprobs")
	}

	// Set default max_tokens if not provided
	if _, ok := payload["max_tokens"]; !ok {
		payload["max_tokens"] = 4096
	}

	if out, err := json.Marshal(payload); err == nil {
		return out
	}
	return body
}

// PreFlightCheck with 5-minute cache
func (g *Gateway) PreFlightCheck(model engine.ModelCandidate) bool {
	targetURL := g.getProviderURL(model.ID, model.Provider)
	if targetURL == "" {
		return false
	}
	parsed, err := url.Parse(targetURL)
	if err != nil {
		return false
	}
	host := parsed.Host

	g.preflightCacheMu.RLock()
	if e, ok := g.preflightCache[host]; ok && time.Since(e.checkedAt) < 5*time.Minute {
		g.preflightCacheMu.RUnlock()
		return e.ok
	}
	g.preflightCacheMu.RUnlock()

	client := &http.Client{Timeout: 3 * time.Second}
	resp, err := client.Head(parsed.Scheme + "://" + host)
	ok := err == nil
	if ok {
		resp.Body.Close()
	}
	g.preflightCacheMu.Lock()
	g.preflightCache[host] = preflightEntry{ok: ok, checkedAt: time.Now()}
	g.preflightCacheMu.Unlock()
	return ok
}

// forwardRequest sends the request to a specific provider
func (g *Gateway) forwardRequest(client *http.Client, r *http.Request, model engine.ModelCandidate, body []byte) *ProxyResponse {
	var payload map[string]interface{}
	if err := json.Unmarshal(body, &payload); err != nil {
		return &ProxyResponse{Err: fmt.Errorf("unmarshal: %v", err)}
	}

	// Set model ID, stripping provider prefixes where needed
	modelForAPI := model.ID
	if model.Provider == "nvidia_nim" {
		modelForAPI = strings.TrimPrefix(modelForAPI, "nvidia_nim/")
	}
	payload["model"] = modelForAPI

	stream, _ := payload["stream"].(bool)
	newBody, _ := json.Marshal(payload)
	if mapped, err := TransformRequestBody(model.Provider, newBody); err == nil {
		newBody = mapped
	}

	targetURL := g.getProviderURL(model.ID, model.Provider)
	if targetURL == "" {
		return &ProxyResponse{Err: fmt.Errorf("unsupported provider: %s", model.Provider)}
	}

	req, err := http.NewRequestWithContext(r.Context(), "POST", targetURL, bytes.NewBuffer(newBody))
	if err != nil {
		return &ProxyResponse{Err: err}
	}
	g.transformRequest(req, model.Provider)

	resp, err := client.Do(req)
	if err != nil {
		return &ProxyResponse{Err: fmt.Errorf("%s: %v", model.Provider, err)}
	}

	if stream && resp.StatusCode == http.StatusOK {
		return &ProxyResponse{
			Status:  resp.StatusCode,
			Header:  resp.Header,
			Stream:  resp.Body,
			ModelID: model.ID,
		}
	}
	defer resp.Body.Close()

	respBody, _ := io.ReadAll(resp.Body)

	if !stream && resp.StatusCode == 200 {
		if mapped, err := TransformResponseBody(model.Provider, respBody); err == nil {
			respBody = mapped
		}
		var rd map[string]interface{}
		if json.Unmarshal(respBody, &rd) == nil {
			// Strip reasoning_content from response messages too
			if choices, ok := rd["choices"].([]interface{}); ok {
				for _, c := range choices {
					if choice, ok := c.(map[string]interface{}); ok {
						if msg, ok := choice["message"].(map[string]interface{}); ok {
							delete(msg, "reasoning_content")
						}
					}
				}
				rd["choices"] = choices
			}
			// Add usage if missing
			if _, ok := rd["usage"]; !ok {
				rd["usage"] = map[string]int{
					"prompt_tokens":     len(body) / 4,
					"completion_tokens": len(respBody) / 4,
					"total_tokens":      (len(body) + len(respBody)) / 4,
				}
			}
			// Set model name in response
			rd["model"] = model.ID
			respBody, _ = json.Marshal(rd)
		}
	}

	return &ProxyResponse{
		Status: resp.StatusCode,
		Body:   respBody,
		Header: resp.Header,
	}
}

// Complete provider URL mapping
func (g *Gateway) getProviderURL(modelID, provider string) string {
	switch provider {
	case "openrouter":
		return "https://openrouter.ai/api/v1/chat/completions"
	case "groq":
		return "https://api.groq.com/openai/v1/chat/completions"
	case "github":
		return "https://models.inference.ai.azure.com/chat/completions"
	case "deepinfra":
		return "https://api.deepinfra.com/v1/openai/chat/completions"
	case "cerebras":
		return "https://api.cerebras.ai/v1/chat/completions"
	case "nvidia", "nvidia_nim":
		return "https://integrate.api.nvidia.com/v1/chat/completions"
	case "huggingface":
		return "https://api-inference.huggingface.co/models/" + modelID + "/v1/chat/completions"
	case "mistral":
		return "https://api.mistral.ai/v1/chat/completions"
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
		aid := os.Getenv("CLOUDFLARE_ACCOUNT_ID")
		if aid == "" {
			return ""
		}
		return "https://api.cloudflare.com/client/v4/accounts/" + aid + "/ai/v1/chat/completions"
	case "opencode_zen":
		return "https://opencode.ai/zen/v1/chat/completions"
	case "ollama":
		return "http://localhost:11434/v1/chat/completions"
	case "lm_studio":
		return "http://localhost:1234/v1/chat/completions"
	case "anthropic":
		return "https://api.anthropic.com/v1/messages"
	case "gemini":
		return "https://generativelanguage.googleapis.com/v1beta/models/" + modelID + ":streamGenerateContent"
	}
	return ""
}

// API key resolution for all providers (with NVIDIA fallback)
func (g *Gateway) getAPIKey(provider string) string {
	switch provider {
	case "openrouter":
		return os.Getenv("OPENROUTER_API_KEY")
	case "groq":
		return os.Getenv("GROQ_API_KEY")
	case "github":
		return os.Getenv("GITHUB_TOKEN")
	case "deepinfra":
		return os.Getenv("DEEPINFRA_API_KEY")
	case "cerebras":
		return os.Getenv("CEREBRAS_API_KEY")
	case "huggingface":
		return os.Getenv("HUGGINGFACE_API_KEY")
	case "nvidia", "nvidia_nim":
		key := os.Getenv("NVIDIA_NIM_API_KEY")
		if key == "" {
			key = os.Getenv("NVIDIA_API_KEY")
		}
		return key
	case "mistral":
		return os.Getenv("MISTRAL_API_KEY")
	case "codestral":
		return os.Getenv("CODESTRAL_API_KEY")
	case "cohere":
		return os.Getenv("COHERE_API_KEY")
	case "sambanova":
		return os.Getenv("SAMBANOVA_API_KEY")
	case "fireworks":
		return os.Getenv("FIREWORKS_API_KEY")
	case "hyperbolic":
		return os.Getenv("HYPERBOLIC_API_KEY")
	case "cloudflare":
		return os.Getenv("CLOUDFLARE_API_KEY")
	case "opencode_zen":
		return os.Getenv("OPENCODE_ZEN_API_KEY")
	case "anthropic":
		return os.Getenv("ANTHROPIC_API_KEY")
	case "gemini":
		return os.Getenv("GEMINI_API_KEY")
	}
	return ""
}

func (g *Gateway) transformRequest(req *http.Request, provider string) {
	req.Header.Set("Content-Type", "application/json")
	apiKey := g.getAPIKey(provider)
	if apiKey == "" {
		return
	}
	if provider == "anthropic" {
		req.Header.Set("x-api-key", apiKey)
		req.Header.Set("anthropic-version", "2023-06-01")
	} else {
		req.Header.Set("Authorization", "Bearer "+apiKey)
	}
}

func (g *Gateway) handleModels(w http.ResponseWriter, r *http.Request) {
	type ME struct {
		ID      string `json:"id"`
		Object  string `json:"object"`
		Created int64  `json:"created"`
		OwnedBy string `json:"owned_by"`
	}
	resp := struct {
		Object string `json:"object"`
		Data   []ME   `json:"data"`
	}{
		Object: "list",
		Data: []ME{
			{"free-llm", "model", time.Now().Unix(), "litellm-cp"},
			{"free-llm-fallback", "model", time.Now().Unix(), "litellm-cp"},
			{"free-llm-plain", "model", time.Now().Unix(), "litellm-cp"},
		},
	}
	for _, m := range g.GetModels() {
		resp.Data = append(resp.Data, ME{m.ID, "model", time.Now().Unix(), m.Provider})
	}
	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(resp)
}

func (g *Gateway) RestoreQueue() {
	if g.DB == nil {
		return
	}
	pending, err := db.GetPendingRequests(g.DB)
	if err != nil || len(pending) == 0 {
		return
	}
	log.Printf("Restoring %d pending requests...", len(pending))
	for _, p := range pending {
		req, _ := http.NewRequest(p.Method, p.URL, bytes.NewBuffer(p.Body))
		job := &RequestJob{
			Request:  req,
			Response: make(chan *ProxyResponse, 1),
			Ctx:      context.Background(),
			DBID:     p.ID,
		}
		select {
		case g.Queue <- job:
		default:
		}
	}
}

func (g *Gateway) logUsage(modelID string, reqBody, respBody []byte) {
	if g.DB == nil {
		return
	}
	pt, ct := len(reqBody)/4, len(respBody)/4
	if respBody != nil {
		var r struct {
			Usage struct {
				P int `json:"prompt_tokens"`
				C int `json:"completion_tokens"`
			} `json:"usage"`
		}
		if json.Unmarshal(respBody, &r) == nil && r.Usage.P > 0 {
			pt, ct = r.Usage.P, r.Usage.C
		}
	} else {
		pt, ct = 0, 0
	}
	db.LogUsage(g.DB, modelID, pt, ct)
}

// writeJSONError sends an OpenAI-compatible error response
func writeJSONError(w http.ResponseWriter, status int, message, code, param string) {
	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(status)
	json.NewEncoder(w).Encode(map[string]interface{}{
		"error": map[string]interface{}{
			"message": message,
			"type":    "server_error",
			"param":   param,
			"code":    code,
		},
	})
}

func minInt(a, b int) int {
	if a < b {
		return a
	}
	return b
}
