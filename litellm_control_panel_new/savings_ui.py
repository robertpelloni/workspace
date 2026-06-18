import tkinter as tk
from tkinter import ttk
import database

class SavingsDashboardUI:
    def __init__(self, app_instance=None):
        self.app = app_instance
        self.root = tk.Tk()
        self.root.title("FreeLLM - Cost Savings")
        self.root.geometry("800x500")

        self.create_widgets()
        self.refresh_data()

    def create_widgets(self):
        padding = {'padx': 20, 'pady': 10}

        # Header
        header = ttk.Frame(self.root, padding=10)
        header.pack(fill='x')

        ttk.Label(header, text="Estimated Cost Savings",
                  font=('Helvetica', 16, 'bold')).pack(side='left')

        self.total_saved_label = ttk.Label(header, text="Total Saved: $0.00",
                                          font=('Helvetica', 14, 'bold'), foreground='green')
        self.total_saved_label.pack(side='right')

        # Description
        ttk.Label(self.root, text="Savings are calculated by comparing usage of free models against their paid counterparts' API rates.",
                  font=('Helvetica', 9, 'italic')).pack(fill='x', padx=20)

        # Savings Table
        columns = ('model', 'savings', 'tokens')
        self.tree = ttk.Treeview(self.root, columns=columns, show='headings')
        self.tree.heading('model', text='Model ID')
        self.tree.heading('savings', text='Estimated Savings (USD)')
        self.tree.heading('tokens', text='Total Tokens')

        self.tree.column('model', width=400)
        self.tree.column('savings', width=200, anchor='e')
        self.tree.column('tokens', width=150, anchor='e')

        self.tree.pack(fill='both', expand=True, padx=20, pady=10)

        # Footer
        footer = ttk.Frame(self.root, padding=10)
        footer.pack(fill='x')

        ttk.Button(footer, text="Refresh", command=self.refresh_data).pack(side='right', padx=5)
        ttk.Button(footer, text="Close", command=self.root.destroy).pack(side='right', padx=5)

    def refresh_data(self):
        # Clear tree
        for i in self.tree.get_children():
            self.tree.delete(i)

        total, breakdown = database.get_savings_summary()
        self.total_saved_label.config(text=f"Total Saved: ${total:.4f}")

        for model_id, savings, tokens in breakdown:
            self.tree.insert('', 'end', values=(
                model_id,
                f"${savings:.4f}",
                f"{tokens:,}"
            ))

    def run(self):
        self.root.mainloop()

if __name__ == "__main__":
    ui = SavingsDashboardUI()
    ui.run()
