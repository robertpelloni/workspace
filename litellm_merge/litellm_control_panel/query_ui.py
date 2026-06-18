import tkinter as tk
from tkinter import scrolledtext, ttk
import threading
import httpx
import json
import database

class QueryUI:
    def __init__(self, settings):
        self.settings = settings
        self.root = tk.Tk()
        self.root.title("LiteLLM Quick Query")
        self.root.geometry("600x500")

        self.create_widgets()
        self.root.protocol("WM_DELETE_WINDOW", self.root.destroy)

    def create_widgets(self):
        padding = {'padx': 10, 'pady': 5}

        # Prompt Input
        ttk.Label(self.root, text="Enter your prompt:").pack(fill='x', **padding)
        self.prompt_entry = ttk.Entry(self.root)
        self.prompt_entry.pack(fill='x', **padding)
        self.prompt_entry.bind("<Return>", lambda e: self.send_query())

        # Buttons
        btn_frame = ttk.Frame(self.root)
        btn_frame.pack(fill='x', **padding)

        self.send_btn = ttk.Button(btn_frame, text="Send", command=self.send_query)
        self.send_btn.pack(side='left', padx=5)

        ttk.Button(btn_frame, text="Clear", command=self.clear_all).pack(side='left', padx=5)
        ttk.Button(btn_frame, text="Copy Response", command=self.copy_response).pack(side='left', padx=5)

        # Response Area
        ttk.Label(self.root, text="Response:").pack(fill='x', **padding)
        self.response_area = scrolledtext.ScrolledText(self.root, wrap=tk.WORD, state='disabled')
        self.response_area.pack(fill='both', expand=True, **padding)

    def clear_all(self):
        self.prompt_entry.delete(0, tk.END)
        self.response_area.config(state='normal')
        self.response_area.delete(1.0, tk.END)
        self.response_area.config(state='disabled')

    def copy_response(self):
        self.root.clipboard_clear()
        self.root.clipboard_append(self.response_area.get(1.0, tk.END))

    def send_query(self):
        prompt = self.prompt_entry.get()
        if not prompt:
            return

        self.send_btn.config(state='disabled')
        self.response_area.config(state='normal')
        self.response_area.insert(tk.END, f"\n\nUser: {prompt}\n\nAssistant: ")
        self.response_area.config(state='disabled')

        threading.Thread(target=self._perform_query, args=(prompt,), daemon=True).start()

    def _perform_query(self, prompt):
        url = "http://localhost:4000/v1/chat/completions" # Default LiteLLM port
        payload = {
            "model": "free-llm", # The model name we set in config.yaml
            "messages": [{"role": "user", "content": prompt}],
            "stream": True
        }

        try:
            with httpx.stream("POST", url, json=payload, timeout=60.0) as response:
                if response.status_code != 200:
                    self._append_text(f"\nError: {response.status_code}\n")
                    return

                for line in response.iter_lines():
                    if line.startswith("data: "):
                        content = line[6:]
                        if content == "[DONE]":
                            break
                        try:
                            data = json.loads(content)
                            delta = data['choices'][0]['delta'].get('content', '')
                            self._append_text(delta)
                            # Log usage if token counts available (usually only at end)
                            usage = data.get('usage')
                            if usage:
                                database.log_usage("free-llm",
                                                 usage.get('prompt_tokens', 0),
                                                 usage.get('completion_tokens', 0))
                        except:
                            pass
        except Exception as e:
            self._append_text(f"\nFailed to connect to LiteLLM: {e}\n")
        finally:
            self.root.after(0, lambda: self.send_btn.config(state='normal'))

    def _append_text(self, text):
        def inner():
            self.response_area.config(state='normal')
            self.response_area.insert(tk.END, text)
            self.response_area.see(tk.END)
            self.response_area.config(state='disabled')
        self.root.after(0, inner)

    def run(self):
        self.root.mainloop()

if __name__ == "__main__":
    ui = QueryUI({})
    ui.run()
