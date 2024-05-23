#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <unordered_map>
#include <set>
#include <queue>
#include <sstream>

class Node
{
public:
    char symbol = '0';
    char parent_char = '0';
    bool terminal;
    std::size_t len_word = 0;
    std::size_t size_pattern = 0;
    std::vector<std::size_t> position;
    std::unordered_map<char, Node *> children;
    Node *sufflink = nullptr;
    Node *parent = nullptr;
    Node(bool terminal = false) : terminal(terminal) {}
    ~Node()
    {
        for (auto &pair : children)
        {
            delete pair.second;
        }
    }
};

class Trie
{
private:
    Node root;
    std::vector<std::pair<int, int>> answer;
    std::vector<int> counter;

public:
    Trie(const std::string &string)
    {
        counter.resize(string.size());
    }

    void printCounter(int size_pattern, int count_subwords)
    {
        /* for (auto &per : counter)
            std::cout << per << ' ';
        std::cout << std::endl; */
        std::vector<int> ans;
        for (int i = 0 ; i < counter.size(); i++)
        {
            if (i <= counter.size()-size_pattern && counter[i] == count_subwords)
                ans.push_back(i + 1);
        }
        std::sort(ans.begin(), ans.end());
        for (auto& per : ans)
            std::cout << per << '\n';
     //   std::cout << '\n';
    }

    void addWord(const std::string &input_string, std::size_t id)
    {
        Node *temp_root = &root;
        for (auto &symbol : input_string)
        {
            if (temp_root->children.count(symbol) == 0)
            {
                temp_root->children[symbol] = new Node();
                temp_root->children[symbol]->symbol = symbol;
                temp_root->children[symbol]->parent = temp_root;
                temp_root->children[symbol]->parent_char = temp_root->symbol;
            }
            temp_root = temp_root->children[symbol];
        }
        temp_root->position.push_back(id);
        temp_root->len_word = input_string.length();
        temp_root->terminal = true;
    }

    void setSufflinks()
    {
        bfs();
    }

    void printAnswer()
    {
        std::sort(std::begin(answer), std::end(answer));
        for (auto &&per : answer)
        {
            std::cout << per.first << ' ' << per.second << '\n';
        }
    }

    void solve(const std::string &string)
    {

        Node *current = &root;
        for (auto i = 0; i < string.length(); i++)
        {
            char b = string[i];
            if (current->children.count(string[i]))
            {
                current = current->children[string[i]];
            }
            else if (current->symbol == '0')
            {
          //      checkFindWord(current, i);
                continue;
            }
            else
            {
                Node *suf_node = current->sufflink;
                while (suf_node->children.count(string[i]) == 0 && suf_node->symbol != '0')
                {
                    suf_node = suf_node->sufflink;
                }
                if (suf_node->children.count(string[i]))
                {
                    current = suf_node->children[string[i]];
                }
                else if (suf_node->symbol == '0')
                {
                    current = &root;
                }
            }
            checkFindWord(current, i);
        }
    }

private:
    void checkFindWord(Node *node, int index)
    {
        Node *current = node;
        while (current->symbol != '0')
        {
            if (current->terminal)
            {
                for (auto &per : current->position)
                {
                    if (index - current->len_word + 1 - per >= 0 && index - current->len_word + 1 - per < counter.size())
                        counter[index - current->len_word + 1 - per] += 1;
                }
                    
            }

            current = current->sufflink;
        }
    }

    void createSufflink(Node *node)
    {
        if (node->symbol == '0')
        {
            return;
        }
        if (node->parent_char == '0')
        {
            node->sufflink = node->parent;
            return;
        }
        Node *parent = node->parent;
        Node *suf_parent = parent->sufflink;
        while (suf_parent->children.count(node->symbol) == 0 && suf_parent->symbol != '0')
        {
            suf_parent = suf_parent->sufflink;
        }
        if (suf_parent->children.count(node->symbol))
        {
            node->sufflink = suf_parent->children[node->symbol];
        }
        else if (suf_parent->symbol == '0')
        {
            node->sufflink = suf_parent;
            return;
        }
    }

    void bfs()
    {
        std::queue<Node *> queue({&root});
        while (!queue.empty())
        {
            Node *current = queue.front();
            queue.pop();
            createSufflink(current);
            for (auto &[_, node] : current->children)
            {
                queue.push(node);
            }
        }
    }
};

/*

aab
abba
bbab
bbbab



*/

auto splitString(const std::string &string, char joker)
{
    std::vector<std::string> answer;
    std::stringstream ss(string);
    std::string token;
    while (std::getline(ss, token, joker))
    {
        if (token.length() > 0)
            answer.push_back(token);
    }
    return answer;
}

auto getPositions(const std::string &string, char joker)
{
    std::vector<int> answer;
    for (int i = 0; i < string.size(); i++)
    {
        if (string[i] != joker)
        {
            answer.push_back(i);
            while (i < string.size() && string[i] != joker)
            {
                i++;
            }
        }
    }
    return answer;
}

int main()
{

    std::string input_string;
    std::string pattern;
    char joker;
    std::cin >> input_string >> pattern >> joker;
    Trie temp(input_string);
    auto position = getPositions(pattern, joker);
    /* for (auto per : position)
        std::cout << per << ' ';
    std::cout << std::endl; */
    auto substring = splitString(pattern, joker);

    for (int i = 0; i < substring.size(); i++)
    {
        temp.addWord(substring[i], position[i]);
    }
    temp.setSufflinks();


    temp.solve(input_string);
    // temp.printAnswer();
    temp.printCounter(pattern.size(), substring.size());
    return 0;
}
