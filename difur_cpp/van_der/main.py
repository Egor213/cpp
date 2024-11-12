import csv
import matplotlib.pyplot as plt

# Функция для считывания данных из CSV файла
def read_csv(file_name):
    x_values = []
    y_values = []
    with open(file_name, mode='r') as file:
        reader = csv.reader(file, delimiter=';') 
        for row in reader:
            if len(row) >= 2:  
                try:
                    x_values.append(float(row[0]))  # Считываем x
                    y_values.append(float(row[1]))  # Считываем y
                except ValueError:
                    continue  
    
    return x_values, y_values

# Считывание данных
x, y = read_csv('../data.csv')
plt.plot(x, y, label="y = f(x)")  
plt.xlabel('x')
plt.ylabel('y')
plt.title('2D график из CSV файла')
plt.legend()
plt.grid(True)

# Показать график
plt.show()
