#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <unordered_map>
#include <algorithm>
#include <concepts>
#include <iterator>
#include <limits>
#include <fstream>
#include <chrono>

struct Edge;

using ld = long double;
using Graph = std::unordered_map<char, std::deque<Edge>>;

class Edge
{
public:
    const char end_node;
    const ld weight;
    explicit Edge(const char end_node, const ld weight) : end_node(end_node), weight(weight) {}
};

template <typename Descriptor = std::istream>
Graph readGraph(Descriptor &input = std::cin)
{
    Graph graph;
    std::size_t size_graph;
    input >> size_graph;
    for (int i = 'a'; i < size_graph + 'a'; i++)
    {
        for (int j = 'a'; j < size_graph + 'a'; j++)
        {
            ld temp_weight;
            input >> temp_weight;
            if (temp_weight != -1)
            {
                graph[i].emplace_back(j, temp_weight);
            }
        }
    }
    return std::move(graph);
}





class HamiltonianСycle
{
private:
    const char start_node;
    ld best_cost;
    ld current_cost;
    std::string best_path;
    std::string current_path;
    std::deque<char> visited_nodes;
    const Graph &graph;

public:
    HamiltonianСycle(const Graph &graph) : start_node('a'), graph(graph),
                                           best_cost(std::numeric_limits<double>::max()),
                                           current_cost(0), visited_nodes{start_node},
                                           current_path{start_node}, best_path{""} {}

    const std::string getCyclePath()
    {
        backtracking(start_node);
        return best_path;
    }

    const ld getCycleCost() const
    {
        return best_cost;
    }


private:
    void backtracking(const char current_node)
    {
        if (current_cost > best_cost)
        {
            return;
        }

        if (checkFinish())
        {
            processingFinish(current_node);
            return;
        }

        for (const auto &[neighbour, weight] : graph.at(current_node))
        {
            if (!checkInCointeiner(visited_nodes, neighbour))
            {
                addAdjacentEdge(neighbour, weight, current_node);
                backtracking(neighbour);
                deleteAdjacentEdge(weight);
            }
        }
    }

    void addAdjacentEdge(const char node, const ld &weight, const char current_node)
    {
        visited_nodes.push_back(current_node);
        current_cost += weight;
        current_path += node;
    }

    void deleteAdjacentEdge(const ld &weight)
    {
        visited_nodes.pop_back();
        current_cost -= weight;
        current_path.pop_back();
    }

    void processingFinish(const char node)
    {
        current_cost += getLastWeight(node);
        if (checkBestPath())
        {
            best_cost = current_cost;
            best_path = current_path;
        }
        current_cost -= getLastWeight(node);
    }

    [[nodiscard]] const ld getLastWeight(const char last_node)
    {
        auto compare = [&](const Edge& current_node)
        {
            return current_node.end_node == start_node;
        };
        auto last_weight_it = std::find_if(std::begin(graph.at(last_node)), std::end(graph.at(last_node)), compare);
        return (*last_weight_it).weight;
    }

    [[nodiscard]] const bool checkBestPath() const noexcept
    {
        return current_cost < best_cost;
    }

    [[nodiscard]] const bool checkFinish() const noexcept
    {
        return visited_nodes.size() == graph.size();
    }

    template <typename Conteiner, typename Object>
    [[nodiscard]] const bool checkInCointeiner(const Conteiner &conteiner, const Object objeck) const
    {
        return std::find(std::begin(conteiner), std::end(conteiner), objeck) != std::end(conteiner);
    }
};




int main()
{
    std::ifstream file("input.txt");
    Graph graph = readGraph(file);
    HamiltonianСycle temp(graph);
    std::cout << "Path: " << temp.getCyclePath() << "\nCost: " << temp.getCycleCost() << std::endl;
    return 0;
}
