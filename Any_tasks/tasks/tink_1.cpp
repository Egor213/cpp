#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
bool isTink(std::string &s)
{
    std::string temp = "FFIKNOT";
    std::sort(s.begin(), s.end());
    return temp == s;
}

int main()
{
    int a;
    std::cin >> a;
    std::string line;
    while (std::cin >> line)
    {
        auto answer = isTink(line) ? "Yes" : "No";
        std::cout << answer << std::endl;
    }
    return 0;
}
