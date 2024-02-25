#include <iostream>
#include <vector>
#include <iterator>

int main() {
    std::istream_iterator<int> start(std::cin), end; // чтение данных из стандартного ввода
    std::vector<int> numbers(start, end); // инициализация вектора считанными числами

    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    return 0;
}
