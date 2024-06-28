import customtkinter as ctk
import csv
from tkinter import filedialog
import random
import matplotlib.pyplot as plt 
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2Tk
import numpy as np
import math
from PIL import Image, ImageTk

class MyNavigationToolbar2Tk(NavigationToolbar2Tk):
    def __init__(self, canvas, window):
        super().__init__(canvas, window)

    def pack(self, *args, **kwargs):
        pass

    def grid(self, *args, **kwargs):
        super().grid(*args, **kwargs)

class App(ctk.CTk):
    def __init__(self):
        super().__init__()
        self.geometry("1920x1080")
        self.title("Find roof")
        self.resizable(False, False)
        self.string_state_frame = dict()
        self.info_state_labels = dict()
        self.best_value_state = dict()
        self.points = set()
        self.points_button_delete = []

        self.general_left_frame = ctk.CTkFrame(master=self,width=620, height=950, fg_color='green')
        self.general_left_frame.grid(row=0, column=0, rowspan=4)
        # #ввод начальных состояний
        # self.state_frame = ctk.CTkFrame(master=self, fg_color='#808080', height=300, width=250)
        # self.state_frame.grid(row=0, column=0, padx=20, pady=20, sticky="nw")
        #
        # self.createStateLabel('Шанс мутации', 0)
        # self.createStateLabel('Шанс cкрещивания', 2)
        # self.createStateLabel('Максимальное количество эпох', 4)
        #
        # #информация о начальных состояних
        # self.state_frame_info = ctk.CTkFrame(master=self, fg_color='#808080', height=90, width=270)
        # self.state_frame_info.grid(row=1, column=0, padx=20, pady=20, sticky="nw")
        # self.state_frame_info.grid_propagate(False)
        #
        # self.createInfoStateLabel("Шанс мутации: error", 0)
        # self.createInfoStateLabel("Шанс cкрещивания: error", 1)
        # self.createInfoStateLabel("Максимальное количество эпох: error", 2)
        #
        # #Добавление точек
        # self.frame_points = ctk.CTkScrollableFrame(master=self, width=250, height=200)
        # self.frame_points.grid(row=0, column=1, padx=20, pady=20, sticky='nw')
        # self.createAddPointLabel()
        # self.frame_points.bind("<Button-4>",
        #                                 lambda e: self.frame_points._parent_canvas.yview("scroll", -1, "units"))
        # self.frame_points.bind("<Button-5>",
        #                                 lambda e: self.frame_points._parent_canvas.yview("scroll", 1, "units"))

        #График
        self.x_values = []
        self.y_values = []

        self.figure, self.ax = plt.subplots()
        self.ax.set_xlim(0, 10)
        self.ax.set_ylim(0, 4)
        self.canvas = FigureCanvasTkAgg(self.figure, master=self)
        self.canvas.get_tk_widget().grid(row=1, column=3, sticky="nsew")

        self.toolbar = MyNavigationToolbar2Tk(self.canvas, self)
        self.toolbar.update()
        self.toolbar.grid(row=2, column=3, sticky="ew")

        #Кнопки графика
        self.graphic_frame = ctk.CTkFrame(master=self, width=100, height=50, fg_color='white')
        self.graphic_frame.grid(row=3, column=3, pady=0, sticky='nsew')
        self.createGraphicButtons()

        #Информационное табло
        self.createInformationTable()

        #Выбор способа мутации
        # self.choose_method_frame = ctk.CTkFrame(master=self, width=100, height=100, fg_color='green')
        # self.choose_method_frame.grid(row=2, column=1, rowspan=2, columnspan=2, padx=20, pady=20, sticky="n")


    def createMethodlabel(self):
        pass
    def createInformationTable(self):
        information_table_frame = ctk.CTkFrame(master=self, height=900, width=600, fg_color='white')
        information_table_frame.grid(row=0, column=4, rowspan=5, padx=20, pady=20, sticky="nw")
        information_table_lable = ctk.CTkLabel(master=information_table_frame, text="Панель информации", width=600,
                                                text_color='black', font=("Arial", 20), fg_color="white")
        information_table_lable.grid(row=0, column=0, padx=20, pady=20, sticky="nw")
        self.information_table = ctk.CTkScrollableFrame(master=information_table_frame, height=800, width=590,
                                                        fg_color='white', border_width=2)
        self.information_table.bind("<Button-4>", lambda e: self.information_table._parent_canvas.yview("scroll", -1, "units"))
        self.information_table.bind("<Button-5>", lambda e: self.information_table._parent_canvas.yview("scroll", 1, "units"))

        self.information_table.grid(row=1, column=0, padx=20, pady=20, sticky="nw")


    def addInformationEvent(self, message):
        count = len(self.information_table.winfo_children())
        inform_message = ctk.CTkLabel(master=self.information_table, text="#log " + str(count+1) + ": " + message)
        inform_message.grid(row=count, column=0, padx=0, pady=0,
                            sticky="nw", columnspan=2)
        self.information_table._parent_canvas.yview("scroll", 1, "units")


    def createGraphicButtons(self):
        prev_image = ctk.CTkImage(Image.open("GUI/images/prev.png").resize((30, 30)))
        self.prev_button = ctk.CTkButton(master=self.graphic_frame, width=40, height=40, image=prev_image, text="")
        self.prev_button.grid(row=0, column=1, padx=(5, 0), pady=5, sticky="nsew")

        forward_image = ctk.CTkImage(Image.open("GUI/images/forward.png").resize((30, 30)))
        self.forward_button = ctk.CTkButton(master=self.graphic_frame, width=40, height=40, image=forward_image,
                                            text="", command=self.handleNextButton)
        self.forward_button.grid(row=0, column=2, padx=(5, 0), pady=5, sticky="nsew")

        next_next_image = ctk.CTkImage(Image.open("GUI/images/next_next.png").resize((30, 30)))
        self.next_next_button = ctk.CTkButton(master=self.graphic_frame, width=40, height=40, image=next_next_image,
                                              text="")
        self.next_next_button.grid(row=0, column=3, padx=(5, 0), pady=5, sticky="nsew")

        reload_image = ctk.CTkImage(Image.open("GUI/images/reload.png").resize((30, 30)))
        self.reload_button = ctk.CTkButton(master=self.graphic_frame, width=40, height=40, image=reload_image, text="")
        self.reload_button.grid(row=0, column=0, padx=(220, 0), pady=(5, 5), sticky="nsew")

    def handleNextButton(self):
        self.addInformationEvent("Произошла итерация алгоритма")
    def createAddPointLabel(self):
        general_add_frame = ctk.CTkFrame(master=self, width=200, height=100)
        general_add_frame.grid(row=1, column=1, padx=20, pady=20, sticky='nw')
        input_frame = ctk.CTkFrame(master=general_add_frame, width=200, height=50)
        input_frame.grid(row=0, column=0, padx=0, pady=0, sticky='n')

        self.x_string = ctk.StringVar()
        self.y_string = ctk.StringVar()
        self.value_string = ctk.StringVar()
        x_label = ctk.CTkLabel(master=input_frame, text="X")
        x_label.grid(row=0, column=0, padx=5, pady=0, sticky='nw')
        x_enter = ctk.CTkEntry(master=input_frame, width=50, textvariable=self.x_string)
        x_enter.grid(row=0, column=1, padx=0, pady=0, sticky='nw')
        y_label = ctk.CTkLabel(master=input_frame, text="Y")
        y_label.grid(row=0, column=2, padx=5, pady=0, sticky='nw')
        y_enter = ctk.CTkEntry(master=input_frame, width=50, textvariable=self.y_string)
        y_enter.grid(row=0, column=3, padx=0, pady=0, sticky='nw')

        value_label = ctk.CTkLabel(master=input_frame, text="Значение")
        value_label.grid(row=0, column=4, padx=5, pady=0, sticky='nw')
        value_enter = ctk.CTkEntry(master=input_frame, width=50, textvariable=self.value_string)
        value_enter.grid(row=0, column=5, padx=0, pady=0, sticky='nw')

        button_add_point = ctk.CTkButton(master=general_add_frame, text='Добавить точку',
                                         width=200, command=self.handlerAddPoint)
        button_add_point.grid(row=1, column=0, padx=0, pady=5)
        button_add_point_file = ctk.CTkButton(master=general_add_frame, text='Считать точки из файла',
                                              width=200, command=self.readFilePoints)
        button_add_point_file.grid(row=2, column=0, padx=0, pady=5)

        button_add_point_random = ctk.CTkButton(master=general_add_frame, text='Случайная генерация',
                                         width=200, command=self.openWindowRangeRandow)
        button_add_point_random.grid(row=3, column=0, padx=0, pady=5)



    def randomGeneratePoints(self):
        random_from = self.range_random_from.get()
        random_before = self.range_random_before.get()
        random_count = self.range_random_count.get()
        try:
            random_from = int(random_from)
            random_before = int(random_before)
            random_count = int(random_count)
            self.generate_random_window.destroy()  # Закрываем окно после ввода

            for i in range(random_count):
                x = random.randint(min(random_from, random_before), max(random_from, random_before))
                y = random.randint(min(random_from, random_before), max(random_from, random_before))
                value = random.randint(0, 1)
                if ((x, y, 1) not in self.points) and ((x, y, 0) not in self.points):
                    self.points.add((x, y, value))
                    self.createPoint(x, y, value, len(self.points))
        except ValueError:
            pass



    def openWindowRangeRandow(self):
        self.generate_random_window = ctk.CTkToplevel(self)
        self.generate_random_window.title("Введите диапазон")
        self.generate_random_window.geometry("250x300")

        # Метка для поля ввода
        label_random = ctk.CTkLabel(self.generate_random_window, text="Введите диапазон значений генерации")
        label_random.grid(row=0, column=0, padx=10, pady=10, sticky='w')

        # Поле ввода
        self.range_random_from = ctk.CTkEntry(self.generate_random_window)
        self.range_random_from.grid(row=1, column=0, padx=10, pady=10, sticky='we')

        self.range_random_before = ctk.CTkEntry(self.generate_random_window)
        self.range_random_before.grid(row=2, column=0, padx=10, pady=10, sticky='we')

        label_count = ctk.CTkLabel(self.generate_random_window, text="Введите количество точек")
        label_count.grid(row=3, column=0, padx=10, pady=10, sticky='w')

        self.range_random_count = ctk.CTkEntry(self.generate_random_window)
        self.range_random_count.grid(row=4, column=0, padx=10, pady=10, sticky='we')

        # Кнопка подтверждения
        submit_button = ctk.CTkButton(self.generate_random_window, text="Подтвердить", command=self.randomGeneratePoints)
        submit_button.grid(row=5, column=0, padx=10, pady=10, sticky='we')

    def readFilePoints(self):
        file_path = filedialog.askopenfilename(title="Выберите файл",
                                               filetypes=(("CSV files", "*.csv"), ("All files", "*.*")))
        with open(file_path, newline='', encoding='utf-8') as csvfile:
            csvreader = csv.reader(csvfile, delimiter=',')
            for x, y, value in csvreader:
                try:
                    x_int = int(x)
                    y_int = int(y)
                    value_int = int(value)
                    if value_int == 0 or value_int == 1:
                        self.points.add((x_int, y_int, value_int))
                        self.createPoint(x_int, y_int, value_int, len(self.points))
                except ValueError:
                    pass

    def handlerAddPoint(self):
        x = self.x_string.get()
        y = self.y_string.get()
        value = self.value_string.get()
        try:
            x = int(x)
            y = int(y)
            value = int(value)
            if ((x, y, 1) not in self.points) and ((x, y, 0) not in self.points) and (value == 0 or value == 1):
                self.points.add((x, y, value))
                self.x_string.set('')
                self.y_string.set('')
                self.value_string.set('')
                self.createPoint(x, y, value, len(self.points))
        except ValueError:
            pass


    def createPoint(self, x, y, value, row_index):
        text_label = ctk.CTkLabel(master=self.frame_points, text=f'X: {x}, Y: {y}, VALUE: {value}')
        text_label.grid(row=row_index, column=0, padx=5, pady=5)
        point_button = ctk.CTkButton(master=self.frame_points, width=50, text="Удалить",
                                     command=lambda: self.deletePoint(text_label, point_button, (x, y, value)))
        point_button.grid(row=row_index, column=1, padx=10, pady=5, sticky='e')
        self.points_button_delete.append((text_label, point_button))



    def deletePoint(self, label, button, coords):
        self.points.remove(coords)
        label.destroy()
        button.destroy()

    def createInfoStateLabel(self, text, index_row):
        state_label_info = ctk.CTkLabel(master=self.state_frame_info, width=100, text=text)
        state_label_info.grid(row=index_row, column=0, padx=5, pady=0, sticky='w')
        self.info_state_labels[text[:-7]] = state_label_info


    def createStateLabel(self, text, index_row):
        self.string_state_frame[text] = ctk.StringVar()
        state_label = ctk.CTkLabel(master=self.state_frame, text=text)
        state_label.grid(row=index_row, column=0, padx=15, pady=3, sticky="we")
        state_entry = ctk.CTkEntry(master=self.state_frame, textvariable=self.string_state_frame[text])
        state_entry.grid(row=index_row+1, column=0, padx=10, pady=3, sticky="we")
        state_entry.bind('<Return>', lambda event: self.handleEnter(event, text))

    def handleEnter(self, event, extra_arg):
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
                    self.ax.set_xlim(0, number)
                    self.canvas.draw()
        except ValueError:
            pass
        self.string_state_frame[extra_arg].set("")




