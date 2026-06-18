import tkinter as tk
from tkinter import ttk
import threading
import database


class DashboardUI:
    def __init__(self, app_instance):
        self.app = app_instance
        self.root = tk.Tk()
        self.root.title("FreeLLM - Dashboard")
        self.root.geometry("1000x600")
        self.create_widgets()
        self.running = True
        self.root.protocol("WM_DELETE_WINDOW", self.on_close)
        self.update_loop()

    def on_close(self):
        self.running = False
        self.root.destroy()

    def create_widgets(self):
        header = ttk.Frame(self.root, padding=10)
        header.pack(fill='x')
        ttk.Label(header, text="Model Performance & Rankings",
                  font=('Helvetica', 14, 'bold')).pack(side='left')
        self.usage_label = ttk.Label(header, text="Usage: 0 queries (0 tokens)",
                                     font=('Helvetica', 10))
        self.usage_label.pack(side='right', padx=20)

        columns = ('id', 'provider', 'parameters', 'latency', 'score', 'actions')
        self.tree = ttk.Treeview(self.root, columns=columns, show='headings')
        self.tree.heading('id', text='Model ID')
        self.tree.heading('provider', text='Provider')
        self.tree.heading('parameters', text='Params (B)')
        self.tree.heading('latency', text='Latency (s)')
        self.tree.heading('score', text='Score')
        self.tree.heading('actions', text='Status')
        self.tree.column('id', width=300)
        self.tree.column('provider', width=100)
        self.tree.column('parameters', width=100)
        self.tree.column('latency', width=100)
        self.tree.column('score', width=100)
        self.tree.column('actions', width=200)
        self.tree.pack(fill='both', expand=True, padx=10, pady=10)

        footer = ttk.Frame(self.root, padding=10)
        footer.pack(fill='x')
        ttk.Button(footer, text="Refresh Now",
                   command=lambda: self.app.refresh_now(None, None)).pack(side='right')

        self.context_menu = tk.Menu(self.tree, tearoff=0)
        self.context_menu.add_command(label="Switch to Model", command=self.action_switch)
        self.context_menu.add_command(label="Skip (24h)", command=self.action_skip)
        self.context_menu.add_command(label="Blacklist", command=self.action_blacklist)
        self.tree.bind("<Button-3>", self.show_context_menu)

    def show_context_menu(self, event):
        item = self.tree.identify_row(event.y)
        if item:
            self.tree.selection_set(item)
            self.context_menu.post(event.x_root, event.y_root)

    def action_switch(self):
        selected = self.tree.item(self.tree.selection())['values']
        if selected:
            self.app.select_model(selected[0], selected[1])(None, None)

    def action_skip(self):
        selected = self.tree.item(self.tree.selection())['values']
        if selected:
            self.app.skip_model(selected[0])(None, None)

    def action_blacklist(self):
        selected = self.tree.item(self.tree.selection())['values']
        if selected:
            self.app.blacklist_model(selected[0])(None, None)

    def update_loop(self):
        if not self.running:
            return
        queries, prompts, completions = database.get_total_usage()
        prompts = prompts or 0
        completions = completions or 0
        self.usage_label.config(text=f"Usage: {queries} queries ({prompts + completions} tokens)")
        for i in self.tree.get_children():
            self.tree.delete(i)
        for idx, m in enumerate(self.app.ranked_models):
            status = "Top Ranked" if idx == 0 else ""
            self.tree.insert('', 'end', values=(
                m['id'], m['provider'],
                f"{m['parameters']}B", f"{m['latency']:.3f}",
                f"{m['score']:.2f}", status
            ))
        self.root.after(5000, self.update_loop)

    def run(self):
        self.root.mainloop()


class LeaderboardUI:
    def __init__(self, app_instance):
        self.app = app_instance
        self.root = tk.Tk()
        self.root.title("Model Leaderboard - Reliability Over Time")
        self.root.geometry("1100x700")
        self.create_widgets()
        self.running = True
        self.root.protocol("WM_DELETE_WINDOW", self.on_close)
        self.update_loop()

    def on_close(self):
        self.running = False
        self.root.destroy()

    def create_widgets(self):
        # Sort controls
        controls = ttk.Frame(self.root, padding=10)
        controls.pack(fill='x')
        ttk.Label(controls, text="Sort by:",
                  font=('Helvetica', 10, 'bold')).pack(side='left')
        self.sort_var = tk.StringVar(value='score_best')
        sort_options = [
            ('Best Score', 'score_best'),
            ('Avg Score', 'score_avg'),
            ('Avg Latency', 'avg_latency'),
            ('P50 Latency', 'p50_latency'),
            ('Min Latency', 'min_latency'),
            ('Uptime %', 'uptime_pct'),
            ('Total Successes', 'total_successes'),
        ]
        for text, value in sort_options:
            ttk.Radiobutton(controls, text=text, variable=self.sort_var,
                            value=value, command=self.refresh_data).pack(side='left', padx=4)
        ttk.Button(controls, text="Refresh",
                   command=self.refresh_data).pack(side='right')

        # Summary label
        self.summary_label = ttk.Label(self.root, text="",
                                       font=('Helvetica', 9))
        self.summary_label.pack(fill='x', padx=10)

        # Table
        columns = ('rank', 'id', 'provider', 'params', 'avg_lat', 'p50_lat',
                   'min_lat', 'uptime', 'probes', 'successes', 'failures',
                   'score_best', 'score_avg', 'consec_ok', 'last_ok')
        self.tree = ttk.Treeview(self.root, columns=columns, show='headings')
        headings = {
            'rank': ('#', 30), 'id': ('Model ID', 250),
            'provider': ('Provider', 80), 'params': ('Params', 60),
            'avg_lat': ('Avg(s)', 65), 'p50_lat': ('P50(s)', 65),
            'min_lat': ('Min(s)', 65), 'uptime': ('Up%', 50),
            'probes': ('Probes', 50), 'successes': ('OK', 40),
            'failures': ('Fail', 40), 'score_best': ('Best', 55),
            'score_avg': ('Avg', 55), 'consec_ok': ('Streak', 50),
            'last_ok': ('Last Success', 130),
        }
        for col, (heading, width) in headings.items():
            self.tree.heading(col, text=heading)
            self.tree.column(col, width=width, minwidth=30)

        scrollbar = ttk.Scrollbar(self.root, orient='vertical',
                                  command=self.tree.yview)
        self.tree.configure(yscrollcommand=scrollbar.set)
        self.tree.pack(side='left', fill='both', expand=True,
                       padx=(10, 0), pady=10)
        scrollbar.pack(side='right', fill='y', pady=10)

        # Right-click menu
        self.context_menu = tk.Menu(self.tree, tearoff=0)
        self.context_menu.add_command(label="View Probe History",
                                      command=self.action_probe_history)
        self.tree.bind("<Button-3>", self.show_context_menu)

    def show_context_menu(self, event):
        item = self.tree.identify_row(event.y)
        if item:
            self.tree.selection_set(item)
            self.context_menu.post(event.x_root, event.y_root)

    def action_probe_history(self):
        selected = self.tree.item(self.tree.selection())
        if not selected or not selected.get('values'):
            return
        model_id = selected['values'][1]
        history = database.get_model_probe_history(model_id, limit=30)
        if not history:
            return
        win = tk.Toplevel(self.root)
        win.title("Probe History: " + str(model_id))
        win.geometry("700x400")
        text = tk.Text(win, font=('Consolas', 9))
        text.pack(fill='both', expand=True)
        hdr = "{:<22} {:>8} {:>4} {:>6} {:>8}".format(
            "Timestamp", "Latency", "OK", "Code", "Score")
        text.insert('end', hdr + '\n')
        text.insert('end', '-' * 55 + '\n')
        for h in history:
            ts = str(h['timestamp'])[:19] if h['timestamp'] else ''
            lat = "{:.3f}".format(h['latency']) if h['latency'] else '---'
            ok = 'Y' if h['success'] else 'N'
            code = str(h['error_code'] or '')
            score = "{:.1f}".format(h['score']) if h.get('score') else ''
            line = "{:<22} {:>8} {:>4} {:>6} {:>8}".format(
                ts, lat, ok, code, score)
            text.insert('end', line + '\n')
        text.config(state='disabled')

    def refresh_data(self):
        for i in self.tree.get_children():
            self.tree.delete(i)
        sort_by = self.sort_var.get()
        models = database.get_leaderboard(sort_by=sort_by, limit=50)
        for rank, m in enumerate(models, 1):
            last_ok = str(m.get('last_success', ''))[:19] if m.get('last_success') else 'never'
            self.tree.insert('', 'end', values=(
                rank,
                m['id'],
                m['provider'],
                "{}B".format(m.get('parameters', 0)),
                "{:.3f}".format(m.get('avg_latency', 0)),
                "{:.3f}".format(m.get('p50_latency', 0)),
                "{:.3f}".format(m.get('min_latency', 999)),
                "{}%".format(m.get('uptime_pct', 0)),
                m.get('total_probes', 0),
                m.get('successes', 0),
                m.get('failures', 0),
                "{:.1f}".format(m.get('score_best', 0)),
                "{:.1f}".format(m.get('score_avg', 0)),
                m.get('consec_successes', 0),
                last_ok,
            ))
        self.summary_label.config(
            text="{} models with probe data | Sorted by: {}".format(
                len(models), sort_by))

    def update_loop(self):
        if not self.running:
            return
        self.refresh_data()
        self.root.after(15000, self.update_loop)

    def run(self):
        self.root.mainloop()
