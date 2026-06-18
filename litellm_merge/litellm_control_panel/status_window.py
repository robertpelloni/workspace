import tkinter as tk
from tkinter import ttk
import database

class StatusWindow:
    def __init__(self, app_instance):
        self.app = app_instance
        self.root = tk.Tk()
        self.root.title("LiteLLM System Status")
        self.root.geometry("500x400")
        self.root.resizable(False, False)

        self.create_widgets()
        self.update_status()

    def create_widgets(self):
        padding = {'padx': 20, 'pady': 10}

        # LiteLLM Proxy Status
        self.proxy_label = ttk.Label(self.root, text="LiteLLM Proxy: Checking...", font=('Helvetica', 12, 'bold'))
        self.proxy_label.pack(fill='x', **padding)

        # Active Model
        self.model_label = ttk.Label(self.root, text="Active Model: None", font=('Helvetica', 10))
        self.model_label.pack(fill='x', **padding)

        # Last Benchmark
        self.benchmark_label = ttk.Label(self.root, text="Last Benchmark: Never", font=('Helvetica', 10))
        self.benchmark_label.pack(fill='x', **padding)

        # Provider Health Overview
        ttk.Label(self.root, text="Provider Health Overview:", font=('Helvetica', 10, 'bold')).pack(fill='x', **padding)

        self.provider_tree = ttk.Treeview(self.root, columns=('provider', 'status'), show='headings', height=5)
        self.provider_tree.heading('provider', text='Provider')
        self.provider_tree.heading('status', text='Status')
        self.provider_tree.column('provider', width=200)
        self.provider_tree.column('status', width=200)
        self.provider_tree.pack(fill='both', expand=True, padx=20, pady=5)

        # Buttons
        btn_frame = ttk.Frame(self.root)
        btn_frame.pack(fill='x', pady=20)
        ttk.Button(btn_frame, text="Refresh Status", command=self.update_status).pack(side='right', padx=20)

    def update_status(self):
        # Update Proxy Status
        is_running = self.app.process_mgr.is_running()
        status_text = "Running" if is_running else "Stopped"
        color = "green" if is_running else "red"
        self.proxy_label.config(text=f"LiteLLM Proxy: {status_text}", foreground=color)

        # Update Active Model
        active_model = "None"
        if self.app.ranked_models:
            active_model = self.app.ranked_models[0]['id']
        self.model_label.config(text=f"Active Model: {active_model}")

        # Update Last Benchmark
        if self.app.last_benchmark_time:
            time_str = self.app.last_benchmark_time.strftime("%Y-%m-%d %H:%M:%S")
            self.benchmark_label.config(text=f"Last Benchmark: {time_str}")

        # Update Provider Tree
        for i in self.provider_tree.get_children():
            self.provider_tree.delete(i)

        provider_stats = database.get_provider_status()
        for name, is_free, empty_cycles, last_check in provider_stats:
            status = "Online" if is_free else "Offline"
            self.provider_tree.insert('', 'end', values=(name, status))

    def run(self):
        self.root.mainloop()
