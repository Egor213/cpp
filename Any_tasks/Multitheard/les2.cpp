#include <iostream>
#include <thread>

void foo(int a, int b)
{
    for (int i = 0; i < 10; i++)
    {
        std::cout << a + b << " - foo\n";
    }
}

int main()
{   
    std::thread t(foo, 1, 2);
    //t.detach(); // говорит потоку, что он может работать независимо, но когда основной проток завершится то и этот тоже 
    for (int i = 0; i < 10; i++)
    {
        std::cout << "main\n";
    }
    t.join(); // теперь поток t будет завершон, основной поток будет ждать поток t
    

    return 0;
}
