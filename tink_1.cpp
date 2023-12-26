#include <iostream>
#include <string>
#include <vector>

bool isTink(const std::string& s)
{
    std::vector<char> temp_vec = {'T','I','N','K','O','F','F'};
    std::vector<char> temp2_vec(s.begin(), s.end());
    return (temp_vec == temp2_vec) && s.length() == temp_vec.size();
}


int main() {
    int a;
    std::cin >> a;
    std::string line;
    while(std::cin >> line)
    {
        auto answer = isTink(line) ? "Yes" : "No";
        std::cout << answer << std::endl;   
    } 
    
    
    return 0;
}
