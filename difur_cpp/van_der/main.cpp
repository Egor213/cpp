#include <iostream>
#include <vector>
#include <cmath>
#include <Eigen/Dense>
#include <fstream>
#include <string>
#include "../csvfile.h"
#include <iomanip> 
#include "../tables.h"
#include <chrono>
#define ld long double
#define lli long long int





std::vector<ld> van_der_pole(const std::vector<ld>& state, ld m) {
    ld x = state[0];
    ld y = state[1];
    ld dxdt = y;
    ld dydt = m * (1 - x * x) * y - x;
    return {dxdt, dydt};
}

template <typename T>
void printV(const std::vector<T>& vec)
{
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << std::fixed << std::setprecision(10) <<  vec[i] << ' ';
    }
}

class RungeKutta {
public:
    using Func = std::vector<ld>(*)(const std::vector<ld>&, ld);

    RungeKutta(Func function, const std::vector<std::vector<ld>>& table) 
        : function(function), table(table) {}

    std::vector<ld> next_step(const std::vector<ld>& state, ld step, ld m) {
        std::vector<std::vector<ld>> array_k;
        array_k.push_back(function(state, m)); 
        for (size_t i = 0; i < table.size(); ++i) {
            std::vector<ld> arg(state.size(), 0.0);
            for (size_t j = 0; j < table[i].size(); ++j) {
                for (size_t k = 0; k < arg.size(); ++k) {
                    arg[k] += step * table[i][j] * array_k[j][k];
                }
            }
            for (size_t j = 0; j < arg.size(); ++j) {
                arg[j] += state[j];
            }
            array_k.push_back(function(arg, m));
        }
        std::vector<ld> res_state = state;
        for (size_t i = 0; i < table.back().size(); ++i) {
            for (size_t j = 0; j < res_state.size(); ++j) {
                res_state[j] += step * table.back()[i] * array_k[i][j];
            }
        }
        return res_state;
}

    std::vector<std::vector<ld>> solution(const std::vector<ld>& start_state, ld step, lli max_iteration, ld m) {
        std::vector<std::vector<ld>> all_steps;
        std::vector<ld> state = start_state;
        for (lli i = 0; i < max_iteration; ++i) {
            state = next_step(state, step, m);
            all_steps.push_back(state);
        }
        
        return all_steps;
    }

private:
    Func function;
    std::vector<std::vector<ld>> table;
};




int main() {
    ld m = 5.0;
    ld step = 0.01;
    lli max_iteration = 2 * 1e3;

    std::vector<ld> start_state = {1.0, 1.0};
    RungeKutta rk5(van_der_pole, dorman_prince_8_table);
    auto res = rk5.solution(start_state, step, max_iteration, m);
    try
    {
        csvfile csv("../data.csv"); 
        for (auto& per : res) {
            for (auto& arg : per)
                csv << arg;
            csv << endrow;
        }
            
    }
    catch (const std::exception& ex)
    {
        std::cout << "Exception was thrown: " << ex.what() << std::endl;
    }
  

    return 0;
}
