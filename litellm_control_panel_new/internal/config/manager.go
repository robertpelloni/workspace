package config

import (
	"log"
	"os"

	"github.com/fsnotify/fsnotify"
	"gopkg.in/yaml.v3"
	"github.com/robertpelloni/freellm/internal/engine"
)

type Config struct {
	ModelList       []ModelEntry              `yaml:"model_list"`
	RouterSettings  map[string]interface{}    `yaml:"router_settings"`
	ProxySettings   map[string]interface{}    `yaml:"proxy_settings"`
	Port            int                       `yaml:"port"`
	Providers       map[string]ProviderCfg    `yaml:"providers"`
}

type ProviderCfg struct {
	BaseURL     string `yaml:"api_base"`
	ModelsURL   string `yaml:"models_url"`
	Completions string `yaml:"completions_url"`
}

type ModelEntry struct {
	ModelName  string                 `yaml:"model_name"`
	ProxyParams map[string]interface{} `yaml:"proxy_params"`
	ModelInfo  map[string]interface{} `yaml:"model_info"`
}

func LoadConfig(path string) (*Config, error) {
	data, err := os.ReadFile(path)
	if err != nil {
		return nil, err
	}
	var cfg Config
	if err := yaml.Unmarshal(data, &cfg); err != nil {
		return nil, err
	}
	return &cfg, nil
}

func SaveConfig(path string, cfg *Config) error {
	data, err := yaml.Marshal(cfg)
	if err != nil {
		return err
	}
	return os.WriteFile(path, data, 0644)
}

func WatchConfig(path string, onReload func(*Config)) error {
	watcher, err := fsnotify.NewWatcher()
	if err != nil {
		return err
	}
	go func() {
		defer watcher.Close()
		for {
			select {
			case event, ok := <-watcher.Events:
				if !ok {
					return
				}
				if event.Op&fsnotify.Write == fsnotify.Write {
					log.Printf("Config file changed: %s, reloading...", event.Name)
					cfg, err := LoadConfig(path)
					if err == nil {
						onReload(cfg)
					} else {
						log.Printf("Reload failed: %v", err)
					}
				}
			case err, ok := <-watcher.Errors:
				if !ok {
					return
				}
				log.Printf("Watcher error: %v", err)
			}
		}
	}()
	return watcher.Add(path)
}

// ApplyRankedModels generates a FreeLLM config with primary + fallback groups.
func ApplyRankedModels(ranked []engine.ModelCandidate, cfgPath string, primaryCount int) error {
	cfg := &Config{
		Port: 4000,
		RouterSettings: map[string]interface{}{
			"routing_strategy":               "simple-shuffle",
			"cooldown_time":                  30,
			"allowed_fails":                  2,
			"num_retries":                    2,
			"timeout":                        30,
			"enable_pre_call_checks":         false,
			"ignore_cooldown_on_fallbacks":   true,
		},
		ProxySettings: map[string]interface{}{
			"drop_params":     true,
			"num_retries":     2,
			"request_timeout": 60,
			"stream_timeout":  300,
			"allowed_fails":   2,
			"cooldown_time":   30,
			"fallbacks": []map[string]interface{}{
				{"free-llm": []string{"free-llm-fallback"}},
			},
		},
	}

	primaryGroup := "free-llm"
	fallbackGroup := "free-llm-fallback"
	plainGroup := "free-llm-plain"

	// Split models into tool-compatible and non-tool groups
	noToolProviders := map[string]bool{
		"nvidia":     true,
		"nvidia_nim": true,
		"cerebras":   true,
		"cloudflare": true,
		"deepinfra":  true,
	}

	var toolCompatible []engine.ModelCandidate
	var plainOnly []engine.ModelCandidate
	for _, m := range ranked {
		if noToolProviders[m.Provider] {
			plainOnly = append(plainOnly, m)
		} else {
			toolCompatible = append(toolCompatible, m)
		}
	}
	log.Printf("Group split: %d tool-compatible, %d plain-only", len(toolCompatible), len(plainOnly))

	// Build primary group with provider diversity (max 2 per provider)
	maxPerProvider := 2
	primarySet := map[int]bool{}
	providerCount := map[string]int{}
	for i, m := range toolCompatible {
		if providerCount[m.Provider] < maxPerProvider && len(primarySet) < primaryCount {
			primarySet[i] = true
			providerCount[m.Provider]++
		}
	}

	// Assign groups: tool-compatible -> primary/fallback, plain -> plainGroup
	toolPrimaryIDs := map[string]bool{}
	for i, m := range toolCompatible {
		if primarySet[i] {
			toolPrimaryIDs[m.ID] = true
		}
	}

	for _, m := range ranked {
		var group string
		if noToolProviders[m.Provider] {
			group = plainGroup
		} else if toolPrimaryIDs[m.ID] {
			group = primaryGroup
		} else {
			group = fallbackGroup
		}

		timeout := 30
		if m.Latency > 4.0 {
			timeout = 60
		}

		upstreamModel := m.Provider + "/" + m.ID
		// Some providers use different prefix conventions
		switch m.Provider {
		case "nvidia_nim":
			upstreamModel = "nvidia_nim/" + m.ID
		case "github":
			upstreamModel = "openai/" + m.ID // GitHub uses OpenAI-compatible API
		case "codestral":
			upstreamModel = "codestral/" + m.ID
		}

		entry := ModelEntry{
			ModelName: group,
			ProxyParams: map[string]interface{}{
				"model":   upstreamModel,
				"timeout": timeout,
			},
		}

		// Add streaming timeout for slow providers
		if engine.NeedsStreamTimeout(m.Provider) || timeout > 45 {
			entry.ProxyParams["stream_timeout"] = max(timeout*5, 300)
		}

		// Add max_tokens based on context length
		maxOut := 16384
		if m.ContextLength > 0 {
			maxOut = m.ContextLength - 256
			if maxOut > 16384 {
				maxOut = 16384
			}
		}
		entry.ProxyParams["max_tokens"] = maxOut

		// Add model info
		noToolProviders := map[string]bool{
			"nvidia_nim": true,
			"nvidia":     true,
			"cerebras":   true,
			"cloudflare": true,
			"deepinfra":  true,
		}
		entry.ModelInfo = map[string]interface{}{
			"score":   m.Score,
			"latency": m.Latency,
			"params":  m.Parameters,
			"context": m.ContextLength,
		}
		if noToolProviders[m.Provider] {
			entry.ModelInfo["supports_function_calling"] = false
		}

		// For nvidia_nim/nvidia: set supported_params to exclude tools
		if m.Provider == "nvidia_nim" || m.Provider == "nvidia" {
			entry.ProxyParams["supported_params"] = []string{
				"max_tokens", "temperature", "top_p",
				"frequency_penalty", "presence_penalty",
				"stop", "n", "stream", "response_format",
				"seed", "logprobs", "top_logprobs",
			}
		}

		cfg.ModelList = append(cfg.ModelList, entry)
	}

	return SaveConfig(cfgPath, cfg)
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
