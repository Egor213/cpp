#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <deque>
#include <algorithm>
#include <set>

class Node;

using ld = long double;
using Graph = std::map<char, std::vector<Node>>;

struct Node
{
    char to;
    ld weight;
};

Graph read_graph()
{
    Graph graph;
    char from, to;
    ld weight;
    while (std::cin >> from >> to >> weight)
    {
        graph[from].emplace_back(to, weight);
    }
    return graph;
}

void print(Graph graph)
{
    for (const auto &node : graph)
    {
        for (auto way : node.second)
        {
            std::cout << node.first << " --> " << way.to << " Weight: " << way.weight << '\n';
        }
    }
}

char get_min_way(std::vector<Node> ways, std::set<char> visited_nodes)
{
    ld min = INT16_MAX;
    char node = '-';
    for (auto &way : ways)
    {
        auto it = std::find(visited_nodes.begin(), visited_nodes.end(), way.to);
        if (way.weight < min && it == visited_nodes.end())
        {
            min = way.weight;
            node = way.to;
        }
    }
    return node;
}

std::string get_way(Graph &graph, char from, const char to)
{
    std::set<char> visited_nodes({from});
    std::string answer(1, from);
    std::deque<char> queue({from});
    while (queue.front() != to)
    {
        char temp = get_min_way(graph[queue.front()], visited_nodes);
        if (temp == '-')
        {
            answer.pop_back();
            queue.pop_front();
            continue;
        }
        answer += temp;
        visited_nodes.insert(temp);
        queue.push_front(temp);
        if (visited_nodes.size() == graph.size() && queue.front() == to)
        {
            return "";
        }
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
