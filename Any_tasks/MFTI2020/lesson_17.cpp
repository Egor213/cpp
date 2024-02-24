#include <cassert>
#include <iostream>
#include <vector>
#include <type_traits>
#include <functional>

void print() {}
//Args - это пакет типов, его можно распаковывать с помощью ... в конце
//args - заданная переменная, пакет аргументов
template <typename ... Args>
void print(const Args&... args)
{
    (std::cout << ... << args) << '\n'; // можно вывести так
}

template<typename T>
class C
{
    C() = delete;
};

template <typename T>
void f(T x)
{
    C<T>();
} // благодаря такой штуке можно во время компиляции узнать тип подаваемой переменной.




int main()
{
 //   print("123", 3, 4.0, 'a');
    int a = 10;
    int& y = a;
   // f(y);
    //f<int&>(y) - передаст ссылку на инт
    // как не пытаися передать по нормальному ссылку не получается
    // но std::ref решает эту проблему
    // он создает класс референс враппер который работает почти как ссылка
    //f(std::ref(a)); - теперь a передается почти как ссылка, у а нельзя будет менять значение
    // но есть метод get, который возвращает настояющую ссылку

   // std::vector v {1,2,3};

    return 0;
}
