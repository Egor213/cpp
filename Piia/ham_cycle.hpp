#pragma once
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
    return graph;
}

template <typename Conteiner, typename Object>
[[nodiscard]] const bool checkInCointeiner(const Conteiner &conteiner, const Object objeck)
{
    return std::find(std::begin(conteiner), std::end(conteiner), objeck) != std::end(conteiner);
}

class BranchesBoards
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
    explicit BranchesBoards(const Graph &graph) : start_node('a'), graph(graph),
                                                  best_cost(std::numeric_limits<double>::max()),
                                                  current_cost(0), visited_nodes{start_node},
                                                  current_path{start_node}, best_path{""}
    {
        backtracking(start_node);
    }

    const std::string getHamiltonianCyclePath() const
    {
        return best_path;
    }

    const ld getHamiltonianCycleCost() const
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
        auto compare = [&](const Edge &current_node)
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
};

class Greedy
{
private:
    const char start_node;
    ld cost_path;
    std::deque<char> visited_nodes;
    std::string path;
    const Graph &graph;

public:
    explicit Greedy(const Graph &graph) : start_node('a'), graph(graph),
                                          cost_path(0), path{""}
    {
        createPath();
    }

    const std::string getHamiltonianCyclePath() const
    {
        return path;
    }

    const ld getHamiltonianCycleCost() const
    {
        return cost_path;
    }

private:
    void createPath()
    {
        std::string path{start_node};
        char curr_node = start_node;
        while (visited_nodes.size() + 1 != graph.size())
        {
            processingNode(curr_node, path);
        }
        cost_path += getLastWeight(curr_node);
        this->path = std::move(path);
    }

    void processingNode(char &curr_node, std::string &path)
    {
        visited_nodes.push_back(curr_node);
        const auto &[min_node, min_cost] = getMinWeight(curr_node);
        cost_path += min_cost;
        path += min_node;
        curr_node = min_node;
    }

    [[nodiscard]] const ld getLastWeight(const char last_node)
    {
        auto compare = [&](const Edge &current_node)
        {
            return current_node.end_node == start_node;
        };
        auto last_weight_it = std::find_if(std::begin(graph.at(last_node)), std::end(graph.at(last_node)), compare);
        return (*last_weight_it).weight;
    }

    [[nodiscard]] const std::pair<char, ld> getMinWeight(const char node)
    {
        std::pair<char, ld> min_node = {-1, INT16_MAX};
        for (const auto &[neighbour, weight] : graph.at(node))
        {
            if ((weight < min_node.second || !min_node.second) && !checkInCointeiner(visited_nodes, neighbour))
            {
                min_node = {neighbour, weight};
            }
        }
        return min_node;
    }
};

template <typename Output = std::ostream>
void printAnswer(const Graph &graph, Output &out = std::cout)
{
    BranchesBoards temp(graph);
    Greedy temp1(graph);
    out << "Path: " << temp.getHamiltonianCyclePath() << "\nCost: " << temp.getHamiltonianCycleCost() << std::endl;
    out << "Path: " << temp1.getHamiltonianCyclePath() << "\nCost: " << temp1.getHamiltonianCycleCost() << std::endl;
}
