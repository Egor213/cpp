#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <concepts>
#include <set>


template <typename Container>
concept GoodCont = requires(Container container, size_t index) {
    { container.at(index) } -> std::same_as<decltype(container.at(index))>;
    { container.erase(container.begin()) } -> std::same_as<typename Container::iterator>;
};


template <std::size_t Size>
class Mask
{
private:
    std::array<bool, Size> mask = {};

public:
    Mask() = default;

    Mask(std::initializer_list<bool> init_list)
    {
        if (init_list.size() != Size)
        {
            throw std::invalid_argument("Неверный размер входных данных!");
        }
        std::copy(init_list.begin(), init_list.end(), mask.begin());
    }


    constexpr std::size_t size() const
    {
        return Size;
    }

    constexpr bool at(std::size_t index) const
    {
        if (index >= Size) {
            throw std::out_of_range("Неверный индекс элемента!");
        }
        return mask[index];
    }

    template<GoodCont Conteiner>
    void slice(Conteiner& conteiner)
    {
        for (auto i = 0, j = 0; i < conteiner.size(); j++)
        {
            auto index_mask = j % Size;
            if (!mask[index_mask])
              conteiner.erase(conteiner.begin() + i);
            else
                i++;
        } 
    }

    template<GoodCont Conteiner, typename Func>
    Conteiner transform(const Conteiner& conteiner, const Func& func)
    {
        Conteiner temp(conteiner.begin(), conteiner.end());
        for (auto i = 0; i < conteiner.size(); i++)
        {
            auto index_mask = i % Size;
            if (mask[index_mask])
                temp[i] = func(temp[i]);
        } 
        return temp;
    }

    template<GoodCont Conteiner, typename Func>
    Conteiner slice_and_transfrom(const Conteiner& conteiner, const Func& func)
    {
        Conteiner temp = transform(conteiner, func);
        slice(temp);
        return temp;
    }


};

template<typename Conteiner>
void print_cont(const Conteiner& conteiner)
{
    for (const auto& per : conteiner)
    {
        std::cout << per << ' ';
    }
    std::cout << '\n';
}

int main()
{
    Mask<3> mask1 = {1,0,0};
    std::vector vec1 = {1,2,3,4,5,6,7};
    mask1.slice(vec1);
    print_cont(vec1);


    Mask<5> mask2 = {1,0,0,0,0};
    std::vector vec2 = {1,2,3,4,5,6,7,8,9,10};
    vec2 = mask2.transform(vec2, [](auto x){ return x*10; });
    print_cont(vec2);


    Mask<5> mask3 = {1,0,0,0,0};
    std::vector vec3 = {1,2,3,4,5,6,7,8,9,10};
    vec3 = mask3.slice_and_transfrom(vec3, [](auto x){ return x*10; });
    print_cont(vec3);


    Mask<3> mask4 = {1,0,0};
    std::string temp = "Hello_world!";
    temp = mask4.transform(temp, [](auto x){ return 'A'; });
    std::cout << temp << std::endl;


    return 0;
}
