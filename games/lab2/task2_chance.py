from math import comb

# Параметры
N = 51      # всего карт
K = 21      # плохие карты
n = 6       # размер расклада

# Функция для вычисления количества комбинаций и вероятности
def count_combinations(k_bad):
    bad_combinations = comb(K, k_bad)
    good_combinations = comb(N - K, n - k_bad)
    total_combinations = comb(N, n)
    probability = (bad_combinations * good_combinations) / total_combinations
    return bad_combinations, good_combinations, bad_combinations * good_combinations, probability

# Инициализация
total_combinations = comb(N, n)
print(f"Общее количество 6-картных раскладов: {total_combinations}\n")

# Словарь для классификации
classification = { "Хороший": [], "Средний": [], "Плохой": [] }

# Подсчет по каждому числу плохих карт
for k in range(0, n+1):
    bad_c, good_c, favorable, prob = count_combinations(k)
    print(f"Плохих карт: {k}")
    print(f"  Количество комбинаций плохих карт: {bad_c}")
    print(f"  Количество комбинаций хороших карт: {good_c}")
    print(f"  Всего благоприятных комбинаций: {favorable}")
    print(f"  Вероятность: {prob:.5f} ({prob*100:.2f}%)\n")
    
    # Классификация
    if k < 3:
        classification["Хороший"].append(prob)
    elif k == 3:
        classification["Средний"].append(prob)
    else:
        classification["Плохой"].append(prob)

# Итоговые вероятности по типам раскладов
for key, probs in classification.items():
    total_prob = sum(probs)
    print(f"{key} расклад: вероятность = {total_prob:.5f} ({total_prob*100:.2f}%)")
