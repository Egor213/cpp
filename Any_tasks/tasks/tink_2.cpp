#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


std::size_t get_max_econom(std::vector<int>& vec, std::size_t& money1)
{
    std::sort(vec.begin(), vec.end());
    auto max = 0;
    auto money = money1 - vec[0];
    for (auto i = 1; i < vec.size(); i++)
    {
        size_t max_temp = std::max((vec[i] - 1 - vec[i - 1]), max);
        if (max_temp >= money)
            return money;
        else   
            max = max_temp;
        money -= vec[i];
    }
    if (max == 0 && money != 0)
        return money;
    return max;
}

int main()
{
     size_t a, money;
    std::cin >> a >> money;
    std::vector<int> temp(a);
    while (a != 0)
    {
        std::cin >> temp[--a];
    } 
    std::cout << get_max_econom(temp, money) << '\n';
    
    return 0;
}
