import yaml

path = "/home/hyper/.hermes/litellm-config.yaml"
data = yaml.safe_load(open(path))

ml = data["model_list"]

# Separate models by group
free_llm_models = [m for m in ml if m["model_name"] == "free-llm"]
free_llm_or = [m for m in ml if m["model_name"] == "free-llm-or"]
free_llm_thinking = [m for m in ml if m["model_name"] == "free-llm-thinking"]

# Within free-llm, separate by provider
ollama = [m for m in free_llm_models if "ollama.com" in m["litellm_params"].get("api_base", "")]
nim = [m for m in free_llm_models if "nvidia" in m["litellm_params"].get("api_base", "") or "integrate.api.nvidia" in m["litellm_params"].get("api_base", "")]
other = [m for m in free_llm_models if m not in ollama and m not in nim]

print("free-llm: %d ollama, %d nim, %d other" % (len(ollama), len(nim), len(other)))

# Reorder: Ollama first (fast + tool capable), then NIM
for i, m in enumerate(ollama):
    m["litellm_params"]["order"] = i + 1
for i, m in enumerate(nim):
    m["litellm_params"]["order"] = len(ollama) + i + 1

# Rebuild model_list
reordered = ollama + nim + other + free_llm_or + free_llm_thinking
data["model_list"] = reordered

# Update fallbacks
data["default_fallbacks"] = ["free-llm-or"]
data["fallbacks"] = [
    {"free-llm": ["free-llm-or"]},
    {"free-llm-thinking": ["free-llm-or", "free-llm"]},
    {"free-llm-or": ["free-llm"]},
]

with open(path, "w") as f:
    yaml.dump(data, f, default_flow_style=False, width=200, sort_keys=False)

print("Reordered: Ollama(%d) -> NIM(%d) -> Other(%d)" % (len(ollama), len(nim), len(other)))
print("Fallback: free-llm -> free-llm-or")
