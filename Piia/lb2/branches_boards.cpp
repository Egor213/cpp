#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <string>

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

class Branch_board
{
private:
    int best_cost;
    int current_cost;
    std::string current_path;
    std::string best_path;
    Graph graph;
    const char start;
    const char end;

public:
    Branch_board(const char start, const char end, Graph graph) : best_cost(INT16_MAX), current_cost(0),
                                                                  start(start), end(end), graph(graph), current_path({start})
    {
    }

    std::string get_way()
    {
        backtracking(start);

#ifdef DEBUG

        if (best_cost == INT16_MAX)
        {
            std::cout << "Нет пути\n";
            return "";
        }
        else
        {
            std::cout << "длина пути " << best_cost << ' ' << best_path << '\n';
        }
#endif

        return best_cost == INT16_MAX ? "Нет пути" : best_path;
    }

    const int get_len_path() const
    {
        return best_cost;
    }

private:
    void backtracking(const char node)
    {
        if (current_cost < best_cost && node == end)
        {
            best_cost = current_cost;
            best_path = current_path;
            return;
        }

        if (current_cost >= best_cost || node == end)
        {
            return;
        }

        for (const auto &[node, weight] : graph[node])
        {
            process_node(node, weight);
        }
    }

    template <typename Container, typename Object>
    bool check_in(Container conteiner, Object elem)
    {
        return std::find(conteiner.begin(), conteiner.end(), elem) != conteiner.end();
    }

    void process_node(const char node, const int weight)
    {
        if (!check_in(current_path, node))
        {
            current_cost += weight;
            current_path += node;
            backtracking(node);
            current_cost -= weight;
            current_path.pop_back();
        }
    }
};

int main()
{
    char start, end;
    std::cin >> start >> end;
    Graph graph = read_graph();
    Branch_board a(start, end, graph);
#ifdef DEBUG
    a.get_way();
#else
    std::cout << a.get_way();
#endif
    return 0;
}
