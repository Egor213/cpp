#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <fstream>
#include <random>
#include <math.h>
#include <stdexcept>

struct Node;

using Graph = std::map<char, std::vector<Node>>;

struct Node
{
    char to;
    float weight;
    Node(char to, float weight) : to(to), weight(weight) {}
};

int generate_number(const int left_border, const int right_border)
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<int> range_number(left_border, right_border);
    return range_number(generator);
}

std::vector<int> init_random_vector_by_graph(const int size, const int graph_size)
{
    std::vector<int> indexes_delete;
    for (auto i = 0; i < size; i++)
    {
        int random_number = generate_number(0, graph_size - 1);
        while (auto it_find = std::find(indexes_delete.begin(), indexes_delete.end(), random_number) != indexes_delete.end())
        {
            random_number = generate_number(0, graph_size - 1);
        }
        indexes_delete.push_back(random_number);
    }
    return indexes_delete;
}

void delete_elem_vec(Graph &graph, const int index_del)
{
    int count_index = 0;
    for (auto &node : graph)
    {
        if (index_del >= count_index && index_del < count_index + node.second.size())
        {
            node.second.erase(node.second.begin() + (index_del - count_index));
            return;
        }
        else
        {
            count_index += node.second.size();
        }
    }
}

void random_cut_graph(Graph &graph, const float fullnes)
{
    int full_count_edge = (graph.size() * (graph.size() - 1));
    int count_edge = std::ceil(full_count_edge * fullnes);
    std::vector<int> indexes_delete = init_random_vector_by_graph(full_count_edge - count_edge, full_count_edge);
    std::sort(indexes_delete.begin(), indexes_delete.end(), std::greater<int>());
    for (const auto index : indexes_delete)
    {
        delete_elem_vec(graph, index);
    }
}

Graph generate_full_graph(const int size)
{
    Graph graph;
    for (auto i = 'a'; i - 'a' < size; i++)
    {
        for (auto j = 'a'; j - 'a' < size; j++)
        {
            if (i == j)
            {
                continue;
            }
            graph[i].emplace_back(j, generate_number(1, 100));
        }
    }
    return graph;
}

std::pair<char, char> generate_start_end(const int size)
{
    char start = generate_number(0, size - 1) + 'a';
    char end = generate_number(0, size - 1) + 'a';
    while (char end = (generate_number(0, size - 1) + 'a') == start)
    {
    }
    return std::make_pair(start, end);
}

template <typename Descriptor = std::ostream>
void output_date(const Graph &graph, const int graph_size, Descriptor &out = std::cout)
{
    std::pair<char, char> start_end = generate_start_end(graph_size);
    out << start_end.first << ' ' << start_end.second << '\n';
    for (const auto &node : graph)
    {
        for (const auto &way : node.second)
        {
            out << node.first << ' ' << way.to << ' ' << way.weight << '\n';
        }
    }
}

int main()
{
    int graph_size = 0;
    std::cin >> graph_size;
    if (graph_size < 0 || graph_size > 30)
        throw std::runtime_error("Неверно заданно количество вершин!");
    Graph graph = generate_full_graph(graph_size);
    random_cut_graph(graph, 0.25);
    std::ofstream file("Random_graph.txt");
    output_date(graph, graph_size, file);
}
