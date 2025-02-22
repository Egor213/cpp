# Анализ на возможность c_koans на возможность рандомизации

## Темы курса
В данном курсе представлены следующие темы:
- **Basics** (Базовые конструкции и структуры)
- **Pointers** (Указатели)
- **Functions** (Функции)
- **Arrays** (Массивы)
- **Strings** (Строки)
- **The Preprocessor** (Препроцессор)
- **Control Statements** (Операторы управления)
- **Structs** (Структуры)
- **DataClasses** (Датаклассы)
- **I/O** (Ввод/вывод)
- **Malloc** (Аллокация памяти)
- **Linked List Project** (Связанные списки)

## Рекомендуемый порядок выполнения
Автор рекомендует проходить тесты в следующем порядке:

1. [`about_basics.c`](#файл-about_basicsc)
2. `about_control_statements.c`(#файл-about_control_statementsс)
3. `about_functions.c`(#файл-about_functionsс)
4. `about_pointers.c`(#файл-about_pointersс)
5. `about_malloc.c`(#файл-about_mallocс)
6. `about_arrays.c`(#файл-about_arrays)
7. `about_strings.c`(#файл-about_stringsс)
8. `about_structs.c`(#файл-about_structsс)
9. `about_dataclasses.c`(#файл-about_dataclassesс)
10. `about_printing.c`(#файл-about_printingс)
11. `about_io.c`(#файл-about_ioс)
12. `about_linked_lists.c`(#файл-about_linked_listsс)
13. `about_preprocessor.c`(#файл-about_preprocessorс)

## Файл `about_basics.c`
### *Test intro*
Приветсвенный тест, рандомизировать нечего, просто знакомство с системой.

### *Test variables*

 + Тест 1. 
 Описание:
 Предлагает посмотреть в ASCII таблицу и выяснить код некоторого символа, после чего присвоить его заданной переменной.
 Рандомизация:
 В тесте можно задавать случаный символ из ASCII таблицы.
 Участок кода:
 ```C
 char c = TODO;
cr_assert_eq(c, 'C',
    "All characters in C are interpreted from the ASCII "
    "table, go to your terminal and enter 'man ascii' to "
    "find this solution");
 ```
