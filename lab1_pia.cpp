#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <cmath>
#include <cstring>
#define DEBU

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
    int **matrix;
    int **best_matrix;
    int iteration = 0;

    Square *best_answer = nullptr;
    Square *current_answer = nullptr;
    int max_count_square;
    int current_count_square;
    int best_count_square;
    int bool_prime = false;
    

public:
    Work(int size) : size(size), current_count_square(0), best_count_square(INT16_MAX)
    {
        matrix = new int *[size];
        for (int i = 0; i < size; i++)
        {
            matrix[i] = new int[size]{};
        }
#ifdef DEBUG
        best_matrix = new int *[size];
        for (int i = 0; i < size; i++)
        {
            best_matrix[i] = new int[size]{};
        }
#endif


        int check = check_base_variant();
        if (!check)
        {
            solve();
            backtraking();
        }
    }

    ~Work()
    {
#ifdef DEBUG
        for (int i = 0; i < size; i++)
            delete[] best_matrix[i];
        delete[] best_matrix;
#endif
        for (int i = 0; i < size; i++)
            delete[] matrix[i];
        delete[] matrix;
        delete[] best_answer;
        delete[] current_answer;
    }

    void solve()
    {
        int temp = check_composite();
        if (temp)
        {
            max_count_square = get_min_count_square(temp);
        }
        else
        {
            max_count_square = 6 * int(std::log2(3 * size - 1)) - 9;
        }
        best_answer = new Square[max_count_square]{};
        current_answer = new Square[max_count_square]{};
        if (check_prime())
        {
            bool_prime = true;
            set_base_square();
        }
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
                for(int i = 0; i < size; i++)
                {
                    std::copy(matrix[i], matrix[i] + size, best_matrix[i]);
                }
                std::cout << "Установленая новая матрица: " << '\n';
                print_best_matrix();
                std::cout << '\n';
#endif
                best_count_square = current_count_square;
                std::memcpy(best_answer, current_answer, sizeof(Square) * best_count_square);

            }
            return;
        }

        for (int i = std::min({size - 1, size - coords.first, size - coords.second}); i > 0; i--)
        {
            if (check_set_square(coords.first, coords.second, i))
            {
                current_answer[current_count_square++] = {coords.first, coords.second, i};
                set_square(coords.first, coords.second, i);
                backtraking();
                --current_count_square;
                del_square(coords, i);
            }
        }
    }

    void del_square(std::pair<int, int> coords, int width)
    {
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
        best_count_square = 4;
        best_answer = new Square[4];
        best_answer[0] = Square{0, 0, size / 2};
        best_answer[1] = Square{size / 2, 0, size / 2};
        best_answer[2] = Square{0, size / 2, size / 2};
        best_answer[3] = Square{size / 2, size / 2, size / 2};
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
        best_count_square = 6;
        best_answer = new Square[6];
        best_answer[0] = Square({0, 0, 2 * (size / 3)});
        best_answer[1] = Square({2 * (size / 3), 0, (size / 3)});
        best_answer[2] = Square({2 * (size / 3), (size / 3), (size / 3)});
        best_answer[3] = Square({0, 2 * (size / 3), (size / 3)});
        best_answer[4] = Square({(size / 3), 2 * (size / 3), (size / 3)});
        best_answer[5] = Square({2 * (size / 3), 2 * (size / 3), (size / 3)});
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

    int get_min_count_square(int temp)
    {
        return std::min((6 * int(std::log2(3 * size - 1)) - 9), (6 * int(std::log2(3 * (size / temp) - 1)) - 9));
    }

    bool check_prime()
    {
        std::vector<int> temp({5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 47});
        return std::find(temp.begin(), temp.end(), size) != temp.end();
    }

    void set_base_square()
    {
        current_answer[0] = {0, 0, (size + 1) / 2};
        current_answer[1] = {(size + 1) / 2, 0, (size - 1) / 2};
        current_answer[2] = {0, (size + 1) / 2, (size - 1) / 2};
        current_count_square++;
        set_square(0, 0, (size + 1) / 2);
        current_count_square++;
        set_square((size + 1) / 2, 0, (size - 1) / 2);
        current_count_square++;
        set_square(0, (size + 1) / 2, (size - 1) / 2);
    }

    void set_square(int x, int y, int width)
    {
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
    // temp.print_matrix();
    //temp.print_best_matrix();

    return 0;
}
