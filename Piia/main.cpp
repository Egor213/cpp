#include "ham_cycle.hpp"

int main()
{
    std::ifstream file("input.txt");
    Graph graph = readGraph(file);
    for (auto&& per : graph)
    {
        std::cout << per.first << " ----> ";
        for (auto&& per1 : per.second)
        {
            std::cout << per1.end_node << " : " << per1.weight << ", ";
        }
        std::cout << std::endl;
    }
    printAnswer(graph);
    return 0;
}