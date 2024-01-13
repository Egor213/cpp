#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <concepts>



class Interval
{
private:
    using ld = long double;
    const ld start;
    const ld end;

public:
    Interval(ld start, ld end) : start(std::min(start, end)), end(std::max(start, end)) {}

    constexpr ld len() const
    {
        return end - start;
    }
    
    constexpr bool in(double x)
    {
        if (abs(end - x) < 0.000001 || abs(x - start) < 0.000001)
            return true;
        return (x < end && x > start ) ? true : false;
    }

    std::vector<ld> split(int n)
    {
        ld step = len() / n;
        std::vector<ld> temp;
        ld temp_number = start;
        while (true)
        {
            temp.push_back(temp_number);
            temp_number += step;
            if ((end - temp_number) < 0.000001)
            {
                temp.push_back(end);
                break;
            }
                
        }
        return temp;
    }
};

int main()
{
    Interval temp(0.4, 0.1);
    std::cout << temp.len() << '\n';
    std::cout << temp.in(0.1) << '\n';
    std::vector<long double> v = temp.split(10);
    for (auto per : v)
        std::cout << per << '\n';
    std::cout << '\n';
    return 0;
}
