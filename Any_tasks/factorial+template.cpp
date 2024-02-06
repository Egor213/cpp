#include <iostream>
#include <string>
#include <type_traits>

template <typename T = uint64_t>
constexpr T factorial(T&& number)
{
    if (!number)
        return 1;
    return factorial(number - 1) * number;
} 

template <typename T = uint64_t>
constexpr T factorial(T& number)
{
   return factorial(static_cast<T&&>(number));
}



template <uint64_t Number>
class Factor {
public:
    static constexpr uint64_t res = Factor<Number - 1>::res * Number;
};

template <>
class Factor<0> {
public:
    static constexpr uint64_t res = 1;
}; 


int main()
{
    uint64_t a = 3;
    std::cout << factorial(a) << std::endl;
    constexpr auto result = factorial(4);
    std::cout << result << std::endl;
    return 0;
}
