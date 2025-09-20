import numpy as np
import itertools

np.set_printoptions(precision=6, suppress=True)


def print_matrix(title, M):
    print(f"\n{title}")
    print(M)


def has_saddle_point(matrix):
    """Проверка наличия седловой точки"""
    for i in range(matrix.shape[0]):
        row_min = np.min(matrix[i])
        for j in range(matrix.shape[1]):
            col_max = np.max(matrix[:, j])
            if matrix[i, j] == row_min and matrix[i, j] == col_max:
                return True
    return False


def generate_matrix_without_saddle(rows=4, cols=4, low=-5, high=30):
    """Генерация матрицы без седловой точки"""
    while True:
        matrix = np.random.randint(low, high, size=(rows, cols))
        if not has_saddle_point(matrix):
            return matrix


def check_dominating_strategies(matrix):
    """Удаление доминируемых строк и столбцов (печатает действия)"""
    print("\n--- Проверка и удаление доминируемых стратегий ---")
    mat = matrix.copy()
    rows, cols = mat.shape
    dominated_rows = []
    dominated_cols = []
    changed = True

    while changed:
        changed = False
        rows, cols = mat.shape
        # строки
        for i in range(rows):
            for k in range(rows):
                if i == k:
                    continue
                if np.all(mat[i] <= mat[k]) and np.any(mat[i] < mat[k]):
                    print(f"Строка {i} доминируется строкой {k} (все элементы ≤ и есть <). Удаляем строку {i}.")
                    dominated_rows.append((i, k))
                    if rows > 2:
                        mat = np.delete(mat, i, axis=0)
                        changed = True
                    break
            if changed:
                break
        if changed:
            continue
        # столбцы
        rows, cols = mat.shape
        for j in range(cols):
            for l in range(cols):
                if j == l:
                    continue
                if np.all(mat[:, j] >= mat[:, l]) and np.any(mat[:, j] > mat[:, l]):
                    print(f"Столбец {j} доминируется столбцом {l} (для всех строк a_ij ≥ a_il и есть >). Удаляем столбец {j}.")
                    dominated_cols.append((j, l))
                    if cols > 2:
                        mat = np.delete(mat, j, axis=1)
                        changed = True
                    break
            if changed:
                break

    return mat, dominated_rows, dominated_cols


def print_equations_primal(Apos):
    m, n = Apos.shape
    print("\nПрямое ЗЛП (в стандартизированном виде, для объяснения):")
    print(" min  sum(x_i)")
    print(" при условиях (A')^T x >= 1, x >= 0")
    print("Эквивалентно (в виде неравенств):")
    for j in range(n):
        coeffs = [f"{Apos[i, j]:.6f}*x{i+1}" for i in range(m)]
        print(f"  {' + '.join(coeffs)} >= 1")


def print_equations_dual(Apos):
    m, n = Apos.shape
    print("\nДвойственная (которая мы решаем через симплекс):")
    print(" max sum(y_j)")
    print(" при условиях A' * y <= 1, y >= 0")
    print("То есть для каждой строки i:")
    for i in range(m):
        coeffs = [f"{Apos[i, j]:.6f}*y{j+1}" for j in range(n)]
        print(f"  {' + '.join(coeffs)} <= 1")


# печать симплекс-таблицы
def print_tableau(T, basis, n_vars):
    m = T.shape[0] - 1
    total_cols = T.shape[1] - 1
    header = [f"y{j+1}" for j in range(n_vars)] + [f"s{j+1}" for j in range(m)] + ["RHS"]
    print("\n" + "-" * 80)
    print("Базис:", ["y"+str(b+1) if b < n_vars else "s"+str(b-n_vars+1) for b in basis])
    print("Таблица (каждая строка — уравнение базовой переменной):")
    print("{:>6}".format(""), end=" ")
    for h in header:
        print(f"{h:>10}", end=" ")
    print()
    for i in range(m):
        row_label = f"r{i+1}"
        print(f"{row_label:>6}", end=" ")
        for j in range(total_cols):
            print(f"{T[i, j]:10.6f}", end=" ")
        print(f"{T[i, -1]:10.6f}")
    print("-" * 80)
    print("obj ", end=" ")
    for j in range(total_cols):
        print(f"{T[-1, j]:10.6f}", end=" ")
    print(f"{T[-1, -1]:10.6f}")
    print("-" * 80)


def simplex_maximize(A, b, c, verbose=True, max_iters=200):
    """
    Tabular simplex for max c^T x subject to A x <= b, x >= 0
    Returns solution vector x (length n), objective value, tableau and basis.
    """
    m, n = A.shape
    # Tableau: rows m constraints + 1 objective, columns n variables + m slacks + RHS
    T = np.zeros((m + 1, n + m + 1))
    T[:m, :n] = A.copy()
    T[:m, n:n + m] = np.eye(m)
    T[:m, -1] = b.copy()
    T[-1, :n] = -c.copy()  # maximize -> -c in tableau
    basis = list(range(n, n + m))

    if verbose:
        print("\n=== Начальная симплекс-таблица ===")
        print_tableau(T, basis, n)

    tol = 1e-10
    it = 0
    while True:
        it += 1
        if it > max_iters:
            raise RuntimeError("Превышено число итераций симплекс-метода")
        reduced = T[-1, :-1]
        min_val = reduced.min()
        if min_val >= -tol:
            if verbose:
                print("\nДостигнуто оптимальное решение (все коэффициенты в строке целей неположительны).")
            break
        # выбираем входящую переменную: наиболее отрицательный коэффициент
        entering = int(np.argmin(reduced))
        if verbose:
            print(f"\nИтерация {it}: входящая переменная column = {entering} (коэффициент = {T[-1, entering]:.6f})")
        # вычисляем отношения для выбора уходящей строки
        col = T[:m, entering]
        with np.errstate(divide='ignore', invalid='ignore'):
            ratios = np.where(col > tol, T[:m, -1] / col, np.inf)
        if np.all(ratios == np.inf):
            raise RuntimeError("Задача неограничена по выбранному направлению (unbounded).")
        leaving = int(np.argmin(ratios))
        if verbose:
            print(f"  уходящая строка = {leaving}, pivot = {T[leaving, entering]:.6f}, ratio = {ratios[leaving]:.6f}")

        # pivot
        pivot = T[leaving, entering]
        T[leaving, :] = T[leaving, :] / pivot
        for i in range(m + 1):
            if i == leaving:
                continue
            factor = T[i, entering]
            T[i, :] = T[i, :] - factor * T[leaving, :]
        basis[leaving] = entering

        if verbose:
            print_tableau(T, basis, n)

    # extract solution
    x = np.zeros(n + m)
    for i in range(m):
        var = basis[i]
        if var < n + m:
            x[var] = T[i, -1]
    solution = x[:n]
    objective = float(np.dot(c, solution))
    if verbose:
        print("\n=== Результат симплекс-метода ===")
        print_tableau(T, basis, n)
        print("Решение (переменные y):", solution)
        print("Значение целевой функции (max sum y_j) = ", objective)
    return solution, objective, T, basis


def solve_zero_sum_via_lp_verbose(matrix, verbose=True):
    """
    Подробное решение нулевой игры через сведение к линейной задаче и симплекс.
    Печатает все шаги и возвращает p, q, v.
    """
    m, n = matrix.shape
    print("\n======================== РЕШЕНИЕ НУЛЕВОЙ ИГРЫ ЧЕРЕЗ LP ========================")
    print_matrix("Исходная матрица A (I - строки, II - столбцы):", matrix)

    # 1) Сдвиг матрицы чтобы все элементы были положительны (нужен трюк приведения)
    min_entry = matrix.min()
    shift = 0.0
    if min_entry <= 0:
        shift = -min_entry 
    Apos = matrix + shift
    print(f"\nШаг 1: сдвиг матрицы на K = {shift:.6f}, чтобы все элементы > 0.")
    print_matrix("A' = A + K:", Apos)

    # 2) Формулировка ЗЛП
    print_equations_primal(Apos)
    print_equations_dual(Apos)

    # 3) Решаем двойственную задачу (которая принимает вид max sum y subject to A' y <= 1, y>=0)
    A_dual = Apos.copy()  # m x n
    b = np.ones(m)        # RHS = 1
    c = np.ones(n)        # maximize sum y_j

    print("\nШаг 2: Решаем двойственную задачу методом симплекс (max sum y_j s.t. A' y <= 1).")
    y, obj, T, basis = simplex_maximize(A_dual, b, c, verbose=verbose)

    # 4) Восстановление цены игры и стратегии II
    sum_y = obj
    if sum_y <= 0:
        raise RuntimeError("Невозможно восстановить решение: sum(y) <= 0.")
    v_prime = 1.0 / sum_y
    v = v_prime - shift
    q = y * v_prime

    print("\nШаг 3: восстановление цены игры и стратегии II:")
    print(f" sum(y) = {sum_y:.6f}")
    print(f" v' = 1 / sum(y) = {v_prime:.6f} (цена для сдвинутой матрицы)")
    print(f" исходная цена v = v' - K = {v:.6f}")
    print("Вектор y (результат симплекса):", y)
    print("Стратегия II (q = y * v'):", q, "сумма =", q.sum())

    # 5) Восстановление x и стратегии I
    print("\nШаг 4: восстановление стратегии игрока I (p).")
    tol = 1e-9
    S = np.where(y > tol)[0].tolist()
    print("Индексы поддерживающих y (y>tol):", S)

    # нам надо найти x (размер m) такое, что (Apos[:, S].T) x = 1 (в компонентах), x >= 0
    x = None
    if len(S) == m:
        print("Поддержка ровно равна числу строк. Попытка прямого решения системы.")
        M = Apos[:, S]
        try:
            x_candidate = np.linalg.solve(M.T, np.ones(m))
            print("Решение системы найдено:", x_candidate)
            if np.all(x_candidate >= -1e-9):
                x = x_candidate
        except np.linalg.LinAlgError:
            print("Матрица вырождена, не удалось решить напрямую.")
    # если прямого решения нет, переберём комбинации
    if x is None:
        candidates = S if len(S) > 0 else list(range(n))
        print("Перебор комбинаций столбцов из кандидатов для поиска допустимого x...")
        found = False
        # переберём комбинации размера m (если возможно)
        for comb in itertools.combinations(candidates, min(m, len(candidates))):
            if len(comb) < m:
                continue
            M = Apos[:, comb]  # m x m
            try:
                x_cand = np.linalg.solve(M.T, np.ones(m))
            except np.linalg.LinAlgError:
                continue
            if np.all(x_cand >= -1e-9):
                print(f"Найдена допустимая комбинация столбцов comb = {comb}, x = {x_cand}")
                # развернём x в вектор длины m (тут x_cand длины m соответствует x)
                x = x_cand
                found = True
                break
        if not found and x is None:
            print("Не найдено простое решение комбинациями. Пробуем least squares или NNLS-приближение...")
            # Простейшая проекция отрицательных в ноль через итерации (грубая NNLS)
            x0 = np.ones(m)
            for k in range(200):
                # решение min ||Apos^T x - 1||^2, даём Apos^T x = 1 -> lstsq
                x_ls, *_ = np.linalg.lstsq(Apos.T, np.ones(n), rcond=None)
                x_ls = np.maximum(x_ls, 0)
                x0 = x_ls
            x = x0
            print("Приближённый вектор x (NNLS-подобный):", x)

    print("\nВектор x (где x_i = p_i / v'):", x)
    p = x * v_prime
    p = np.maximum(p, 0)
    if p.sum() == 0:
        p = np.ones_like(p) / len(p)
    else:
        p = p / p.sum()
    print("Стратегия игрока I (p):", p, "sum =", p.sum())

    # 6) проверки
    print("\nШаг 5: проверки корректности (ожидания):")
    exp_cols = p @ matrix  # p^T * A
    exp_rows = matrix @ q  # A * q
    print("p^T * A (ожидание по столбцам):", exp_cols)
    print("min(p^T A) =", exp_cols.min(), "≈ v ?", v)
    print("A * q (ожидание по строкам):", exp_rows)
    print("max(A q) =", exp_rows.max(), "≈ v ?", v)

    return {
        "A": matrix,
        "Apos": Apos,
        "shift": shift,
        "y": y,
        "q": q,
        "x": x,
        "p": p,
        "v": v,
        "v_prime": v_prime,
        "simplex_tableau": T,
        "simplex_basis": basis
    }


# ================ Пример запуска ================
if __name__ == "__main__":
    # np.random.seed(1)  # фиксируем д.ля воспроизводимости (удали, если хочешь случайные матрицы)
    rows = 4
    cols = 4
    A = generate_matrix_without_saddle(rows, cols)
    print_matrix("Сгенерированная исходная матрица A:", A)

    reduced_A, rows_dom, cols_dom = check_dominating_strategies(A)
    print_matrix("\nМатрица после удаления доминируемых стратегий:", reduced_A)
    if rows_dom:
        print("Удалённые строки (доминируемые):", rows_dom)
    if cols_dom:
        print("Удалённые столбцы (доминируемые):", cols_dom)

    result = solve_zero_sum_via_lp_verbose(reduced_A, verbose=True)

    print("\n=== ИТОГОВЫЕ РЕЗУЛЬТАТЫ ===")
    print("p (игрок I):", result['p'])
    print("q (игрок II):", result['q'])
    print("v (цена игры):", result['v'])
