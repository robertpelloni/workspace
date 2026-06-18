import tkinter as tk
from tkinter import ttk
import database

class MonitoringUI:
    def __init__(self, app_instance=None):
        self.app = app_instance
        self.root = tk.Tk()
        self.root.title("LiteLLM Control Panel - Autonomous Monitoring")
        self.root.geometry("1000x700")

        self.notebook = ttk.Notebook(self.root)
        self.notebook.pack(fill='both', expand=True)

        self.create_activity_tab()
        self.create_performance_tab()
        self.create_load_tab()

        self.refresh_data()
        self.root.protocol("WM_DELETE_WINDOW", self.root.destroy)

    def create_activity_tab(self):
        tab = ttk.Frame(self.notebook)
        self.notebook.add(tab, text="Activity Log")

        columns = ('time', 'event', 'model', 'details')
        self.activity_tree = ttk.Treeview(tab, columns=columns, show='headings')
        self.activity_tree.heading('time', text='Timestamp')
        self.activity_tree.heading('event', text='Event Type')
        self.activity_tree.heading('model', text='Model ID')
        self.activity_tree.heading('details', text='Details')

        self.activity_tree.column('time', width=180)
        self.activity_tree.column('event', width=150)
        self.activity_tree.column('model', width=250)
        self.activity_tree.column('details', width=400)

        scrollbar = ttk.Scrollbar(tab, orient='vertical', command=self.activity_tree.yview)
        self.activity_tree.configure(yscrollcommand=scrollbar.set)

        self.activity_tree.pack(side='left', fill='both', expand=True, padx=5, pady=5)
        scrollbar.pack(side='right', fill='y', pady=5)

    def create_performance_tab(self):
        tab = ttk.Frame(self.notebook)
        self.notebook.add(tab, text="Performance Metrics")

        # Summary Frame
        summary_frame = ttk.LabelFrame(tab, text="24h System Summary", padding=10)
        summary_frame.pack(fill='x', padx=10, pady=10)

        self.probes_var = tk.StringVar(value="Total Probes: 0")
        self.ttft_var = tk.StringVar(value="Avg TTFT: 0.00s")
        self.success_var = tk.StringVar(value="Success Rate: 0.0%")
        self.error_rate_var = tk.StringVar(value="Protocol Errors: 0.0%")

        ttk.Label(summary_frame, textvariable=self.probes_var, font=('Helvetica', 10)).grid(row=0, column=0, padx=10)
        ttk.Label(summary_frame, textvariable=self.ttft_var, font=('Helvetica', 10)).grid(row=0, column=1, padx=10)
        ttk.Label(summary_frame, textvariable=self.success_var, font=('Helvetica', 10)).grid(row=0, column=2, padx=10)
        ttk.Label(summary_frame, textvariable=self.error_rate_var, font=('Helvetica', 10)).grid(row=0, column=3, padx=10)

        # Provider Breakdown
        breakdown_frame = ttk.LabelFrame(tab, text="Provider Reliability", padding=10)
        breakdown_frame.pack(fill='both', expand=True, padx=10, pady=10)

        columns = ('provider', 'avg_lat', 'success')
        self.perf_tree = ttk.Treeview(breakdown_frame, columns=columns, show='headings')
        self.perf_tree.heading('provider', text='Provider')
        self.perf_tree.heading('avg_lat', text='Avg Latency (s)')
        self.perf_tree.heading('success', text='Success Rate (%)')

        self.perf_tree.pack(fill='both', expand=True)

    def create_load_tab(self):
        tab = ttk.Frame(self.notebook)
        self.notebook.add(tab, text="Load Analysis")

        load_summary = ttk.Frame(tab, padding=10)
        load_summary.pack(fill='x')

        self.qpm_var = tk.StringVar(value="Queries/Min: 0")
        self.tps_var = tk.StringVar(value="Tokens/Sec: 0")
        ttk.Label(load_summary, textvariable=self.qpm_var, font=('Helvetica', 12, 'bold')).pack(side='left', padx=20)
        ttk.Label(load_summary, textvariable=self.tps_var, font=('Helvetica', 12, 'bold')).pack(side='left', padx=20)

        chart_frame = ttk.LabelFrame(tab, text="Activity Chart (Last 60 mins)", padding=10)
        chart_frame.pack(fill='both', expand=True, padx=10, pady=10)

        self.canvas = tk.Canvas(chart_frame, bg='black', height=300)
        self.canvas.pack(fill='both', expand=True)

    def draw_load_chart(self, history):
        self.canvas.delete("all")
        w = self.canvas.winfo_width()
        h = self.canvas.winfo_height()
        if w < 10 or h < 10: return

        if not history:
            self.canvas.create_text(w/2, h/2, text="Collecting load data...", fill='white')
            return

        max_qpm = max([x[1] for x in history] + [1])
        max_tps = max([x[2] for x in history] + [1])

        points_qpm = []
        points_tps = []

        step = w / 60
        for i, (ts, qpm, tps) in enumerate(reversed(history)):
            x = w - (i * step)
            y_qpm = h - (qpm / max_qpm * (h - 20)) - 10
            y_tps = h - (tps / max_tps * (h - 20)) - 10
            points_qpm.extend([x, y_qpm])
            points_tps.extend([x, y_tps])

        if len(points_qpm) > 3:
            self.canvas.create_line(points_qpm, fill='cyan', width=2, smooth=True)
        if len(points_tps) > 3:
            self.canvas.create_line(points_tps, fill='orange', width=2, smooth=True)

        self.canvas.create_text(50, 20, text="QPM (Cyan)", fill='cyan', anchor='w')
        self.canvas.create_text(50, 40, text="TPS (Orange)", fill='orange', anchor='w')

    def refresh_data(self):
        # 1. Activity Log
        for i in self.activity_tree.get_children():
            self.activity_tree.delete(i)

        logs = database.get_recent_activity(limit=100)
        for ts, event, model, details in logs:
            self.activity_tree.insert('', 'end', values=(ts, event, model or "", details or ""))

        # 2. Performance Summary
        perf = database.get_performance_summary()
        self.probes_var.set(f"Total Probes: {perf['total_probes']}")
        self.ttft_var.set(f"Avg TTFT: {perf['avg_ttft']:.2f}s")
        self.success_var.set(f"Success Rate: {perf['success_rate']:.1f}%")

        protocol_metrics = database.get_protocol_health_metrics()
        self.error_rate_var.set(f"Protocol Errors: {protocol_metrics['error_rate']:.1f}%")

        for i in self.perf_tree.get_children():
            self.perf_tree.delete(i)

        for prov, lat, succ in perf['providers']:
            self.perf_tree.insert('', 'end', values=(prov, f"{lat:.3f}", f"{succ:.1f}%"))

        # 3. Load Analysis
        load_history = database.get_load_history(limit=60)
        if load_history:
            latest = load_history[0]
            self.qpm_var.set(f"Queries/Min: {latest[1]:.1f}")
            self.tps_var.set(f"Tokens/Sec: {latest[2]:.1f}")

        self.draw_load_chart(load_history)

        # Schedule next refresh (more frequent for real-time oversight)
        self.root.after(3000, self.refresh_data)

    def run(self):
        self.root.mainloop()

if __name__ == "__main__":
    ui = MonitoringUI()
    ui.run()
