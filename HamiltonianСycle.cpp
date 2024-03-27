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

struct Edge;

using ld = long double;
using Graph = std::unordered_map<char, std::deque<Edge>>;

class Edge
{
public:
    const char end_node;
    const ld weight;
    Edge(const char end_node, const ld weight) : end_node(end_node), weight(weight) {}
    /*     bool operator==(const Edge &other) const
        {
            return ((start_node == other.start_node && end_node == other.end_node) ||
                    (start_node == other.end_node && end_node == other.start_node)) &&
                   (weight == other.weight);
        } */
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
        return getCorrectPath();
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

        for (const auto &adjacent_edge : graph.at(current_node))
        {
            if (!checkInCointeiner(visited_nodes, adjacent_edge.end_node))
            {
                visited_nodes.push_back(current_node);
                current_cost += adjacent_edge.weight;
                current_path += adjacent_edge.end_node;
                backtracking(adjacent_edge.end_node);
                current_cost -= adjacent_edge.weight;
                current_path.pop_back();
            }
        }
    }

    [[nodiscard]] const std::string getCorrectPath() const
    {
        if (checkCorrectPath())
        {
            return best_path;
        }
        return "Нет цикла!";
    }

    [[nodiscard]] const bool checkCorrectPath() const
    {
        return best_path.length() > 1;
    }

    void processingFinish(const char node)
    {
        current_cost += getMinPath(node);
        if (checkBestPath())
        {
            best_cost = current_cost;
            best_path = current_path;
        }
    }

    [[nodiscard]] const ld getMinPath(const char node)
    {
        auto compare = [node](const Edge &first, const Edge &second)
        {
            return first.weight < second.weight;
        };
        auto min_edge_it = std::min_element(std::begin(graph.at(node)), std::end(graph.at(node)), compare);
        return (*min_edge_it).weight;
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
