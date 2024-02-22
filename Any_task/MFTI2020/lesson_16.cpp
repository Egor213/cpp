#include <cassert>
#include <iostream>
#include <vector>
#include <type_traits>

template <typename T>
struct S
{
    using x = T;
};

template<>
struct S<int>
{
    static int x;
};

template<typename T>
void f()
{
    //S<T>::x a; здесь компилятору будет не понятно x это тип или значение
    typename S<T>::x a; //так он будет считать названием типа

}



template <typename T>
struct Base 
{
    int x;
};


template <typename T>
struct Derived : Base<T>
{
    void f()
    {
        //x = 1; x будет не найдет так как компилятор на этапе компиляции 
        //не смотрит что находится в классе родителе, поэтому он не знает о существовании х
        this->x = 10;
        Base<T>::x = 11;
    }
};

//ленивое инстанцирование это когда есть шаблонный класс и в случае создания
//его экземпляра компилятор не будет инициализировать методы класса, а только поля
//поэтому не выдаст сразу ошибки. 
//Если использовать ссылки или указатели на шаблонный класс, то инициализация полей тоже не будет проходить
//и не вызовет никаких ошибок
//эксплисинг инстанцирование это когда явно говоришь компилятору
//инициализировать структуру + методы.
//template struct S<int, 1>;
//если к методу добавить virtual то она будет инициализирована
//Виртуальные методы не могут быть шаблонными

template <int N>
struct Danger
{
    int a[N];
};

template<typename T, int N>
struct S2
{
    
    void f()
    {
        Danger<N> d;
    }

    void g()
    {
        Danger<-1> d;
    }
};

//template struct S2<int, -1>; с ней уже не будет работать


void print() {}
//Args - это пакет типов, его можно распаковывать с помощью ... в конце
//args - заданная переменная, пакет аргументов
template <typename Head, typename ... Args>
void print(const Head& head, const Args&... args)
{
    std::cout << head << ' ';
    print(args...);
}

int main()
{
    print("123", 3, 4.0, 'a');
    //S2<int, -1> a; // будет работать

    return 0;
}
