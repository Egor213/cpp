#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <cmath>
#include <cstring>
#define DEBU
#define CLOC

struct Square
{
    int x;
    int y;
    int size;
};
class Work
{
public:
    int size;
    std::vector<std::vector<int>> matrix;
    std::vector<std::vector<int>> best_matrix;
    int iteration = 0;

    std::vector<Square> best_answer;
    std::vector<Square> current_answer;
    int max_count_square;
    int current_count_square;
    int best_count_square;
    int bool_prime = false;

public:
    Work(int size) : size(size), current_count_square(0), best_count_square(INT16_MAX),
                     matrix(size, std::vector<int>(size, 0)), best_matrix(size, std::vector<int>(size, 0))
    {
        int check = check_base_variant();
        if (!check)
        {
            default_work();
            backtraking();
        }
    }

    void default_work()
    {
        max_count_square = 6 * int(std::log2(3 * size - 1)) - 9;
        best_answer.resize(max_count_square);
        current_answer.resize(max_count_square);
        bool_prime = true;
        set_base_square();
    }

    int check_base_variant()
    {
        if (size % 2 == 0)
        {
            return set_base_two();
        }
        if (size % 3 == 0)
        {
            return set_base_three();
        }
        int temp = check_composite();
        if (temp)
        {
            return set_base_composite(temp);
        }
        return 0;
    }

    void print_matrix()
    {
        for (int y = 0; y < size; y++)
        {
            for (int x = 0; x < size; x++)
            {
                std::cout << matrix[x][y] << ' ';
            }
            std::cout << '\n';
        }
    }
#ifdef DEBUG
    void print_best_matrix()
    {
        for (int y = 0; y < size; y++)
        {
            for (int x = 0; x < size; x++)
            {
                std::cout << best_matrix[x][y] << ' ';
            }
            std::cout << '\n';
        }
    }
#endif

    void print_answer()
    {
        for (int i = 0; i < best_count_square; i++)
        {
            std::cout << best_answer[i].x << ' ' << best_answer[i].y << ' ' << best_answer[i].size << '\n';
        }
    }

private:
    void backtraking()
    {
#ifdef DEBUG
        iteration++;
        std::cout << "Вызов бектрекинга номер: " << iteration << '\n';
        print_matrix();
        std::cout << "\n"; 
#endif
        if (current_count_square >= best_count_square || current_count_square >= max_count_square)
        {
#ifdef DEBUG
            std::cout << "Данная матрица не оптимальна\n\n";
#endif
            return;
        }
        auto coords = get_free_cell();
        if (coords.first == -1)
        {
            if (current_count_square < best_count_square)
            {
#ifdef DEBUG
                best_matrix = matrix;
                std::cout << "Установленая новая матрица: " << '\n';
                print_best_matrix();
                std::cout << '\n';
#endif
                best_count_square = current_count_square;
                best_answer = current_answer;
            }
            return;
        }

        for (int i = std::min({size - 1, size - coords.first, size - coords.second}); i > 0; i--)
        {
            if (check_set_square(coords.first, coords.second, i))
            {
                current_answer[current_count_square] = {coords.first, coords.second, i};
                set_square(coords.first, coords.second, i);
                backtraking();
                del_square(coords, i);
#ifdef DEBUG
                std::cout << "Удален квадрат: \n";
                print_matrix();
                std::cout << "\n";
#endif
            }
        }
    }

    void del_square(std::pair<int, int> coords, int width)
    {
        current_count_square--;
        for (int i = coords.first; i < coords.first + width; i++)
        {
            for (int j = coords.second; j < coords.second + width; j++)
            {
                matrix[i][j] = 0;
            }
        }
    }

    std::pair<int, int> get_free_cell()
    {
        int temp = 0;
        if (bool_prime)
        {
            temp = (size - 1) / 2;
        }
        for (int y = temp; y < size; y++)
        {
            for (int x = temp; x < size; x++)
            {
                if (matrix[x][y] == 0)
                {
                    return std::make_pair(x, y);
                }
            }
        }
        return std::make_pair(-1, -1);
    }

    bool check_set_square(int x, int y, int width)
    {
        for (int i = x; i < x + width; i++)
        {
            for (int j = y; j < y + width; j++)
            {
                if (matrix[i][j] != 0)
                {
                    return false;
                }
            }
        }
        return true;
    }

    int set_base_two()
    {
        set_square(0, 0, size / 2);
        set_square(size / 2, 0, size / 2);
        set_square(0, size / 2, size / 2);
        set_square(size / 2, size / 2, size / 2);
        best_answer.push_back({0, 0, size / 2});
        best_answer.push_back({size / 2, 0, size / 2});
        best_answer.push_back({0, size / 2, size / 2});
        best_answer.push_back({size / 2, size / 2, size / 2});
#ifdef DEBUG
        best_matrix = matrix;
#endif
        best_count_square = current_count_square;
        return 4;
    }

    int set_base_three()
    {
        set_square(0, 0, 2 * (size / 3));
        set_square(2 * (size / 3), 0, (size / 3));
        set_square(2 * (size / 3), (size / 3), (size / 3));
        set_square(0, 2 * (size / 3), (size / 3));
        set_square((size / 3), 2 * (size / 3), (size / 3));
        set_square(2 * (size / 3), 2 * (size / 3), (size / 3));
        best_count_square = current_count_square;
        best_answer.push_back({0, 0, 2 * (size / 3)});
        best_answer.push_back({2 * (size / 3), 0, (size / 3)});
        best_answer.push_back({2 * (size / 3), (size / 3), (size / 3)});
        best_answer.push_back({0, 2 * (size / 3), (size / 3)});
        best_answer.push_back({(size / 3), 2 * (size / 3), (size / 3)});
        best_answer.push_back({2 * (size / 3), 2 * (size / 3), (size / 3)});
#ifdef DEBUG
        best_matrix = matrix;
#endif
        return 6;
    }

    int check_composite()
    {
        for (int i = 2; i <= sqrt(size); i++)
        {
            if (size % i == 0)
            {
                return i;
            }
        }
        return 0;
    }

    int set_base_composite(int temp)
    {

        Work temp1(temp);

        best_count_square = 0;
        for (auto &per : temp1.best_answer)
        {
            best_count_square++;
            per.x *= size / temp;
            per.y *= size / temp;
            per.size *= size / temp;
            for (int i = per.x; i < per.x + per.size; i++)
            {
                for (int j = per.y; j < per.y + per.size; j++)
                {
                    matrix[i][j] = best_count_square;
                }
            }
        }
#ifdef DEBUG
        best_matrix = matrix;
#endif
        best_answer = temp1.best_answer;
        best_count_square = temp1.best_count_square;
        return 1;
}

    void set_base_square()
    {
        current_answer[0] = {0, 0, (size + 1) / 2};
        current_answer[1] = {(size + 1) / 2, 0, (size - 1) / 2};
        current_answer[2] = {0, (size + 1) / 2, (size - 1) / 2};
        set_square(0, 0, (size + 1) / 2);
        set_square((size + 1) / 2, 0, (size - 1) / 2);
        set_square(0, (size + 1) / 2, (size - 1) / 2);
    }

    void set_square(int x, int y, int width)
    {
        current_count_square++;
        for (int i = x; i < x + width; i++)
        {
            for (int j = y; j < y + width; j++)
            {
                matrix[i][j] = current_count_square;
            }
        }
    }
};

int main()
{
    int size;
    std::cin >> size;
    auto start = clock();
    Work temp(size);
#ifdef CLOCK
    std::cout << "Time to complite: " << (double)(clock() - start) / CLOCKS_PER_SEC << std::endl;
#endif
    std::cout << temp.best_count_square << '\n';
    temp.print_answer();
#ifdef DEBUG
     std::cout << "\nFinal matrix: \n"; 
     temp.print_best_matrix();
#endif

    return 0;
}
