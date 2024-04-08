#include <gtest/gtest.h>
#include <optional>
#include "ham_cycle.hpp"
class GraphTests : public ::testing::TestWithParam<int>
{
};

template <typename Descriptor = std::istream>
std::optional<ld> readAnswer(const std::string& pattern, Descriptor &input = std::cin)
{
    std::string line;
    while (std::getline(input, line))
    {
        if (line.find(pattern) != std::string::npos)
        {
            std::istringstream iss(line);
            std::string key;
            ld number;
            iss >> key >> number;
            return number;
        }
    }
     return std::nullopt;
}

TEST_P(GraphTests, BBAndGreedy)
{
    int fileNumber = GetParam();
    std::string filename = "tests/test" + std::to_string(fileNumber) + ".txt";
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    Graph graph = readGraph(file);
    BranchesBoards temp1(graph);
    Greedy temp(graph);
    std::optional<ld> answer_bb = readAnswer("answerBB", file);
    std::optional<ld> answer_greedy = readAnswer("answerGreedy", file);
    file.close();

    EXPECT_NEAR(temp.getHamiltonianCycleCost(), answer_greedy.value(), 0.001);
    EXPECT_NEAR(temp1.getHamiltonianCycleCost(), answer_bb.value(), 0.001);
}

// Генерация параметров для теста
INSTANTIATE_TEST_SUITE_P(FileNumbers,
                         GraphTests,
                         ::testing::Range(1, 8)); 

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}