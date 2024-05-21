#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>
#include <set>
#include <stack>

struct Edge;

using Graph = std::map<char, std::vector<Edge>>;

struct Edge
{
    char node;
    float weight;
    Edge(char node, float weight) : node(node), weight(weight) {}
};

Graph read_graph()
{
    Graph graph;
    char from, node;
    float weight;
    while (std::cin >> from >> node >> weight)
    {
        graph[from].emplace_back(node, weight);
    }
    return graph;
}

template <typename Container, typename Object>
bool check_in(Container conteiner, Object elem)
{
    return std::find(conteiner.begin(), conteiner.end(), elem) != conteiner.end();
}

char get_min_way(const std::vector<Edge> &neighbors, const std::set<char> &visited_nodes)
{
    float min_weight = INT16_MAX;
    char min_node = -1;
    for (const auto &[neighbour, weight] : neighbors)
    {
        if (weight < min_weight && !check_in(visited_nodes, neighbour))
        {
            min_weight = weight;
            min_node = neighbour;
        }
    }
    return min_node;
}

std::string get_way(Graph &graph, const char from, const char node)
{
    std::set<char> visited_nodes({from});
    std::string answer(1, from);
    std::stack<char> stack({from});
    while (stack.top() != node && !stack.empty())
    {
        char min_node = get_min_way(graph[stack.top()], visited_nodes);
        if (min_node == -1)
        {
            answer.pop_back();
            stack.pop();
        }
        else
        {
            answer += min_node;
            visited_nodes.insert(min_node);
            stack.push(min_node);
        }
    }
    if (stack.empty())
    {
        return "Нет пути";
    }
    return answer;
}

int main()
{
    char start, finish;
    std::cin >> start >> finish;
    Graph graph = read_graph();
    std::cout << get_way(graph, start, finish) << std::endl;
    return 0;
}
