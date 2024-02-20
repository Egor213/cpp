#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <cmath>
#include <cstring>

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
    std::vector<Square> best_answer;
    std::vector<Square> current_answer;
    int max_count_square;
    int current_count_square;
    int best_count_square;

public:
    Work(int size) : size(size), current_count_square(0), best_count_square(INT16_MAX),
                     matrix(size, std::vector<int>(size, 0)), best_matrix(size, std::vector<int>(size, 0))
    {

        int temp = check_composite();
        if (temp)
        {
            set_base_composite(temp);
        }
        else
        {
            default_work();
            backtraking();
        }
    }

    void print_answer()
    {
        for (int i = 0; i < best_count_square; i++)
        {
            std::cout << best_answer[i].x << ' ' << best_answer[i].y
                      << ' ' << best_answer[i].size << '\n';
        }
    }

private:
    void backtraking()
    {
        if (current_count_square >= best_count_square || current_count_square > max_count_square)
        {
            return;
        }
        auto coords = get_free_cell();
        if (coords.first == -1)
        {
            if (current_count_square < best_count_square)
            {
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

    void default_work()
    {
        max_count_square = size * 2;
        best_answer.resize(max_count_square);
        current_answer.resize(max_count_square);
        set_base_square();
    }

    std::pair<int, int> get_free_cell()
    {
        for (int y = (size - 1) / 2; y < size; y++)
        {
            for (int x = (size - 1) / 2; x < size; x++)
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

    void set_base_composite(int temp)
    {
        Work temp1(temp);
        for (auto &per : temp1.best_answer)
        {
            per.x *= size / temp;
            per.y *= size / temp;
            per.size *= size / temp;
            set_square(per.x, per.y, per.size);
        }
        best_answer = temp1.best_answer;
        best_count_square = temp1.best_count_square;
    }

    void set_base_square()
    {
        int place_size = std::ceil((size - 1) / 2.0);
        int place_first_square = (size + 1) / 2;
        current_answer[0] = {0, 0, place_first_square};
        current_answer[1] = {place_first_square, 0, place_size};
        current_answer[2] = {0, place_first_square, place_size};
        set_square(0, 0, place_first_square);
        set_square(place_first_square, 0, place_size);
        set_square(0, place_first_square, place_size);
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
    Work temp(size);
    std::cout << temp.best_count_square << '\n';
    temp.print_answer();
    return 0;
}
