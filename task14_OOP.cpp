Utilities
Hastebin
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <concepts>


template<typename Type>
class ToSortContainer
{
private:
    std::vector<Type> data;

public:
    ToSortContainer(std::initializer_list<Type> init_list) : data(init_list) {}

    template<typename Func>
    auto getSortedBy(const Func& func)
    {
        std::vector<Type> temp(data.begin(), data.end());
        std::sort(temp.begin(), temp.end(), func);
        return temp;
    }

    
};

int main()
{
    ToSortContainer<int> tsc = {2,3,-4,1,6};
    auto x = tsc.getSortedBy(std::greater<int>());
    auto y = tsc.getSortedBy([](auto x, auto y){return x < y;});
    for (const auto& per : x)
    {
        std::cout << per << ' ';
    }
    std::cout << '\n';
    for (const auto& per : y)
    {
        std::cout << per << ' ';
    }
    std::cout << '\n';
    return 0;
}
Hire World Class Talent with Toptal
HTML5 Developers
JavaScript Developers
PHP Developers
Front-end Developers
CSS3 Developers
PrestaShop Developers
Hyperledger Developers
WPF Developers
Software Developers
NFT Developers
Marketo Developers
OpenCart Developers
Umbraco Developers
Hive Developers
Freelance Coders
Hire the top 3% of freelance talent
Join the Toptal Network
Copyright 2010 - 2024 Toptal, LLC

Privacy Policy
Website terms
By continuing to use this site you agree to our Cookie Policy Privacy Policy, and Terms of Use.

Got it
