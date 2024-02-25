#include <iostream>
#include <thread>

void foo()
{
    for (int i = 0; i < 10; i++)
    {
        std::cout << "foo\n";
    }
}

int main()
{
    std::thread t(foo);
    t.detach(); // говорит потоку, что он может работать независимо, но когда основной проток завершится то и этот тоже
    for (int i = 0; i < 10; i++)
    {
        std::cout << "main\n";
    }
    //t.join() // теперь поток t будет завершон, основной поток будет ждать поток t

    return 0;
}
