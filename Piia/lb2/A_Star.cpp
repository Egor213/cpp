#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>

struct Edge;

using Graph = std::map<char, std::vector<Edge>>;

struct Edge
{
    char node;
    float weight;
    Edge(char node, int weight) : node(node), weight(weight) {}
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

class A_star
{
private:
    std::vector<char> open_list;
    std::map<char, char> from_map;
    Graph graph;
    const char start;
    const char end;
    std::map<char, int> distance;

public:
    A_star(const char start, const char end, Graph temp) : start(start), end(end),
                                                           open_list({start}), distance({{start, 0}}),
                                                           graph(temp) {}

    std::string get_way()
    {
        char current = -1;
        while (!open_list.empty() && current != end)
        {
            current = get_min_full_dist(open_list);
            open_list.erase(std::remove(open_list.begin(), open_list.end(), current), open_list.end());
            for (const auto &[neighbor, weight] : graph[current])
            {
                process_neighbor(neighbor, weight, current);
            }
        }
        return make_path(from_map);
    }

private:

    template <typename Container, typename Object>
    bool check_in(Container conteiner, Object elem)
    {
        return std::find(conteiner.begin(), conteiner.end(), elem) != conteiner.end();
    }


    void process_neighbor(char node, float weight, char current)
    {
        auto temp_dist = distance[current] + weight;
        if (distance.find(node) == distance.end() || temp_dist < distance[node])
        {
            from_map[node] = current;
            distance[node] = temp_dist;
            if (!check_in(open_list, node)) 
            {
                open_list.push_back(node);
            }
        }
    }

    float heuristic_function(const char start, const char end)
    {
        return abs(start - end);
    }

    char get_min_full_dist(const std::vector<char> &node_list)
    {
        auto it = std::min_element(node_list.begin(), node_list.end(), [&](const char &first, const char &second)
                                   { return distance[first] + heuristic_function(end, first) < distance[second] + heuristic_function(end, second); });
        return *it;
    }

    std::string make_path(std::map<char, char> &from_map)
    {
        char current = end;
        std::string path = "";
        if (from_map.find(end) == from_map.end())
        {
            return "Нет пути!\n";
        }
#ifdef DEBUG
        int len_path = 0;
#endif
        for (; current != start; current = from_map[current])
        {
#ifdef DEBUG
            for (auto per : graph[from_map[current]])
            {
                if (per.node == current)
                {
                    len_path += per.weight;
                    break;
                }
            }
#endif
            path.push_back(current);
        }
        path.push_back(current);
        std::reverse(path.begin(), path.end());
#ifdef DEBUG
        std::cout << "длина пути " << len_path << ' ' <<  path <<'\n';
#endif
        return path;
    }
};

int main()
{
    char start, finish;
    std::cin >> start >> finish;
    Graph graph = read_graph();
    A_star temp(start, finish, graph);
#ifdef DEBUG
    temp.get_way();
#else
    std::cout << temp.get_way() << '\n';
#endif
    return 0;
}
