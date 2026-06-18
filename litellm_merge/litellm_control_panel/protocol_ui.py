import tkinter as tk
from tkinter import ttk
import database

class ProtocolOversightUI:
    def __init__(self, app_instance):
        self.app = app_instance
        self.root = tk.Tk()
        self.root.title("LiteLLM Control Panel - Protocol Oversight")
        self.root.geometry("1000x800")

        self.create_widgets()
        self.update_loop()
        self.root.protocol("WM_DELETE_WINDOW", self.root.destroy)

    def create_widgets(self):
        padding = {'padx': 20, 'pady': 10}

        # 1. Engine Status Section
        status_frame = ttk.LabelFrame(self.root, text="Live Engine Status", padding=10)
        status_frame.pack(fill='x', padx=10, pady=5)

        self.state_var = tk.StringVar(value="State: Idle")
        self.task_var = tk.StringVar(value="Task: Waiting")

        ttk.Label(status_frame, textvariable=self.state_var, font=('Helvetica', 12, 'bold')).pack(anchor='w')
        ttk.Label(status_frame, textvariable=self.task_var, font=('Helvetica', 10)).pack(anchor='w')

        self.progress_bar = ttk.Progressbar(status_frame, orient='horizontal', mode='determinate', length=900)
        self.progress_bar.pack(fill='x', pady=10)

        # 2. Decision History / Strategy Log
        strategy_frame = ttk.LabelFrame(self.root, text="Protocol Decision History", padding=10)
        strategy_frame.pack(fill='both', expand=True, padx=10, pady=5)

        columns = ('time', 'event', 'model', 'details')
        self.tree = ttk.Treeview(strategy_frame, columns=columns, show='headings')
        self.tree.heading('time', text='Timestamp')
        self.tree.heading('event', text='Decision Event')
        self.tree.heading('model', text='Model ID')
        self.tree.heading('details', text='Reasoning / Details')

        self.tree.column('time', width=180)
        self.tree.column('event', width=150)
        self.tree.column('model', width=200)
        self.tree.column('details', width=450)

        self.tree.pack(fill='both', expand=True)

        # 3. Top Model Score Breakdown
        score_frame = ttk.LabelFrame(self.root, text="Active Selection Score Breakdown", padding=10)
        score_frame.pack(fill='x', padx=10, pady=5)

        self.score_details = ttk.Label(score_frame, text="No model currently primary.", font=('Consolas', 10))
        self.score_details.pack(anchor='w')

    def update_loop(self):
        # Update Status
        engine = self.app.engine
        self.state_var.set(f"State: {engine.current_state}")
        self.task_var.set(f"Task: {engine.active_task}")
        self.progress_bar['value'] = engine.progress * 100

        # Update Decision History (Filter for protocol-relevant events)
        for i in self.tree.get_children():
            self.tree.delete(i)

        logs = database.get_recent_activity(limit=50)
        protocol_events = ["Manual Switch", "Auto Switch", "Fallback Triggered", "Circuit Breaker", "Blacklist"]
        for ts, event, model, details in logs:
            if event in protocol_events or "Sync" in event:
                self.tree.insert('', 'end', values=(ts, event, model or "", details or ""))

        # Update Score Breakdown
        if self.app.ranked_models:
            m = self.app.ranked_models[0]
            # Scoring logic: size (60%) + context (20%) - latency (20%)
            # This is a simplification for display
            weights = engine.weights
            size_comp = (m['parameters'] / 100.0) * weights['size']
            ctx_comp = (min(m.get('context_length', 4096), 128000) / 128000.0) * weights['context']
            lat_comp = m['latency'] * weights['latency']

            breakdown_text = (
                f"Primary Model: {m['id']} | Total Score: {m['score']:.2f}\n"
                f"Breakdown: Size Component (+{size_comp:.2f}) | Context Component (+{ctx_comp:.2f}) | Latency Penalty (-{lat_comp:.2f})"
            )
            self.score_details.config(text=breakdown_text)
        else:
            self.score_details.config(text="No models loaded yet.")

        self.root.after(2000, self.update_loop)

    def run(self):
        self.root.mainloop()
