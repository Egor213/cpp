#include <iostream>
#include <thread>

void foo(int &a)
{
    a *= 2;
}

int main()
{   
    int q = 2;
    std::thread t(foo, std::ref(q));
    t.join();
    std::cout << q << std::endl; 

    return 0;
}
