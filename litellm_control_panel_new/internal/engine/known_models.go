package engine

import "strings"

type ModelSpec struct {
    Params   int    `json:"params"`
    Ctx      int    `json:"ctx"`
    Provider string `json:"provider"`
}

var KnownModels = map[string]ModelSpec{
    "github/Meta-Llama-3.1-405B-Instruct": {Params: 405, Ctx: 128000, Provider: "github"},
    "github/gpt-4o": {Params: 175, Ctx: 128000, Provider: "github"},
    "github/gpt-4o-mini": {Params: 175, Ctx: 128000, Provider: "github"},
    "nvidia_nim/mistralai/mistral-large-3-675b-instruct-2512": {Params: 675, Ctx: 128000, Provider: "nvidia_nim"},
    "sambanova/DeepSeek-V3.2": {Params: 671, Ctx: 131072, Provider: "sambanova"},
    "cerebras/gpt-oss-120b": {Params: 120, Ctx: 131072, Provider: "cerebras"},
    "groq/llama-3.3-70b-versatile": {Params: 70, Ctx: 128000, Provider: "groq"},
    "mistral/mistral-large-latest": {Params: 123, Ctx: 128000, Provider: "mistral"},
    "opencode_zen/deepseek-v4-flash-free": {Params: 671, Ctx: 65536, Provider: "opencode_zen"},
}

func LookupKnownModel(modelID string) (ModelSpec, bool) {
    if spec, ok := KnownModels[modelID]; ok { return spec, true }
    for id, spec := range KnownModels {
        if strings.HasSuffix(modelID, id) || strings.HasSuffix(id, modelID) { return spec, true }
    }
    return ModelSpec{}, false
}

// DeadModels - models known to be 404/dead. Lowercase keys for case-insensitive matching.
var DeadModels = map[string]bool{
    "groq/llama-3.1-70b-versatile": true,
    "groq/mixtral-8x7b-32768": true,
    "cerebras/llama3.1-70b": true,
    "cerebras/llama3.1-8b": true,
    "openrouter/google/gemini-2.0-flash-exp:free": true,
    "openrouter/google/gemini-2.0-flash-thinking-exp:free": true,
    "openrouter/google/learnlm-1.5-pro-experimental:free": true,
    "openrouter/mistralai/mistral-7b-instruct:free": true,
    "openrouter/huggingfaceh4/zephyr-7b-beta:free": true,
    "openrouter/openchat/openchat-7b:free": true,
    "openrouter/qwen/qwen-2-7b-instruct:free": true,
    "openrouter/microsoft/phi-3-medium-128k-instruct:free": true,
    "openrouter/meta-llama/llama-3-8b-instruct:free": true,
    "openrouter/owl-alpha": true,
    "01-ai/yi-large": true,
    "adept/fuyu-8b": true,
    "ai21labs/jamba-1.5-large-instruct": true,
    "aisingapore/sea-lion-7b-instruct": true,
    "databricks/dbrx-instruct": true,
    "deepseek-ai/deepseek-coder-6.7b-instruct": true,
    "deepseek-ai/deepseek-v4-flash": true,
    "deepseek-ai/deepseek-v4-pro": true,
    "google/gemma-2b": true,
    "google/gemma-3-12b-it": true,
    "google/gemma-3-4b-it": true,
    "google/gemma-4-31b-it": true,
    "google/recurrentgemma-2b": true,
    "ibm/granite-3.0-3b-a800m-instruct": true,
    "ibm/granite-3.0-8b-instruct": true,
    "ibm/granite-34b-code-instruct": true,
    "ibm/granite-8b-code-instruct": true,
    "meta/codellama-70b": true,
    "meta/llama-3.1-70b-instruct": true,
    "meta/llama-4-maverick-17b-128e-instruct": true,
    "meta/llama2-70b": true,
    "microsoft/phi-3.5-moe-instruct": true,
    "microsoft/phi-4-mini-instruct": true,
    "microsoft/phi-4-multimodal-instruct": true,
    "minimaxai/minimax-m2.7": true,
    "mistralai/codestral-22b-instruct-v0.1": true,
    "mistralai/mistral-7b-instruct-v0.3": true,
    "mistralai/mistral-large": true,
    "mistralai/mistral-large-2-instruct": true,
    "mistralai/mistral-medium-3.5-128b": true,
    "mistralai/mistral-nemotron": true,
    "mistralai/mixtral-8x22b-v0.1": true,
    "nv-mistralai/mistral-nemo-12b-instruct": true,
    "nvidia/cosmos-reason2-8b": true,
    "nvidia/llama-3.1-nemotron-51b-instruct": true,
    "nvidia/llama-3.1-nemotron-70b-instruct": true,
    "nvidia/llama-3.1-nemotron-ultra-253b-v1": true,
    "nvidia/llama3-chatqa-1.5-70b": true,
    "nvidia/mistral-nemo-minitron-8b-8k-instruct": true,
    "nvidia/nemotron-4-340b-instruct": true,
    "nvidia/nemotron-nano-3-30b-a3b": true,
    "nvidia/vila": true,
    "qwen/qwen3-coder-480b-a35b-instruct": true,
    "qwen/qwen3.5-397b-a17b": true,
    "writer/palmyra-creative-122b": true,
    "writer/palmyra-fin-70b-32k": true,
    "writer/palmyra-med-70b": true,
    "writer/palmyra-med-70b-32k": true,
    "z-ai/glm-5.1": true,
    "zyphra/zamba2-7b-instruct": true,
    "deepseek-ai/deepseek-r1": true,
    "deepseek-ai/deepseek-v3": true,
    "meta/llama-3.1-405b-instruct": true,
    "0xsero/deepseek-v4-flash-162b": true,
    "0xsero/deepseek-v4-flash-180b": true,
    "essentialai/rnj-1.5-instruct": true,
    "qwen/qwen2.5-72b-instruct": true,
    "llama-4-scout-17b-16e-instruct": true,
    "whisper-large-v3": true,
    "whisper-large-v3-turbo": true,
    "text-embedding-nomic-embed-text-v1.5": true,
    "orpheus-v1-english": true,
    "orpheus-arabic-saudi": true,
    "hunyuanimage-3.0": true,
    "qwen/qwen3-coder-next": true,
    "xiaomimimo/mimo-v2.5-pro": true,
    "dphn/dolphin-x1-trinity-nano": true,
    "meta-llama/llama-3.1-405b-instruct": true,
    "meta-llama/llama-3.1-70b-instruct": true,
    "meta-llama/meta-llama-3.1-405b-instruct": true,
    "meta-llama/meta-llama-3.1-70b-instruct": true,
    "meta-llama-3.1-405b-instruct": true,
    "meta-llama-3.1-70b-instruct": true,
    "openai/gpt-oss-120b": true,
    "poolside/laguna-xs.2": true,
    "stepfun-ai/step-3.5-flash": true,
    "stepfun-ai/step-3.7-flash": true,
    "tencent/hy3-preview": true,
    "zai-org/glm-5.1": true,
    "qwen/qwen3.5-122b-a10b": true,
    "deepseek-ai/deepseek-v3-0324": true,
    "deepseek-ai/deepseek-r1-0528": true,
    "accounts/fireworks/models/kimi-k2p6": true,
    "accounts/fireworks/models/kimi-k2p5": true,
    "accounts/fireworks/models/gpt-oss-120b": true,
    "accounts/fireworks/models/glm-5p1": true,
    "accounts/fireworks/models/flux-kontext-pro": true,
    "accounts/fireworks/models/flux-kontext-max": true,
    "accounts/fireworks/models/flux-1-schnell-fp8": true,
    "accounts/fireworks/models/flux-1-dev-fp8": true,
    "accounts/fireworks/models/deepseek-v4-pro": true,
    "compound": true,
    "compound-mini": true,
    "llama-prompt-guard-2-86m": true,
    "llama-prompt-guard-2-22m": true,
    "google/lyria-3-pro-preview": true,
    "google/lyria-3-clip-preview": true,
    "minimax-m2.7": true,
    "qwen3.6-plus-free": true,
}

func IsDeadModel(modelID string) bool {
    lower := strings.ToLower(modelID)
    if DeadModels[lower] { return true }
    if idx := strings.Index(lower, "/"); idx >= 0 {
        if DeadModels[lower[idx+1:]] { return true }
    }
    return false
}

var DeadProviders = map[string]bool{
    "together": true,
    "gemini": true,
    "nebius": true,
	"huggingface": true,
}

func IsDeadProvider(provider string) bool {
    lower := strings.ToLower(provider)
    if DeadProviders[lower] { return true }
    for dp := range DeadProviders {
        if strings.Contains(lower, dp) { return true }
    }
    return false
}

var GlobalExclusions = []string{
	"-base",
	"dummy",
	"whisper",
	"orpheus",
	"flux",
	"prompt-guard",
	"compound",
	"lyria",
	"dall",
	"sdxl",
	"stable-diffusion",
	"midjourney",
	"canopylabs",
	"tts",
	"asr",
	"image-gen",
	"embed",
	"nomic-embed",
	"nomic-embed-text",
	"text-embedding",
	// Non-chat model types
	"ocr",
	"voxtral",
	"moderation",
	"nemotron-parse",
	"nemoretriever",
	"bge-m3",
	"deplot",
	"kosmos-2",
	"nvclip",
	"nemotron-4-340b-reward",
	"reward",
	"ai-synthetic-video",
	"phi-3-vision",
	"labs-",
}

func IsExcluded(modelID string) bool {
    lower := strings.ToLower(modelID)
    for _, exc := range GlobalExclusions {
        if strings.Contains(lower, exc) { return true }
    }
    return false
}

// StreamTimeoutProviders need longer streaming timeouts.
var StreamTimeoutProviders = map[string]bool{
    "nvidia_nim": true, "nvidia": true, "openrouter": true,
    "sambanova": true,
}

func NeedsStreamTimeout(provider string) bool {
    return StreamTimeoutProviders[strings.ToLower(provider)]
}
