import tkinter as tk
from tkinter import ttk
import database
import time

class ExecutionDashboardUI:
    def __init__(self, app_instance):
        self.app = app_instance
        self.root = tk.Tk()
        self.root.title("LiteLLM Control Panel - Protocol Execution")
        self.root.geometry("900x600")

        self.create_widgets()
        self.refresh_data()
        self.root.protocol("WM_DELETE_WINDOW", self.root.destroy)

    def create_widgets(self):
        padding = {'padx': 20, 'pady': 10}

        # 1. Health Summary
        summary_frame = ttk.LabelFrame(self.root, text="Protocol Health Metrics (24h)", padding=10)
        summary_frame.pack(fill='x', padx=10, pady=5)

        self.error_rate_var = tk.StringVar(value="Error Rate: 0.0%")
        self.avg_sync_var = tk.StringVar(value="Avg Sync Time: 0.0s")
        self.sync_count_var = tk.StringVar(value="Total Cycles: 0")

        ttk.Label(summary_frame, textvariable=self.error_rate_var, font=('Helvetica', 12, 'bold')).grid(row=0, column=0, padx=30)
        ttk.Label(summary_frame, textvariable=self.avg_sync_var, font=('Helvetica', 12)).grid(row=0, column=1, padx=30)
        ttk.Label(summary_frame, textvariable=self.sync_count_var, font=('Helvetica', 12)).grid(row=0, column=2, padx=30)

        # 2. Execution Timeline / Error Log
        logs_frame = ttk.LabelFrame(self.root, text="Recent Protocol Events", padding=10)
        logs_frame.pack(fill='both', expand=True, padx=10, pady=5)

        columns = ('time', 'event', 'details')
        self.tree = ttk.Treeview(logs_frame, columns=columns, show='headings')
        self.tree.heading('time', text='Timestamp')
        self.tree.heading('event', text='Event')
        self.tree.heading('details', text='Details / Duration')

        self.tree.column('time', width=180)
        self.tree.column('event', width=150)
        self.tree.column('details', width=500)

        self.tree.pack(fill='both', expand=True)

        # 3. Execution Duration Chart (Canvas)
        chart_frame = ttk.LabelFrame(self.root, text="Protocol Sync Duration (Last 20 cycles)", padding=10)
        chart_frame.pack(fill='x', padx=10, pady=5)

        self.canvas = tk.Canvas(chart_frame, bg='black', height=150)
        self.canvas.pack(fill='x', expand=True)

    def draw_duration_chart(self, logs):
        self.canvas.delete("all")
        w = self.canvas.winfo_width()
        h = self.canvas.winfo_height()
        if w < 10 or h < 10: return

        durations = []
        import re
        for _, event, _, details in logs:
            if event == "Protocol Sync":
                match = re.search(r'took (\d+\.?\d*)s', details)
                if match:
                    durations.append(float(match.group(1)))

        if not durations:
            self.canvas.create_text(w/2, h/2, text="No sync data yet", fill='white')
            return

        durations = durations[:20]
        max_dur = max(durations + [5.0])
        step = w / 20

        points = []
        for i, dur in enumerate(reversed(durations)):
            x = i * step + 10
            y = h - (dur / max_dur * (h - 20)) - 10
            points.extend([x, y])
            self.canvas.create_rectangle(x-2, y-2, x+2, y+2, fill='green')

        if len(points) > 3:
            self.canvas.create_line(points, fill='lime', width=2)

        self.canvas.create_text(10, 10, text=f"Max: {max_dur:.1f}s", fill='gray', anchor='nw')

    def refresh_data(self):
        # 1. Summary
        metrics = database.get_protocol_health_metrics()
        self.error_rate_var.set(f"Error Rate: {metrics['error_rate']:.1f}%")
        self.avg_sync_var.set(f"Avg Sync Time: {metrics['avg_sync_duration']:.1f}s")
        self.sync_count_var.set(f"Total Cycles: {metrics['sync_count']}")

        # 2. Table
        for i in self.tree.get_children():
            self.tree.delete(i)

        all_logs = database.get_recent_activity(limit=100)
        protocol_events = ["Protocol Sync", "Protocol Error", "Health Check Failure", "Fallback Triggered"]
        relevant_logs = []
        for ts, event, model, details in all_logs:
            if event in protocol_events:
                self.tree.insert('', 'end', values=(ts, event, details or ""))
                relevant_logs.append((ts, event, model, details))

        # 3. Chart
        self.draw_duration_chart(relevant_logs)

        self.root.after(5000, self.refresh_data)

    def run(self):
        self.root.mainloop()
