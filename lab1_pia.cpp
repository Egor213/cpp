#include <iostream>
#include <vector>
#include <time.h>
#include <deque>
#include <algorithm>
#include <climits>
#include <cmath>
class Square;


using Board = std::vector<Square>;
constexpr int MAX_COUNT = 80;

class Square
{
public:
    int x;
    int y;
    int size;

public:
    Square(int x, int y, int size) : x(x), y(y), size(size){};
};

int base_two(int size, Board &board)
{
    board.push_back({0, 0, size / 2});
    board.push_back({size / 2, 0, size / 2});
    board.push_back({0, size / 2, size / 2});
    board.push_back({size / 2, size / 2, size / 2});
    return 4;
}

int base_three(int size, Board &board)
{
    board.push_back({0, 0, 2 * (size / 3)});
    board.push_back({2 * (size / 3), 0, (size / 3)});
    board.push_back({2 * (size / 3), (size / 3), (size / 3)});
    board.push_back({0, 2 * (size / 3), (size / 3)});
    board.push_back({(size / 3), 2 * (size / 3), (size / 3)});
    board.push_back({2 * (size / 3), 2 * (size / 3), (size / 3)});
    return 6;
}

int check_base_variant(int size, Board &board)
{
    if (size % 2 == 0)
    {
        return base_two(size, board);
    }
    if (size % 3 == 0 && size != 3)
    {
        return base_three(size, board);
    }
    return 0;
}

// устанавливает 3 стандартных квадрата
void set_base_square(int size, Board &board)
{
    board.push_back({0, 0, (size + 1) / 2});
    board.push_back({(size + 1) / 2, 0, (size - 1) / 2});
    board.push_back({0, (size + 1) / 2, (size - 1) / 2});
}

// Проверяет по координатам свободна ли клетка
bool check_cell(const Board &board, int size, std::pair<int, int> coords)
{
    for (const auto &per : board)
    {
        if (coords.first >= per.x && coords.first < per.x + per.size && coords.second >= per.y && coords.second < per.y + per.size)
        {
            return false;
        }
    }
    return true;
}

// находит свободную клетку
std::pair<int, int> get_free_cell(int size, const Board &board)
{
    for (int y = (size - 1) / 2; y < size; y++)
    {
        for (int x = (size - 1) / 2; x < size; x++)
        {
            if (check_cell(board, size, std::make_pair(x, y)))
            {
                return std::make_pair(x, y);
            }
        }
    }
    return std::make_pair(-1, -1);
}
// проверяет можно ли добавить квадрат по заданным координатам
bool can_add_square(std::pair<int, int> coords, int size_square, int size_board, const Board &board)
{
    if (coords.first + size_square > size_board || coords.second + size_square > size_board)
    {
        return false;
    }
    for (int i = coords.first; i < coords.first + size_square; i++)
    {
        for (int j = coords.second; j < coords.second + size_square; j++)
        {
            if (!check_cell(board, size_board, std::make_pair(i, j)))
            {
                return false;
            }
        }
    }
    return true;
}



int is_composite(int size)
{
    for (int i = 2; i <= sqrt(size); i++)
    {
        if (size % i == 0)
        {
            return i;
        }
    }
    return -1;
}

int get_max_count_square(int size)
{
    int temp = is_composite(size);
    if (temp)
    {
        int min_one = 6 * int(std::log2(3 * temp - 1)) - 9;
        int min_two = 6 * int(std::log2(3 * (size / temp) - 1)) - 9;
        return std::min({min_one, min_two});
    }
    return 6 * int(std::log2(3 * temp - 1)) - 9;
}

void backtracking(int size, Board& board)
{
    std::deque<Board> deque({board});
    Board final_boards;
    int max_count_square = get_max_count_square(size);
    int best_result = INT32_MAX;
    while (!deque.empty())
    {
        Board temp = deque.front();
        deque.pop_front();  
        if (temp.size() > max_count_square || temp.size() > best_result)
        {
            continue;
        }
        std::pair<int, int> free_cell = get_free_cell(size, temp);
        if (free_cell.first == -1)
        {
            if (temp.size() < best_result)
            {
                best_result = temp.size();
                final_boards = temp;
            }
        }
        else
        {
            for (int i = std::min({(size - 1) / 2, size - free_cell.first, size - free_cell.second}); i > 0; i--)
            {
                if (can_add_square(free_cell, i, size, temp))
                {
                    Board new_temp = temp;
                    new_temp.push_back({free_cell.first, free_cell.second, i});
                    deque.push_back(new_temp);
                }
            }
        }   
    }
    std::cout << best_result << '\n';
    for (auto per : final_boards)
        std::cout << per.x << ' ' << per.y << ' ' << per.size << '\n';
}

int main()
{
    int size;
    std::cin >> size;

    Board board;
    board.reserve(MAX_COUNT);

    auto check = check_base_variant(size, board);

    if (!check)
    {
        set_base_square(size, board);
        backtracking(size, board);
    }
    else
    {
        std::cout << check << '\n';
        for (auto per : board)
        {
            std::cout << per.x << ' ' << per.y << ' ' << per.size << '\n';
        }
    }

    return 0;
}
