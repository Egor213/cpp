#include <cassert>
#include <iostream>
#include <vector>
#include <type_traits>
template<int T>
struct Fibonacci
{
    static const long long value =  Fibonacci<T - 1>::value + Fibonacci<T - 2>::value;
};

template<>
struct Fibonacci<1>
{
    static const long long value = 1;
};


template<>
struct Fibonacci<0>
{
    static const long long value = 0;
};


template<size_t N, size_t D>
struct isPrimeHelper
{
    static const bool value = N % D == 0 ? false : isPrimeHelper<N, D - 1>::value;
};

template<size_t N>
struct isPrimeHelper<N, 1>
{
    static const bool value = true;
};

template<int N>
struct isPrime
{
    static const bool value = isPrimeHelper<N, N - 1>::value;
};



template <typename T, template <typename> class Conteiner = std::vector>
struct Stack
{
    Conteiner<T> c;
};



template<typename T>
struct remove_const
{
    using type = T;
};

template<typename T>
struct remove_const<const T>
{
    using type = T;
};

template<typename T>
using remove_const_t = typename remove_const<T>::value;



template<typename T, typename U>
struct is_same
{
    static const bool value = false;
};

template<typename T>
struct is_same<T, T>
{
    static const bool value = true;
};




int main()
{
    
    return 0;
}
