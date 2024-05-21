#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

struct Node;

using Graph = std::map<char, std::vector<Node>>;

struct Node
{
    char to;
    float weight;
    Node(char to, float weight) : to(to), weight(weight) {}
};

Graph read_graph()
{
    Graph graph;
    char from, to;
    float weight;
    while (std::cin >> from >> to >> weight)
    {
        graph[from].emplace_back(to, weight);
    }
    return graph;
}

class A_Star
{
private:
    std::vector<char> openSet;
    std::map<char, char> fromSet;
    Graph graph;
    const char start;
    const char end;
    std::map<char, float> G;

public:
    A_Star(const char start, const char end, Graph temp) : start(start), end(end),
                                                           openSet({start}), G({{start, 0}}),
                                                           graph(temp) {}

public:
    std::string get_way()
    {
        char current;
        while (!openSet.empty() && current != end)
        {
            current = min_f(openSet);
            openSet.erase(std::remove(openSet.begin(), openSet.end(), current), openSet.end());
            for (auto &neighbor : graph[current])
            {
                process_neighbor(neighbor.to, neighbor.weight, current);
            }
        }
        return make_path(fromSet);
    }

    void process_neighbor(char node, float weight, char current)
    {
        auto temp_dist = G[current] + weight;
        if (G.find(node) == G.end() || temp_dist < G[node])
        {
            fromSet[node] = current;
            G[node] = temp_dist;
            if (std::find(openSet.begin(), openSet.end(), node) == openSet.end())
            {
                openSet.push_back(node);
            }
        }
    }

    float h(const char start, const char end)
    {
        return abs(start - end);
    }

    char min_f(const std::vector<char> &set)
    {
        auto it = std::min_element(set.begin(), set.end(), [&](const char &elem1, const char &elem2)
                                   { return G[elem1] + h(end, elem1) < G[elem2] + h(end, elem2); });
        return *it;
    }

    std::string make_path(std::map<char, char> &fromSet)
    {
        char curr = end;
        std::string path = "";
        while (curr != start)
        {
            path.push_back(curr);
            curr = fromSet[curr];
        }
        if (path.size())
            path.push_back(curr);
        std::reverse(path.begin(), path.end());
        return path;
    }
};

int main()
{
    char start, finish;
    std::cin >> start >> finish;
    Graph graph = read_graph();
    A_Star temp(start, finish, graph);
    std::cout << temp.get_way();
    return 0;
}
