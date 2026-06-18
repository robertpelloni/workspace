import tkinter as tk
from tkinter import scrolledtext, ttk
import threading

class LogViewer:
    def __init__(self, process_mgr=None, engine=None):
        self.process_mgr = process_mgr
        self.engine = engine
        self.root = tk.Tk()
        title = "FreeLLM Process Logs" if process_mgr else "Model Engine Benchmarking Logs"
        self.root.title(title)
        self.root.geometry("900x700")

        self.create_widgets()

        self.running = True
        self.root.protocol("WM_DELETE_WINDOW", self.on_close)

        # Start log polling
        if self.process_mgr:
            threading.Thread(target=self.poll_logs, daemon=True).start()
        elif self.engine:
            threading.Thread(target=self.poll_engine_logs, daemon=True).start()

    def create_widgets(self):
        # Toolbar
        toolbar = ttk.Frame(self.root, padding=5)
        toolbar.pack(fill='x')

        ttk.Label(toolbar, text="Filter:").pack(side='left', padx=5)
        self.filter_entry = ttk.Entry(toolbar)
        self.filter_entry.pack(side='left', fill='x', expand=True, padx=5)
        self.filter_entry.bind("<KeyRelease>", lambda e: self.apply_filter())

        ttk.Button(toolbar, text="Clear", command=self.clear_logs).pack(side='right', padx=5)
        ttk.Button(toolbar, text="Copy All", command=self.copy_all).pack(side='right', padx=5)

        # Log Area
        self.log_area = scrolledtext.ScrolledText(self.root, wrap=tk.WORD)
        self.log_area.pack(fill='both', expand=True)
        self.full_logs = []

    def clear_logs(self):
        self.full_logs = []
        self.log_area.delete(1.0, tk.END)

    def copy_all(self):
        self.root.clipboard_clear()
        self.root.clipboard_append(self.log_area.get(1.0, tk.END))

    def apply_filter(self):
        filter_text = self.filter_entry.get().lower()
        self.log_area.delete(1.0, tk.END)
        for line in self.full_logs:
            if filter_text in line.lower():
                self.log_area.insert(tk.END, line)
        self.log_area.see(tk.END)

    def on_close(self):
        self.running = False
        self.root.destroy()

    def poll_logs(self):
        last_count = 0
        while self.running:
            if self.process_mgr.process:
                current_len = len(self.process_mgr.log_buffer)
                if current_len > last_count:
                    new_lines = self.process_mgr.log_buffer[last_count:current_len]
                    for line in new_lines:
                        self.root.after(0, self.append_log, line)
                    last_count = current_len
                elif current_len < last_count:
                    # Buffer rolled over
                    last_count = 0
            
            import time
            time.sleep(0.5)

    def poll_engine_logs(self):
        """Polls the ModelEngine log queue for new entries."""
        import time
        last_log_id = -1
        while self.running:
            if self.engine:
                # Thread-safe snapshot of the queue
                current_logs = list(self.engine.log_queue)
                for log_id, line in current_logs:
                    if log_id > last_log_id:
                        self.root.after(0, self.append_log, line)
                        last_log_id = log_id
            time.sleep(0.5)

    def append_log(self, message):
        self.full_logs.append(message)
        # Apply filter if active
        filter_text = self.filter_entry.get().lower()
        if not filter_text or filter_text in message.lower():
            self.log_area.insert(tk.END, message)
            self.log_area.see(tk.END)

    def run(self):
        self.root.mainloop()
