


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

def solve_game_geom_n2(matrix):
    """Геометрический метод для игры n x 2"""
    n = matrix.shape[0]
    qs = np.linspace(0, 1, 500)
    Ei_all = np.array([(1-qs)*matrix[i,0] + qs*matrix[i,1] for i in range(n)])
    upper_env = Ei_all.max(axis=0)
    imin = np.argmin(upper_env)
    q_star, v_star = qs[imin], upper_env[imin]

    # аналитические наклоны и пересечения
    slopes = matrix[:,1] - matrix[:,0]
    intercepts = matrix[:,0]

    forming_pair = None
    for i in range(n):
        for j in range(i+1, n):
            denom = slopes[i] - slopes[j]
            if denom == 0:
                continue
            q_intersect = (intercepts[j] - intercepts[i]) / denom
            if 0 <= q_intersect <= 1 and np.isclose(q_intersect, q_star, atol=1e-2):
                forming_pair = (i, j)
                break
        if forming_pair:
            break

    # fallback если не нашли аналитически
    if forming_pair is None:
        Ei_at_opt = Ei_all[:, imin]
        forming_indices = np.where(np.isclose(Ei_at_opt, v_star, atol=1e-2))[0]
    else:
        forming_indices = forming_pair

    return {
        "qs": qs,
        "Ei_all": Ei_all,
        "upper_env": upper_env,
        "q_star": q_star,
        "v_star": v_star,
        "forming_indices": forming_indices,
        "matrix": matrix
    }

def strategy_player_I(forming_matrix, v_star):
    """Решение 2 уравнений относительно вероятностей игрока I"""
    a, b = forming_matrix[0,0], forming_matrix[0,1]
    c, d = forming_matrix[1,0], forming_matrix[1,1]
    A = np.array([[a, b],
                  [c, d]])
    B = np.array([v_star, v_star])
    x, y = np.linalg.solve(A, B)
    return x, y

def plot_game_geom_n2(data):
    qs = data["qs"]
    Ei_all = data["Ei_all"]
    upper_env = data["upper_env"]
    q_star = data["q_star"]
    v_star = data["v_star"]
    forming_indices = data["forming_indices"]
    matrix = data["matrix"]
    n = Ei_all.shape[0]

    plt.figure(figsize=(9,6))
    for i in range(n):
        if i in forming_indices:
            plt.plot(qs, Ei_all[i], lw=2.5, color="orange")
        else:
            plt.plot(qs, Ei_all[i], lw=1)
    plt.plot(qs, upper_env, color="black", lw=3, label="Верхняя огибающая")
    plt.scatter([q_star], [v_star], color="red", s=60, zorder=5, label="Оптимум")
    plt.text(q_star, v_star+0.3, f"({q_star:.2f}; {v_star:.2f})", ha="center", color="red")
    plt.plot([q_star, q_star], [0, v_star], linestyle="--", color="gray", alpha=0.7)
    plt.plot([0, q_star], [v_star, v_star], linestyle="--", color="gray", alpha=0.7)
    matrix_text = "Матрица A =\n" + str(matrix)
    plt.text(1.05, 0.5, matrix_text, transform=plt.gca().transAxes,
             fontsize=10, va="center", ha="left",
             bbox=dict(boxstyle="round,pad=0.5", fc="lightyellow", ec="black"))
    plt.title("Геометрический метод (n x 2)")
    plt.xlabel("q — вероятность выбрать 2-й столбец (игрок II)")
    plt.ylabel("Ожидаемый выигрыш игрока I")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.show()


def line_from_two_points(p1, p2):

    x1, y1 = p1
    x2, y2 = p2
    if x2 == x1:
        raise ValueError("Вертикальная линия, наклон не определён")
    k = (y2 - y1) / (x2 - x1)
    b = y1 - k * x1
    return k, b


def strategy_player_B(forming_matrix, v_star):
    a, c = forming_matrix[0, 0], forming_matrix[1, 0]
    b, d = forming_matrix[0, 1], forming_matrix[1, 1]
    A = np.array([[a, c],
                  [b, d]])
    B = np.array([v_star, v_star])
    x, y = np.linalg.solve(A, B)
    return x, y

def intersection_point(k1, b1, k2, b2):
    """
    Вычисляет точку пересечения двух прямых y = k1*x + b1 и y = k2*x + b2.
    Возвращает кортеж (x, y).
    """
    if k1 == k2:
        raise ValueError("Прямые параллельны, пересечения нет")
    x = (b2 - b1) / (k1 - k2)
    y = k1 * x + b1
    return x, y

if __name__ == "__main__":
    col = 2
    row = 7

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


    data = solve_game_geom_n2(reduced_A)
    forming_indices = data["forming_indices"]
    forming_matrix = reduced_A[forming_indices, :]
    print("Формирующие строки:\n", forming_matrix)

    k1, b1 = line_from_two_points((0, forming_matrix[0, 0]), (1, forming_matrix[0, 1]))
    print(f"Первая линия: y = {k1}*x + {b1}")

    k2, b2 = line_from_two_points((0, forming_matrix[1, 0]), (1, forming_matrix[1, 1]))
    print(f"Вторая линия: y = {k2}*x + {b2}")

    x_star, y_star = intersection_point(k1, b1, k2, b2)
    print(f"Точка пересечения: ({x_star:.3f}, {y_star:.3f})")

    q1, q2 = strategy_player_B(forming_matrix, data['v_star'])

    print("Индексы: ", forming_indices)
    temp = [0] * len(reduced_A)
    temp[forming_indices[0]] = q1
    temp[forming_indices[1]] = q2
    print(f"Ответ A({", ".join(map(lambda x: str(round(x, 3)), temp))}), B({1-x_star:.3f}, {x_star:.3f})")
    print("Цена игры: ", data['v_star'])
    plot_game_geom_n2(data)


