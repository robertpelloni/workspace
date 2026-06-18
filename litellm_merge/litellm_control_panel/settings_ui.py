import tkinter as tk
from tkinter import ttk, messagebox, scrolledtext
import json
import os
import datetime
import known_models

SETTINGS_FILE = "settings.json"

# Map: settings key -> environment variable name
ENV_KEY_MAP = {
    "OPENROUTER_API_KEY": "OPENROUTER_API_KEY",
    "GROQ_API_KEY": "GROQ_API_KEY",
    "TOGETHER_API_KEY": "TOGETHER_API_KEY",
    "DEEPINFRA_API_KEY": "DEEPINFRA_API_KEY",
    "CEREBRAS_API_KEY": "CEREBRAS_API_KEY",
    "GITHUB_API_KEY": "GITHUB_TOKEN",
    "GEMINI_API_KEY": "GEMINI_API_KEY",
    "HUGGINGFACE_API_KEY": "HUGGINGFACE_API_KEY",
    "NVIDIA_API_KEY": "NVIDIA_NIM_API_KEY",
    "MISTRAL_API_KEY": "MISTRAL_API_KEY",
    "CODESTRAL_API_KEY": "CODESTRAL_API_KEY",
    "COHERE_API_KEY": "COHERE_API_KEY",
    "SAMBANOVA_API_KEY": "SAMBANOVA_API_KEY",
    "FIREWORKS_API_KEY": "FIREWORKS_API_KEY",
    "HYPERBOLIC_API_KEY": "HYPERBOLIC_API_KEY",
    "NEBIUS_API_KEY": "NEBIUS_API_KEY",
    "CLOUDFLARE_API_KEY": "CLOUDFLARE_API_KEY",
    "OPENCODE_ZEN_API_KEY": "OPENCODE_ZEN_API_KEY",
}

def load_settings():
    if os.path.exists(SETTINGS_FILE):
        try:
            with open(SETTINGS_FILE, 'r') as f:
                return json.load(f)
        except:
            pass
    return {
        "OPENROUTER_API_KEY": os.environ.get("OPENROUTER_API_KEY", ""),
        "GROQ_API_KEY": os.environ.get("GROQ_API_KEY", ""),
        "TOGETHER_API_KEY": os.environ.get("TOGETHER_API_KEY", ""),
        "DEEPINFRA_API_KEY": os.environ.get("DEEPINFRA_API_KEY", ""),
        "CEREBRAS_API_KEY": os.environ.get("CEREBRAS_API_KEY", ""),
        "GITHUB_API_KEY": os.environ.get("GITHUB_TOKEN", ""),
        "HUGGINGFACE_API_KEY": os.environ.get("HUGGINGFACE_API_KEY", ""),
        "NVIDIA_API_KEY": os.environ.get("NVIDIA_NIM_API_KEY", ""),
        "OPENROUTER_BASE_URL": "https://openrouter.ai/api/v1",
        "GROQ_BASE_URL": "https://api.groq.com/openai/v1",
        "TOGETHER_BASE_URL": "https://api.together.xyz",
        "DEEPINFRA_BASE_URL": "https://api.deepinfra.com/v1/openai",
        "CEREBRAS_BASE_URL": "https://api.cerebras.ai/v1",
        "GITHUB_BASE_URL": "https://models.inference.ai.azure.com",
        "HUGGINGFACE_BASE_URL": "https://api-inference.huggingface.co",
        "NVIDIA_BASE_URL": "https://integrate.api.nvidia.com/v1",
        "OLLAMA_BASE_URL": "http://localhost:11434",
        "LM_STUDIO_BASE_URL": "http://localhost:1234",
        "MIN_PARAMETERS": 0,
        "AUTO_PILOT": False,
        "GLOBAL_EXCLUSIONS": "-base, vision, dummy",
        "CONFIG_PATH": "C:/Users/hyper/.hermes/litellm-config.yaml",
        "INTERFACE_URL": "http://localhost:4000",
        "AUTO_MANAGE_LITELLM": True,
        "START_WITH_WINDOWS": False,
        "ROUTING_ENABLED": True,
        "ENABLE_NOTIFICATIONS": True,
        "PRIMARY_COUNT": 5,
        "SIZE_WEIGHT": 0.6,
        "CONTEXT_WEIGHT": 0.2,
        "LATENCY_WEIGHT": 0.2
    }

def save_settings(settings):
    with open(SETTINGS_FILE, 'w') as f:
        json.dump(settings, f, indent=4)

class SettingsUI:
    def __init__(self, on_save_callback=None, engine=None):
        self.on_save_callback = on_save_callback
        self.engine = engine
        self.root = tk.Tk()
        self.root.title("LiteLLM Control Panel Settings")
        self.root.geometry("550x850")
        self.root.resizable(True, True)

        self.settings = load_settings()
        self.create_widgets()
        
        if self.engine:
            self.engine.add_log_listener(self.on_engine_log)

    def on_engine_log(self, msg):
        if hasattr(self, 'log_area'):
            self.root.after(0, lambda: self._append_log(msg))

    def _append_log(self, msg):
        try:
            self.log_area.configure(state='normal')
            self.log_area.insert(tk.END, f"[{datetime.datetime.now().strftime('%H:%M:%S')}] {msg}\n")
            self.log_area.see(tk.END)
            self.log_area.configure(state='disabled')
        except:
            pass

    def create_widgets(self):
        padding = {'padx': 10, 'pady': 5}
        
        self.notebook = ttk.Notebook(self.root)
        self.notebook.pack(fill='both', expand=True, padx=5, pady=5)

        # Tab 1: General Settings
        self.settings_tab = ttk.Frame(self.notebook)
        self.notebook.add(self.settings_tab, text='General Settings')
        
        # Tab 2: Known Models
        self.km_tab = ttk.Frame(self.notebook)
        self.notebook.add(self.km_tab, text='Known Good Models')
        
        # Tab 3: Live Logs
        self.logs_tab = ttk.Frame(self.notebook)
        self.notebook.add(self.logs_tab, text='Live Benchmarking Logs')

        self._setup_settings_tab(self.settings_tab)
        self._setup_km_tab(self.km_tab)
        self._setup_logs_tab(self.logs_tab)

    def _setup_settings_tab(self, tab):
        padding = {'padx': 10, 'pady': 2}
        
        canvas = tk.Canvas(tab)
        scrollbar = ttk.Scrollbar(tab, orient="vertical", command=canvas.yview)
        scrollable_frame = ttk.Frame(canvas)

        scrollable_frame.bind(
            "<Configure>",
            lambda e: canvas.configure(
                scrollregion=canvas.bbox("all")
            )
        )

        canvas.create_window((0, 0), window=scrollable_frame, anchor="nw")
        canvas.configure(yscrollcommand=scrollbar.set)
        
        container = scrollable_frame

        # API Keys and Base URLs
        keys_frame = ttk.LabelFrame(container, text="Provider Configuration")
        keys_frame.pack(fill='x', **padding)

        def add_provider_fields(frame, name, key_pref, url_pref, row):
            ttk.Label(frame, text=f"{name} Key:").grid(row=row, column=0, sticky='w', padx=5, pady=2)
            ent_key = ttk.Entry(frame, show="*")
            ent_key.insert(0, self.settings.get(key_pref, ""))
            ent_key.grid(row=row, column=1, sticky='ew', padx=5, pady=2)

            ttk.Label(frame, text="URL:").grid(row=row, column=2, sticky='w', padx=5, pady=2)
            ent_url = ttk.Entry(frame)
            ent_url.insert(0, self.settings.get(url_pref, ""))
            ent_url.grid(row=row, column=3, sticky='ew', padx=5, pady=2)
            return ent_key, ent_url

        self.or_key, self.or_url = add_provider_fields(keys_frame, "OpenRouter", "OPENROUTER_API_KEY", "OPENROUTER_BASE_URL", 0)
        self.groq_key, self.groq_url = add_provider_fields(keys_frame, "Groq", "GROQ_API_KEY", "GROQ_BASE_URL", 1)
        self.together_key, self.together_url = add_provider_fields(keys_frame, "Together", "TOGETHER_API_KEY", "TOGETHER_BASE_URL", 2)
        self.deepinfra_key, self.deepinfra_url = add_provider_fields(keys_frame, "DeepInfra", "DEEPINFRA_API_KEY", "DEEPINFRA_BASE_URL", 3)
        self.cerebras_key, self.cerebras_url = add_provider_fields(keys_frame, "Cerebras", "CEREBRAS_API_KEY", "CEREBRAS_BASE_URL", 4)
        self.github_key, self.github_url = add_provider_fields(keys_frame, "GitHub", "GITHUB_API_KEY", "GITHUB_BASE_URL", 5)
        self.gemini_key, self.gemini_url = add_provider_fields(keys_frame, "Gemini", "GEMINI_API_KEY", "GEMINI_BASE_URL", 6)
        self.hf_key, self.hf_url = add_provider_fields(keys_frame, "HuggingFace", "HUGGINGFACE_API_KEY", "HUGGINGFACE_BASE_URL", 7)
        self.nvidia_key, self.nvidia_url = add_provider_fields(keys_frame, "NVIDIA", "NVIDIA_API_KEY", "NVIDIA_BASE_URL", 8)
        self.mistral_key, self.mistral_url = add_provider_fields(keys_frame, "Mistral", "MISTRAL_API_KEY", "MISTRAL_BASE_URL", 9)
        self.codestral_key, self.codestral_url = add_provider_fields(keys_frame, "Codestral", "CODESTRAL_API_KEY", "CODESTRAL_BASE_URL", 10)
        self.cohere_key, self.cohere_url = add_provider_fields(keys_frame, "Cohere", "COHERE_API_KEY", "COHERE_BASE_URL", 11)
        self.sambanova_key, self.sambanova_url = add_provider_fields(keys_frame, "SambaNova", "SAMBANOVA_API_KEY", "SAMBANOVA_BASE_URL", 12)
        self.fireworks_key, self.fireworks_url = add_provider_fields(keys_frame, "Fireworks", "FIREWORKS_API_KEY", "FIREWORKS_BASE_URL", 13)
        self.hyperbolic_key, self.hyperbolic_url = add_provider_fields(keys_frame, "Hyperbolic", "HYPERBOLIC_API_KEY", "HYPERBOLIC_BASE_URL", 14)
        self.nebius_key, self.nebius_url = add_provider_fields(keys_frame, "Nebius", "NEBIUS_API_KEY", "NEBIUS_BASE_URL", 15)
        self.cloudflare_key, self.cloudflare_url = add_provider_fields(keys_frame, "Cloudflare", "CLOUDFLARE_API_KEY", "CLOUDFLARE_BASE_URL", 16)
        ttk.Label(keys_frame, text="CF Account ID:").grid(row=16, column=2, sticky='w', padx=5, pady=2)
        self.cf_account_id = ttk.Entry(keys_frame, width=30)
        self.cf_account_id.insert(0, self.settings.get("CLOUDFLARE_ACCOUNT_ID", ""))
        self.cf_account_id.grid(row=16, column=3, sticky='ew', padx=5, pady=2)

        ttk.Label(keys_frame, text="OpenCode Zen:").grid(row=17, column=0, sticky='w', padx=5, pady=2)
        self.opencode_zen_url = ttk.Entry(keys_frame)
        self.opencode_zen_url.insert(0, self.settings.get("OPENCODE_ZEN_BASE_URL", "https://opencode.ai/zen/v1"))
        self.opencode_zen_url.grid(row=17, column=1, columnspan=3, sticky='ew', padx=5, pady=2)

        # Local URLs
        ttk.Label(keys_frame, text="Ollama URL:").grid(row=17, column=0, sticky='w', padx=5, pady=2)
        self.ollama_url = ttk.Entry(keys_frame)
        self.ollama_url.insert(0, self.settings.get("OLLAMA_BASE_URL", "http://localhost:11434"))
        self.ollama_url.grid(row=9, column=1, columnspan=3, sticky='ew', padx=5, pady=2)

        ttk.Label(keys_frame, text="LM Studio URL:").grid(row=18, column=0, sticky='w', padx=5, pady=2)
        self.lms_url = ttk.Entry(keys_frame)
        self.lms_url.insert(0, self.settings.get("LM_STUDIO_BASE_URL", "http://localhost:1234"))
        self.lms_url.grid(row=18, column=1, columnspan=3, sticky='ew', padx=5, pady=2)

        keys_frame.columnconfigure(1, weight=1)
        keys_frame.columnconfigure(3, weight=1)

        # General Params
        gen_frame = ttk.LabelFrame(container, text="Benchmark & Router Settings")
        gen_frame.pack(fill='x', **padding)

        ttk.Label(gen_frame, text="Minimum Parameters (Billions):").grid(row=0, column=0, sticky='w', **padding)
        self.min_params = ttk.Spinbox(gen_frame, from_=1, to=1000)
        self.min_params.set(self.settings.get("MIN_PARAMETERS", 100))
        self.min_params.grid(row=0, column=1, sticky='ew', **padding)

        ttk.Label(gen_frame, text="Primary Group Size:").grid(row=1, column=0, sticky='w', **padding)
        self.primary_count = ttk.Spinbox(gen_frame, from_=1, to=50)
        self.primary_count.set(self.settings.get("PRIMARY_COUNT", 5))
        self.primary_count.grid(row=1, column=1, sticky='ew', **padding)

        ttk.Label(gen_frame, text="Global Exclusions:").grid(row=2, column=0, sticky='w', **padding)
        self.exclusions = ttk.Entry(gen_frame)
        self.exclusions.insert(0, self.settings.get("GLOBAL_EXCLUSIONS", "-base, vision, dummy"))
        self.exclusions.grid(row=2, column=1, sticky='ew', **padding)

        gen_frame.columnconfigure(1, weight=1)

        # Paths
        path_frame = ttk.LabelFrame(container, text="System Paths")
        path_frame.pack(fill='x', **padding)

        ttk.Label(path_frame, text="LiteLLM Config Path:").grid(row=0, column=0, sticky='w', **padding)
        self.config_path = ttk.Entry(path_frame)
        self.config_path.insert(0, self.settings.get("CONFIG_PATH", "config.yaml"))
        self.config_path.grid(row=0, column=1, sticky='ew', **padding)

        ttk.Label(path_frame, text="LLM Interface URL:").grid(row=1, column=0, sticky='w', **padding)
        self.interface_url = ttk.Entry(path_frame)
        self.interface_url.insert(0, self.settings.get("INTERFACE_URL", "http://localhost:4000"))
        self.interface_url.grid(row=1, column=1, sticky='ew', **padding)
        
        path_frame.columnconfigure(1, weight=1)

        # Options
        opt_frame = ttk.LabelFrame(container, text="Options")
        opt_frame.pack(fill='x', **padding)

        self.auto_manage_var = tk.BooleanVar(value=self.settings.get("AUTO_MANAGE_LITELLM", True))
        ttk.Checkbutton(opt_frame, text="Auto-Manage LiteLLM Proxy", variable=self.auto_manage_var).pack(anchor='w', **padding)

        self.start_with_windows_var = tk.BooleanVar(value=self.settings.get("START_WITH_WINDOWS", False))
        ttk.Checkbutton(opt_frame, text="Start with Windows", variable=self.start_with_windows_var).pack(anchor='w', **padding)

        self.enable_notifications_var = tk.BooleanVar(value=self.settings.get("ENABLE_NOTIFICATIONS", True))
        ttk.Checkbutton(opt_frame, text="Enable Notifications", variable=self.enable_notifications_var).pack(anchor='w', **padding)

        # Weights
        weights_frame = ttk.LabelFrame(container, text="Scoring Weights")
        weights_frame.pack(fill='x', **padding)

        ttk.Label(weights_frame, text="Size:").grid(row=0, column=0, padx=5)
        self.size_weight = ttk.Spinbox(weights_frame, from_=0, to=1, increment=0.1, width=5)
        self.size_weight.set(self.settings.get("SIZE_WEIGHT", 0.6))
        self.size_weight.grid(row=0, column=1, padx=5)

        ttk.Label(weights_frame, text="Context:").grid(row=0, column=2, padx=5)
        self.context_weight = ttk.Spinbox(weights_frame, from_=0, to=1, increment=0.1, width=5)
        self.context_weight.set(self.settings.get("CONTEXT_WEIGHT", 0.2))
        self.context_weight.grid(row=0, column=3, padx=5)

        ttk.Label(weights_frame, text="Latency:").grid(row=0, column=4, padx=5)
        self.latency_weight = ttk.Spinbox(weights_frame, from_=0, to=1, increment=0.1, width=5)
        self.latency_weight.set(self.settings.get("LATENCY_WEIGHT", 0.2))
        self.latency_weight.grid(row=0, column=5, padx=5)

        # Live Logs Shortcut
        logs_frame = ttk.LabelFrame(container, text="Live Monitoring")
        logs_frame.pack(fill='x', **padding)

        btn_row = ttk.Frame(logs_frame)
        btn_row.pack(fill='x', padx=5, pady=5)

        def safe_proxy():
            if self.on_proxy_logs_callback: self.on_proxy_logs_callback()
            else: messagebox.showinfo("Info", "Log viewer unavailable in standalone mode.")

        def safe_engine():
            if self.on_engine_logs_callback: self.on_engine_logs_callback()
            else: messagebox.showinfo("Info", "Log viewer unavailable in standalone mode.")

        ttk.Button(btn_row, text="Open Proxy Logs",
                   command=safe_proxy).pack(side='left', padx=5)
        ttk.Button(btn_row, text="Open Engine Logs",
                   command=safe_engine).pack(side='left', padx=5)

        # API Server Settings
        api_frame = ttk.LabelFrame(container, text="External API")
        api_frame.pack(fill='x', **padding)

        self.enable_api_var = tk.BooleanVar(value=self.settings.get("ENABLE_API", False))
        ttk.Checkbutton(api_frame, text="Enable External API Server",
                        variable=self.enable_api_var).pack(fill='x', **padding)

        port_row = ttk.Frame(api_frame)
        port_row.pack(fill='x', padx=5, pady=2)
        ttk.Label(port_row, text="API Port:").pack(side='left', padx=5)
        self.api_port = ttk.Entry(port_row, width=10)
        self.api_port.insert(0, str(self.settings.get("API_PORT", 8000)))
        self.api_port.pack(side='left', padx=5)

        # Save Button
        ttk.Button(container, text="Save Settings", command=self.save).pack(pady=20)

        canvas.pack(side="left", fill="both", expand=True)
        scrollbar.pack(side="right", fill="y")

    def _setup_km_tab(self, tab):
        padding = {'padx': 10, 'pady': 10}
        
        ttk.Label(tab, text="Models with guaranteed specs (override missing metadata):",
                  font=('Helvetica', 10, 'bold')).pack(fill='x', padx=10, pady=(10, 2))

        km_cols = ('id', 'params', 'ctx', 'provider')
        self.km_tree = ttk.Treeview(tab, columns=km_cols, show='headings', height=25)
        self.km_tree.heading('id', text='LiteLLM Model ID')
        self.km_tree.heading('params', text='Params(B)')
        self.km_tree.heading('ctx', text='Context')
        self.km_tree.heading('provider', text='Provider')
        self.km_tree.column('id', width=250)
        self.km_tree.column('params', width=70)
        self.km_tree.column('ctx', width=80)
        self.km_tree.column('provider', width=80)
        self.km_tree.pack(fill='both', expand=True, padx=10, pady=5)

        km_scroll = ttk.Scrollbar(self.km_tree, orient='vertical', command=self.km_tree.yview)
        self.km_tree.configure(yscrollcommand=km_scroll.set)
        km_scroll.pack(side='right', fill='y')

        self._populate_known_models()

        btn_frame = ttk.Frame(tab)
        btn_frame.pack(fill='x', padx=10, pady=10)

        ttk.Button(btn_frame, text="Add Model", command=self.km_add).pack(side='left', padx=5)
        ttk.Button(btn_frame, text="Edit Selected", command=self.km_edit).pack(side='left', padx=5)
        ttk.Button(btn_frame, text="Remove Selected", command=self.km_remove).pack(side='left', padx=5)
        ttk.Button(btn_frame, text="Reset Defaults", command=self.km_reset).pack(side='right', padx=5)

    def _setup_logs_tab(self, tab):
        ttk.Label(tab, text="Real-time Benchmarking Events:", font=('Helvetica', 10, 'bold')).pack(fill='x', padx=10, pady=(10, 2))
        
        self.log_area = scrolledtext.ScrolledText(tab, state='disabled', wrap='word', bg='black', fg='lightgreen', font=('Consolas', 10))
        self.log_area.pack(fill='both', expand=True, padx=10, pady=5)
        
        btn_frame = ttk.Frame(tab)
        btn_frame.pack(fill='x', padx=10, pady=5)
        
        def clear_logs():
            self.log_area.configure(state='normal')
            self.log_area.delete('1.0', tk.END)
            self.log_area.configure(state='disabled')
            
        ttk.Button(btn_frame, text="Clear Logs", command=clear_logs).pack(side='right')

    def save(self):
        try:
            self.settings["OPENROUTER_API_KEY"] = self.or_key.get()
            self.settings["GROQ_API_KEY"] = self.groq_key.get()
            self.settings["TOGETHER_API_KEY"] = self.together_key.get()
            self.settings["DEEPINFRA_API_KEY"] = self.deepinfra_key.get()
            self.settings["CEREBRAS_API_KEY"] = self.cerebras_key.get()
            self.settings["GITHUB_API_KEY"] = self.github_key.get()
            self.settings["HUGGINGFACE_API_KEY"] = self.hf_key.get()
            self.settings["NVIDIA_API_KEY"] = self.nvidia_key.get()
            self.settings["MISTRAL_API_KEY"] = self.mistral_key.get()
            self.settings["CODESTRAL_API_KEY"] = self.codestral_key.get()
            self.settings["COHERE_API_KEY"] = self.cohere_key.get()
            self.settings["SAMBANOVA_API_KEY"] = self.sambanova_key.get()
            self.settings["FIREWORKS_API_KEY"] = self.fireworks_key.get()
            self.settings["HYPERBOLIC_API_KEY"] = self.hyperbolic_key.get()
            self.settings["NEBIUS_API_KEY"] = self.nebius_key.get()
            self.settings["CLOUDFLARE_API_KEY"] = self.cloudflare_key.get()

            self.settings["OPENROUTER_BASE_URL"] = self.or_url.get()
            self.settings["GROQ_BASE_URL"] = self.groq_url.get()
            self.settings["TOGETHER_BASE_URL"] = self.together_url.get()
            self.settings["DEEPINFRA_BASE_URL"] = self.deepinfra_url.get()
            self.settings["CEREBRAS_BASE_URL"] = self.cerebras_url.get()
            self.settings["GITHUB_BASE_URL"] = self.github_url.get()
            self.settings["HUGGINGFACE_BASE_URL"] = self.hf_url.get()
            self.settings["NVIDIA_BASE_URL"] = self.nvidia_url.get()
            self.settings["MISTRAL_BASE_URL"] = self.mistral_url.get()
            self.settings["CODESTRAL_BASE_URL"] = self.codestral_url.get()
            self.settings["COHERE_BASE_URL"] = self.cohere_url.get()
            self.settings["SAMBANOVA_BASE_URL"] = self.sambanova_url.get()
            self.settings["FIREWORKS_BASE_URL"] = self.fireworks_url.get()
            self.settings["HYPERBOLIC_BASE_URL"] = self.hyperbolic_url.get()
            self.settings["NEBIUS_BASE_URL"] = self.nebius_url.get()
            self.settings["CLOUDFLARE_BASE_URL"] = self.cloudflare_url.get()
            self.settings["CLOUDFLARE_ACCOUNT_ID"] = self.cf_account_id.get()
            self.settings["OPENCODE_ZEN_BASE_URL"] = self.opencode_zen_url.get()
            self.settings["OLLAMA_BASE_URL"] = self.ollama_url.get()
            self.settings["LM_STUDIO_BASE_URL"] = self.lms_url.get()
            
            self.settings["GLOBAL_EXCLUSIONS"] = self.exclusions.get()
            self.settings["CONFIG_PATH"] = self.config_path.get()
            self.settings["INTERFACE_URL"] = self.interface_url.get()
            self.settings["AUTO_MANAGE_LITELLM"] = self.auto_manage_var.get()
            self.settings["START_WITH_WINDOWS"] = self.start_with_windows_var.get()
            self.settings["ENABLE_NOTIFICATIONS"] = self.enable_notifications_var.get()
            
            self.settings["SIZE_WEIGHT"] = float(self.size_weight.get())
            self.settings["CONTEXT_WEIGHT"] = float(self.context_weight.get())
            self.settings["LATENCY_WEIGHT"] = float(self.latency_weight.get())
            self.settings["MIN_PARAMETERS"] = int(self.min_params.get())
            self.settings["PRIMARY_COUNT"] = int(self.primary_count.get())
        except Exception as e:
            messagebox.showerror("Error", f"Invalid input: {e}")
            return

        save_settings(self.settings)
        messagebox.showinfo("Success", "Settings saved successfully!")

        if self.on_save_callback:
            self.on_save_callback(self.settings)

        self.root.destroy()

    def _populate_known_models(self):
        for i in self.km_tree.get_children():
            self.km_tree.delete(i)
        for litellm_id, spec in sorted(known_models.all_models().items()):
            self.km_tree.insert('', 'end', values=(
                litellm_id,
                spec.get('params', 0),
                spec.get('ctx', 0),
                spec.get('provider', ''),
            ))

    def km_add(self):
        win = tk.Toplevel(self.root)
        win.title('Add Known Model')
        win.geometry('400x220')
        win.resizable(False, False)
        
        ttk.Label(win, text='LiteLLM Model ID:').grid(row=0, column=0, padx=10, pady=5, sticky='w')
        id_entry = ttk.Entry(win, width=40)
        id_entry.grid(row=0, column=1, padx=10, pady=5)
        
        ttk.Label(win, text='Parameters (B):').grid(row=1, column=0, padx=10, pady=5, sticky='w')
        params_entry = ttk.Entry(win, width=15)
        params_entry.grid(row=1, column=1, padx=10, pady=5, sticky='w')
        
        ttk.Label(win, text='Context Length:').grid(row=2, column=0, padx=10, pady=5, sticky='w')
        ctx_entry = ttk.Entry(win, width=15)
        ctx_entry.grid(row=2, column=1, padx=10, pady=5, sticky='w')
        
        ttk.Label(win, text='Provider:').grid(row=3, column=0, padx=10, pady=5, sticky='w')
        prov_entry = ttk.Entry(win, width=20)
        prov_entry.grid(row=3, column=1, padx=10, pady=5, sticky='w')

        def do_add():
            mid = id_entry.get().strip()
            if not mid:
                messagebox.showwarning('Warning', 'Model ID is required.', parent=win)
                return
            try:
                p = int(params_entry.get())
                c = int(ctx_entry.get())
            except ValueError:
                messagebox.showerror('Error', 'Parameters and Context must be integers.', parent=win)
                return
            prov = prov_entry.get().strip()
            known_models.add_model(mid, p, c, prov)
            self._populate_known_models()
            win.destroy()

        ttk.Button(win, text='Add Model', command=do_add).grid(row=4, column=0, columnspan=2, pady=15)

    def km_edit(self):
        sel = self.km_tree.selection()
        if not sel:
            messagebox.showinfo('Info', 'Select a model to edit.', parent=self.root)
            return
        vals = self.km_tree.item(sel[0])['values']
        if not vals:
            return
        old_id = str(vals[0])

        win = tk.Toplevel(self.root)
        win.title('Edit Known Model')
        win.geometry('400x220')
        win.resizable(False, False)
        
        ttk.Label(win, text='LiteLLM Model ID:').grid(row=0, column=0, padx=10, pady=5, sticky='w')
        id_entry = ttk.Entry(win, width=40)
        id_entry.insert(0, old_id)
        id_entry.config(state='readonly')
        id_entry.grid(row=0, column=1, padx=10, pady=5)
        
        ttk.Label(win, text='Parameters (B):').grid(row=1, column=0, padx=10, pady=5, sticky='w')
        params_entry = ttk.Entry(win, width=15)
        params_entry.insert(0, str(vals[1]))
        params_entry.grid(row=1, column=1, padx=10, pady=5, sticky='w')
        
        ttk.Label(win, text='Context Length:').grid(row=2, column=0, padx=10, pady=5, sticky='w')
        ctx_entry = ttk.Entry(win, width=15)
        ctx_entry.insert(0, str(vals[2]))
        ctx_entry.grid(row=2, column=1, padx=10, pady=5, sticky='w')
        
        ttk.Label(win, text='Provider:').grid(row=3, column=0, padx=10, pady=5, sticky='w')
        prov_entry = ttk.Entry(win, width=20)
        prov_entry.insert(0, str(vals[3]))
        prov_entry.grid(row=3, column=1, padx=10, pady=5, sticky='w')

        def do_save():
            try:
                p = int(params_entry.get())
                c = int(ctx_entry.get())
            except ValueError:
                messagebox.showerror('Error', 'Parameters and Context must be integers.', parent=win)
                return
            prov = prov_entry.get().strip()
            known_models.add_model(old_id, p, c, prov)
            self._populate_known_models()
            win.destroy()

        ttk.Button(win, text='Save Changes', command=do_save).grid(row=4, column=0, columnspan=2, pady=15)

    def km_remove(self):
        sel = self.km_tree.selection()
        if not sel:
            messagebox.showinfo('Info', 'Select a model to remove.', parent=self.root)
            return
        vals = self.km_tree.item(sel[0])['values']
        if not vals:
            return
        model_id = str(vals[0])
        if messagebox.askyesno('Confirm', f"Remove '{model_id}' from known models?", parent=self.root):
            known_models.remove_model(model_id)
            self._populate_known_models()

    def km_reset(self):
        if messagebox.askyesno('Confirm', 'Reset all known models to defaults?', parent=self.root):
            import importlib
            importlib.reload(known_models)
            self._populate_known_models()
            messagebox.showinfo('Done', 'Known models reset to defaults.', parent=self.root)

    def run(self):
        self.root.mainloop()

if __name__ == "__main__":
    ui = SettingsUI()
    ui.run()
