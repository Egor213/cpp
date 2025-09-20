


import numpy as np
import matplotlib.pyplot as plt


def has_saddle_point(matrix):
    """Проверка наличия седловой точки"""
    for i in range(matrix.shape[0]):
        row_min = np.min(matrix[i])
        for j in range(matrix.shape[1]):
            col_max = np.max(matrix[:, j])
            if matrix[i, j] == row_min and matrix[i, j] == col_max:
                return True
    return False

def generate_matrix_without_saddle(rows=2, cols=7):
    """Генерация матрицы без седловой точки"""
    while True:
        matrix = np.random.randint(0, 30, size=(rows, cols))
        if not has_saddle_point(matrix):
            return matrix


def check_dominating_strategies(matrix):
    rows, cols = matrix.shape
    dominated_rows = []
    dominated_cols = []
    changed = True

    while changed:
        changed = False
        rows, cols = matrix.shape

        for i in range(rows):
            for k in range(rows):
                if i != k:
                    if np.all(matrix[i] <= matrix[k]) and np.any(matrix[i] < matrix[k]):
                        dominated_rows.append((i, k))
                        if len(matrix) > 2:
                            matrix = np.delete(matrix, i, axis=0)
                            changed = True
                            break
            if changed:
                break  

        if changed:
            continue 

        for j in range(cols):
            for l in range(cols):
                if j != l:
                    if np.all(matrix[:, j] >= matrix[:, l]) and np.any(matrix[:, j] > matrix[:, l]):
                        dominated_cols.append((j, l))
                        if matrix.shape[1] > 2:
                            matrix = np.delete(matrix, j, axis=1)
                            changed = True
                            break
            if changed:
                break

    return matrix, dominated_rows, dominated_cols




import pandas as pd
from fractions import Fraction

def fraction_str(numer, denom):
    """Возвращает строку дроби numer/denom в сокращённом виде, или целое, если делится."""
    f = Fraction(numer, denom)
    if f.denominator == 1:
        return str(f.numerator)
    return f"{f.numerator}/{f.denominator}"

def brown_robinson_table(A, iterations=10, init_i=0, show_header=True):
    """
    Метод Брауна—Робинсона в табличном виде (формат, как в твоём примере).
    A - матрица (m x n), iterations - число итераций (k от 1..iterations).
    init_i - индекс начальной строки (0-based). Обычно в примере init_i=0.
    Возвращает список строк таблицы (каждая — список строковых полей).
    Также печатает красиво таблицу.
    """
    A = np.asarray(A, dtype=int)
    m, n = A.shape

    # накопленные суммы
    B = np.zeros(n, dtype=int)  # суммы по столбцам (B1..Bn)
    S = np.zeros(m, dtype=int)  # суммы по строкам (A1..Am)

    i = int(init_i)
    table = []

    for k in range(1, iterations + 1):
        # 1) добавляем выбранную строку i к суммам по столбцам
        B += A[i, :]

        # 2) выбираем столбец j : min по B
        j = int(np.argmin(B))

        # 3) добавляем выбранный столбец j к суммам по строкам
        S += A[:, j]

        # 4) вычисления Vmin, Vmax, Vsr как дроби
        minB = int(B.min())
        maxS = int(S.max())

        Vmin_str = fraction_str(minB, k)
        Vmax_str = fraction_str(maxS, k)
        # Vср = (minB/k + maxS/k)/2 = (minB+maxS) / (2*k)
        Vsr_str = fraction_str(minB + maxS, 2 * k)

        # собираем строку таблицы
        row = []
        row.append(str(k))             # k
        row.append(str(i + 1))         # i  (1-based для вывода)

        # B1..Bn
        for colsum in B:
            row.append(str(int(colsum)))

        row.append(str(j + 1))         # j  (1-based)

        # A1..Am (S)
        for rowsum in S:
            row.append(str(int(rowsum)))

        row.append(Vmin_str)
        row.append(Vmax_str)
        row.append(Vsr_str)

        table.append(row)

        # 5) следующий выбор строки i = argmax S (индекс наибольшего в S)
        i = int(np.argmax(S))

    # Печать таблицы аккуратно
    # Заголовок
    hdr = ["k", "i"] + [f"B{t+1}" for t in range(n)] + ["j"] + [f"A{t+1}" for t in range(m)] + ["Vmin", "Vmax", "Vср"]

    # Вычислим ширины столбцов
    cols = [hdr] + table
    col_widths = [max(len(row[c]) for row in cols) for c in range(len(hdr))]

    # печать заголовка
    if show_header:
        header_line = "\t".join(hdr[c].rjust(col_widths[c]) for c in range(len(hdr)))
        print(header_line)
        print("-" * (sum(col_widths) + 3 * len(col_widths)))

    for r in table:
        line = "\t".join(r[c].rjust(col_widths[c]) for c in range(len(r)))
        print(line)

    return table



if __name__ == "__main__":
    col = 4
    row = 4
    np.random.seed(1)
    A = generate_matrix_without_saddle(row, col)
    print("Исходная матрица:")
    print(A)
    
    reduced_A, rows, cols = check_dominating_strategies(A)

    if rows:
        print("\nДоминируемые строки:")
        for r in rows:
            print(f"Строка {r[0]+1} доминируется строкой {r[1]+1}")
    else:
        print("\nДоминируемых строк нет")

    if cols:
        print("\nДоминируемые столбцы:")
        for c in cols:
            print(f"Столбец {c[0]+1} доминируется столбцом {c[1]+1}")
    else:
        print("\nДоминируемых столбцов нет")
    
    print("\nМатрица после исключения доминируемых стратегий:")
    print(reduced_A)



    print("\nТаблица метода Брауна—Робинсона:\n")
    brown_robinson_table(reduced_A, iterations=100, init_i=0)