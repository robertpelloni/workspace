import tkinter as tk
from tkinter import scrolledtext, ttk
import threading
import httpx
import json
import asyncio

class ComparisonUI:
    def __init__(self, settings, models):
        self.settings = settings
        self.models = models[:3]  # Compare top 3 models
        self.root = tk.Tk()
        self.root.title("LiteLLM Model Comparison")
        self.root.geometry("1200x700")

        self.create_widgets()
        self.root.protocol("WM_DELETE_WINDOW", self.root.destroy)

    def create_widgets(self):
        padding = {'padx': 10, 'pady': 5}

        # Prompt Input
        input_frame = ttk.Frame(self.root)
        input_frame.pack(fill='x', **padding)

        ttk.Label(input_frame, text="Enter your prompt:").pack(side='left', padx=5)
        self.prompt_entry = ttk.Entry(input_frame)
        self.prompt_entry.pack(side='left', fill='x', expand=True, padx=5)
        self.prompt_entry.bind("<Return>", lambda e: self.send_query())

        self.send_btn = ttk.Button(input_frame, text="Compare", command=self.send_query)
        self.send_btn.pack(side='left', padx=5)

        # Comparison Area
        self.comparison_frame = ttk.Frame(self.root)
        self.comparison_frame.pack(fill='both', expand=True, **padding)

        self.response_areas = []
        for i, model in enumerate(self.models):
            frame = ttk.LabelFrame(self.comparison_frame, text=f"{model['id']} ({model['provider']})")
            frame.grid(row=0, column=i, sticky='nsew', padx=5)
            self.comparison_frame.columnconfigure(i, weight=1)
            self.comparison_frame.rowconfigure(0, weight=1)

            area = scrolledtext.ScrolledText(frame, wrap=tk.WORD, state='disabled', width=30)
            area.pack(fill='both', expand=True, padx=5, pady=5)
            self.response_areas.append(area)

    def send_query(self):
        prompt = self.prompt_entry.get()
        if not prompt:
            return

        self.send_btn.config(state='disabled')
        for area in self.response_areas:
            area.config(state='normal')
            area.delete(1.0, tk.END)
            area.config(state='disabled')

        threading.Thread(target=self._run_async_queries, args=(prompt,), daemon=True).start()

    def _run_async_queries(self, prompt):
        loop = asyncio.new_event_loop()
        asyncio.set_event_loop(loop)
        loop.run_until_complete(self._perform_comparisons(prompt))
        self.root.after(0, lambda: self.send_btn.config(state='normal'))

    async def _perform_comparisons(self, prompt):
        tasks = []
        for i, model in enumerate(self.models):
            tasks.append(self._stream_response(i, model['id'], prompt))
        await asyncio.gather(*tasks)

    async def _stream_response(self, index, model_id, prompt):
        url = "http://localhost:4000/v1/chat/completions"
        payload = {
            "model": model_id,
            "messages": [{"role": "user", "content": prompt}],
            "stream": True
        }

        try:
            async with httpx.AsyncClient() as client:
                async with client.stream("POST", url, json=payload, timeout=60.0) as response:
                    if response.status_code != 200:
                        self._append_text(index, f"\nError: {response.status_code}\n")
                        return

                    async for line in response.aiter_lines():
                        if line.startswith("data: "):
                            content = line[6:]
                            if content == "[DONE]":
                                break
                            try:
                                data = json.loads(content)
                                delta = data['choices'][0]['delta'].get('content', '')
                                self._append_text(index, delta)
                            except:
                                pass
        except Exception as e:
            self._append_text(index, f"\nFailed to connect to LiteLLM: {e}\n")

    def _append_text(self, index, text):
        def inner():
            area = self.response_areas[index]
            area.config(state='normal')
            area.insert(tk.END, text)
            area.see(tk.END)
            area.config(state='disabled')
        self.root.after(0, inner)

    def run(self):
        self.root.mainloop()
