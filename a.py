import customtkinter as ctk



class App(ctk.CTk):
    def __init__(self):
        super().__init__()

        self.state_check_boxes = []
        self.state_var_check_boxes = []

        self.geometry("1920x1080")
        self.title("Find chepdv")

        # создание таблицы состоянии
        self.state_check_frame = ctk.CTkFrame(master=self, fg_color='#00CED1')
        self.state_check_frame.grid(row=0, column=0, padx=20, pady=20, sticky="nw")
        self.state_var_check_boxes, self.state_check_boxes = self.createStateCheckBox(self.state_check_frame, "Начальные условия", (0, 0))
        self.state_var_check_boxes, self.state_check_boxes = self.createStateCheckBox(self.state_check_frame, "Входные данные", (1, 0))

        #ввод начальных состояний
        self.state_frame = ctk.CTkFrame(master=self, fg_color='#808080', height=300, width=250)
        self.state_frame.grid(row=1, column=0, padx=20, pady=20, sticky="nw")

        self.state_entry = ctk.CTkEntry(master=self.state_frame)
        self.state_entry.grid(row=1, column=0, padx=20, pady=20, sticky="nw")

    def createStateCheckBox(self, master, text, position):
        checkbox_var = ctk.IntVar()
        checkbox = ctk.CTkCheckBox(master, text=text, variable=checkbox_var, text_color_disabled='black', fg_color='green')
        checkbox.configure(state="disabled")
        checkbox.grid(row=position[0], column=position[1], padx=20, pady=20, sticky='w')
        return [checkbox_var, checkbox]
