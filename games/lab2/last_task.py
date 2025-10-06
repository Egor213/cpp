# from math import comb
# import numpy as np

# N1 = comb(13, 4)
# N2 = comb(13, 3) * comb(29, 1)
# N3 = comb(13, 2) * comb(29, 2) + comb(13, 1) * comb(29, 3) + comb(29, 4)
# N0 = comb(42, 4)
# print(N1, N2, N3)
# C1 = N1/N0
# C2 = N2/N0
# C3 = N3/N0

# H = - C1 * np.log2(C1) - C2 * np.log2(C2) - C3 * np.log2(C3)
# print(H)


from math import comb
import numpy as np
import pandas as pd

# Исходные данные из таблицы
data = [
    [0, 0.1751, 0.3006, 0.5244],
    [1, 0.1438, 0.2818, 0.5745],
    [2, 0.1159, 0.2599, 0.6242],
    [3, 0.0916, 0.2355, 0.6729],
    [4, 0.0706, 0.2094, 0.72],
    [5, 0.053,  0.1821, 0.7649],
    [6, 0.0385, 0.1546, 0.8069]
]

df = pd.DataFrame(data, columns=["Плохие у A", "p1", "p2", "p3"])

# Формулы из условия
def pB1_A(number_iter):  # плохие карты A
    return (comb(12 + number_iter, 4) * comb(32 - number_iter, 2)) / (comb(44, 6) * comb(6, 2))

def pB2_A(number_iter):  # средние карты A
    return ((comb(12 + number_iter, 3) * comb(32 - number_iter, 3)) / comb(44, 6)) * (comb(3, 2) / comb(6, 2))

def pB3_A(number_iter):  # хорошие карты A
    return ((comb(12 + number_iter, 2) * comb(32 - number_iter, 4)) / comb(44, 6) * (comb(4, 2) / comb(6, 2)) +
            (comb(12 + number_iter, 1) * comb(32 - number_iter, 5)) / comb(44, 6) * (comb(5, 2) / comb(6, 2)) +
            (comb(32 - number_iter, 6)) / comb(44, 6))


i = 6
def calc_bayes(row):
    global i
    p1, p2, p3 = row["p1"], row["p2"], row["p3"]
    P_A = pB1_A(i) * p1 + pB2_A(i) * p2 + pB3_A(i) * p3
    P_A_B1 = (pB1_A(i) * p1) / P_A
    P_A_B2 = (pB2_A(i) * p2) / P_A
    P_A_B3 = (pB3_A(i) * p3) / P_A
    H = - P_A_B1 * np.log2(P_A_B1) - P_A_B2 * np.log2(P_A_B2) - P_A_B3 * np.log2(P_A_B3)
    i -= 1
    return pd.Series([P_A, P_A_B1, P_A_B2, P_A_B3, H])

df[["P(A)", "P_A(B1)", "P_A(B2)", "P_A(B3)", "H"]] = df.apply(calc_bayes, axis=1)

# Округлим для красоты
df = df.round(6)

print(df)

p_B1 = (comb(13, 4) * comb(31, 2)) / (comb(44, 6) * comb(6, 2))
p_B2 = (comb(13, 3) * comb(31, 3) * comb(3, 2)) / (comb(44, 6) * comb(6, 2))
p_B3_1 = (comb(13, 2) * comb(31, 4) * comb(4, 2)) / (comb(44, 6) * comb(6, 2))
p_B3_2 = (comb(13, 1) * comb(31, 5) * comb(5, 2)) / (comb(44, 6) * comb(6, 2))
p_B3_3 = (comb(31, 6) / comb(44, 6))
p_B3 = p_B3_1 + p_B3_2 + p_B3_3
print(p_B1, p_B2, p_B3)
P_A = 0.053 * p_B1 + 0.1821 * p_B2 + 0.7649 * p_B3
print(f"{P_A=}")
print(f"P_A(B1) = {0.053 * p_B1/P_A}")
print(f"P_A(B2) = {0.1821 * p_B2/P_A}")
print(f"P_A(B3) = {0.7649 * p_B3/P_A}")