from math import comb, log2
import pandas as pd

def entropy(num_cards_total, hand_size):
    """Вычисляет энтропию H = log2(C(num_cards_total, hand_size))"""
    if num_cards_total < hand_size or hand_size <= 0:
        return 0
    return log2(comb(num_cards_total, hand_size))

def info_gain(H0, H1):
    """Информационный выигрыш I = H0 - H1"""
    return H0 - H1

def info_advantage(H1B, H1A):
    """Коэффициент информационного преимущества chi = H1B / H1A"""
    return H1B / H1A if H1A != 0 else 0

def local_game_results(total_cards=51, hand_size=6, open_card=1, cards_played_by_A=2):
    """
    Возвращает список результатов для игры, когда A кидает cards_played_by_A карт.
    """
    results = []
    remaining_cards_initial = total_cards - hand_size - open_card
    H0_A = H0_B = entropy(remaining_cards_initial, hand_size)
    for k in range(0, cards_played_by_A + 1):
        if k < cards_played_by_A:
            take_count = cards_played_by_A
            new_remaining = remaining_cards_initial - (k + take_count)

            H_A = entropy(new_remaining, hand_size - k)
            H_B = entropy(new_remaining + k, hand_size)
            print("K = ", k)
            print("A, ", H_A,  new_remaining, hand_size - k)
            print("B, ", H_B,  new_remaining + k, hand_size)
            
        else:
            take_count = 0
            new_remaining = remaining_cards_initial - 2 * k

            H_A = entropy(new_remaining, hand_size)
            H_B = entropy(new_remaining, hand_size)
            print("K = ", k)
            print("A, ", H_A,  new_remaining, hand_size)
            print("B, ", H_B,  new_remaining, hand_size)

        A_gain = info_gain(H0_A, H_A)
        B_gain = info_gain(H0_B, H_B)
        chi = info_advantage(H_B, H_A)

        results.append({
            "Карты A": cards_played_by_A,
            "Отбито B": k,
            "Взято B": take_count,
            "H1_A": round(H_A, 4),
            "H1_B": round(H_B, 4),
            "I_A": round(A_gain, 4),
            "I_B": round(B_gain, 4),
            "chi": round(chi, 4)
        })
    return results

if __name__ == "__main__":
    all_results = []
    # for n in range(1, 5):  # от 1 до 4 карт
    #     all_results.extend(local_game_results(cards_played_by_A=n))
    all_results.extend(local_game_results(cards_played_by_A=2))
    df = pd.DataFrame(all_results)
    print(df.to_string(index=False))
