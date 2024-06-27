import customtkinter as ctk



class App(ctk.CTk):
    def __init__(self):
        super().__init__()
        self.geometry("1920x1080")
        self.title("Find chepdv")
        self.string_state_frame = dict()
        self.info_state_labels = dict()
        self.best_value_state = dict()

        #ввод начальных состояний
        self.state_frame = ctk.CTkFrame(master=self, fg_color='#808080', height=300, width=250)
        self.state_frame.grid(row=0, column=0, padx=20, pady=20, sticky="nw")

        self.createStateLabel('Шанс мутации', 0)
        self.createStateLabel('Шанс cкрещивания', 2)
        self.createStateLabel('Максимальное количество эпох', 4)

        #информация о начальных состояних
        self.state_frame_info = ctk.CTkFrame(master=self, fg_color='#808080', height=300, width=250)
        self.state_frame_info.grid(row=1, column=0, padx=20, pady=20, sticky="n")

        self.createInfoStateLabel("Шанс мутации: error", 0)
        self.createInfoStateLabel("Шанс cкрещивания: error", 1)
        self.createInfoStateLabel("Максимальное количество эпох: error", 2)

        for i in self.info_state_labels.keys():
            print(i)


    def createInfoStateLabel(self, text, index_row):
        state_label_info = ctk.CTkLabel(master=self.state_frame_info, width=100, text=text)
        state_label_info.grid(row=index_row, column=0, padx=(20, 20), sticky='w')
        self.info_state_labels[text[:-7]] = state_label_info

    def createStateLabel(self, text, index_row):
        self.string_state_frame[text] = ctk.StringVar()
        state_label = ctk.CTkLabel(master=self.state_frame, text=text)
        state_label.grid(row=index_row, column=0, padx=15, pady=3, sticky="we")
        state_entry = ctk.CTkEntry(master=self.state_frame, textvariable=self.string_state_frame[text])
        state_entry.grid(row=index_row+1, column=0, padx=10, pady=3, sticky="we")
        state_entry.bind('<Return>', lambda event: self.handle_enter(event, text))

    def handle_enter(self, event, extra_arg):
        text = self.string_state_frame[extra_arg].get()
        try:
            number = float(text)
            if extra_arg == "Шанс мутации" or extra_arg == "Шанс cкрещивания":
                if 0 <= number <= 1:
                    self.info_state_labels[extra_arg].configure(text=f'{extra_arg}:  {number*100} %')
                    self.best_value_state[extra_arg] = number
            else:
                if 0 <= number:
                    self.info_state_labels[extra_arg].configure(text=f'{extra_arg}:  {number}')
                    self.best_value_state[extra_arg] = number
        except ValueError:
            pass
        self.string_state_frame[extra_arg].set("")
