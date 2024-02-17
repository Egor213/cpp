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

class Node
{
private:
    char to_;
    ld weight_;

public:
    Node(const char to, ld weight) : to_(to), weight_(weight){};

    char getTo() const
    {
        return to_;
    }

    ld getWeight() const
    {
        return weight_;
    }
};

bool compare(Node& a, Node& b)
{
    return a.getTo() < b.getTo();
}

void sort_graph(Graph& graph)
{
    for (auto it = graph.begin(); it != graph.end(); it++)
    {
        std::sort(it->second.begin(), it->second.end(), compare);
    }
}

Graph read_graph()
{
    Graph graph;
    char from, to;
    ld weight;
    while (std::cin >> from >> to >> weight)
    {
        Node temp(to, weight);
        graph[from].push_back(temp);
    }
    return graph;
}

void print(Graph graph)
{
    for (const auto &node : graph)
    {
        for (auto way : node.second)
        {
            std::cout << node.first << " --> " << way.getTo() << " Weight: " << way.getWeight() << '\n';
        }
    }
}

char get_min_way(std::vector<Node> ways, std::set<char> visited_nodes)
{
    ld min = INT16_MAX;
    char node = '-';
    for (auto &way : ways)
    {
        auto it = std::find(visited_nodes.begin(), visited_nodes.end(), way.getTo());
        if (way.getWeight() < min && it == visited_nodes.end())
        {
            min = way.getWeight();
            node = way.getTo();
        }
    }
    return node;
}

std::string answer = "";

void get_way(Graph &graph, char from, const char to)
{
    std::set<char> visited_nodes;
    answer += from;
    
    std::deque<char> queue({from});

    while (queue.front() != to)
    {
        //std::cout << answer << '\n';
        char temp = get_min_way(graph[queue.front()], visited_nodes);

        if (temp == '-')
        {
            answer.pop_back();
            queue.pop_front();
            continue;
        }
        answer += temp;
        // std::cout << answer << '\n';
        visited_nodes.insert(temp);
        queue.push_front(temp);
    }
}

bool check_true_finish(char finish, Graph graph)
{
    for (const auto &node : graph)
    {
        for (auto way : node.second)
        {
            if (way.getTo() == finish)
                return true;
        }
    }
    return false;
}

int main()
{
    char start, finish;
    std::cin >> start >> finish;
    
    
    Graph graph = read_graph();

    

    bool check = check_true_finish(finish, graph);
    if (check)
    {
        sort_graph(graph);  
        get_way(graph, start, finish);
    }
    //print(graph);

    std::cout << answer << '\n';

    return 0;
}
