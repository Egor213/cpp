#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <concepts>

class CaesarEncrypt
{
private:
    std::size_t shift;

public:
    CaesarEncrypt(std::size_t input_shift) : shift(input_shift)
    {
        if (shift > 25 || shift < 0)
            shift = 25;
    }

    std::string encrypt(const std::string& input_string)
    {
        std::string temp = input_string;
        for (auto& per : temp)
        {
            if (std::isalpha(per))
            {
                char aphavit_word = std::isupper(per) ? 'A' : 'a';
                per = ((per + shift - aphavit_word) % 26) + aphavit_word;
            }
        }
        return temp;
    }

    std::string decrypt(const std::string& input_string)
    {
        std::string temp = input_string;
        for (auto& per : temp)
        {
            if (std::isalpha(per))
            {
                char aphavit_word = std::isupper(per) ? 'A' : 'a';
                int temp_sum = per - shift - aphavit_word;
                
                per = (temp_sum < 0 ? temp_sum+=26 : temp_sum % 26) + aphavit_word;
            }
        }
        return temp;
    }



    
};

int main()
{
    CaesarEncrypt temp(10);
    std::string a = "hGh wor&?ld";
    std::string b = temp.encrypt(a);
    std::cout << b << '\n';
    std::cout << temp.decrypt(b) << '\n';
    return 0;
}
