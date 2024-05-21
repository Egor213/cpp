#include <iostream>
#include <thread>

int sum(int a, int b)
{
    return a + b;
}

int main()
{
    int result;
    std::thread t([&result]()
                  { result = sum(2, 5); });
    t.join();
    std::cout << result << std::endl;

    return 0;
}
