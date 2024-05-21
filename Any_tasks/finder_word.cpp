#include <iostream>
#include <vector>
#include <string_view>
  
std::vector<std::string_view> get_words(std::string_view);
 
int main()
{
    std::string text = " An apple a day keeps the doctor away."; // Исходный текст
 
    std::vector<std::string_view> words = get_words(text);
 
    // выводим количество слов
    std::cout << "\nText contains " << words.size() << " words:" << std::endl;
    // выводим все слова на консоль
    for (const auto& word : words)
    {
        std::cout << word << std::endl;
    }
}
 
std::vector<std::string_view> get_words(std::string_view text)
{
    const std::string_view separators{ " ,;:.\"!?'*\n" };
    std::vector<std::string_view> words; // вектор для хранения слов
    size_t start { text.find_first_not_of(separators) }; // начальный индекс первого слова
    while (start != std::string_view::npos) // проходим, пока в строке не окажется других символов, кроме separators
    {
        size_t end = text.find_first_of(separators, start + 1); // находим, где кончается слово
        if (end == std::string_view::npos) // если НЕ найден ни один из символов-разделителей
            end = text.length();        // устанавливаем переменную end на конец текста
        words.push_back(text.substr(start, end - start)); // добавляем в вектор слово
        start = text.find_first_not_of(separators, end + 1); // находим начальный индекс следующего слова и переустанавливаем start
    }
    return words;
}
