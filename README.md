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

### **Test intro**
----
Приветственный тест, рандомизировать нечего, просто знакомство с системой.


### **Test variables**
---
+ **Тест 1**

    **Описание:**
    Предлагает посмотреть в ASCII таблицу и познакомится с представлением различных символов в виде ASCII-кода
    
    **Рандомизация:**
    В тесте можно задавать случайный символ из ASCII таблицы.
    
    **Участок кода:**
    
    ```c
    char c = TODO;
    cr_assert_eq(c, 'C',
        "All characters in C are interpreted from the ASCII "
        "table, go to your terminal and enter 'man ascii' to "
        "find this solution");
    ```

+ **Тест 2-5**

    **Описание:**
    Знакомство с некоторыми типами данных.
    
    **Рандомизация:**
    Нечего.
    
    **Участок кода:**
    
    ```c
    char c = TODO;
    short s = TODO;
    cr_assert_eq(s, 0xBEE, "A short is 2 bytes");

    int i = TODO;
    cr_assert_eq(i, 0xBADBEEF, "A int is 4 bytes");

    long long l = TODO;
    cr_assert_eq(l, 0xDEBA7AB1E,
        "A long is a larger integer type than int (supports unsigned).");

    unsigned int ui = TODO;
    cr_assert_gt(ui, 0xDEADBEEF,
        "The unsigned modifier can be used on a "
        "primitive data type to increase the upper "
        "limit by only storing positive values");
    ```

+ **Тест 6**

    **Описание:**
    Знакомство с некоторыми обозначениями, указывающие на различные системы счисление.
    
    **Рандомизация:**
    Нечего.
    
    **Участок кода:**
    
    ```c
    long long ll = TODO;

    cr_assert_eq(ll, 0xFF,
        "A number literal starting with 0x will be interpreted as hexadecimal");
    cr_assert_eq(ll, 0b11111111,
        "A number literal starting with 0b will be interpreted as binary");
    cr_assert_eq(ll, 0377,
        "A number literal starting with 0 will be interpreted as octal");
    ```

+ **Тест 7-8**

    **Описание:**
    Представление целочисленного деления чисел. Пользователю предлагается указать значение переменное, которое вернет операция из теста.
    
    **Рандомизация:**
    Числа при делении.
    
    **Участок кода:**
    
    ```c
    double d = TODO;
    cr_assert_float_eq(d, (7 / 2), 0.000001,
        "Just like Java, C does integer division for 7/2");

    double d2 = TODO;
    cr_assert_float_eq(d2, 3 + (1 / 2), 0.000001,
        "Addition also effects whether a number literal is "
        "interpreted as IEEE or 2's Comp");
    ```



## Файл `about_control_statements.c`

### **Test ifs**
---
+ **Тест 1-2**

    **Описание:**
    Знакомство с условным оператором `if`. Необходимо понять, какое значение примет переменная `var` по заданной конструкции.
    
    **Рандомизация:**
    Значение чисел, которые определяют значение `var`.
    
    **Участок кода:**
    
    ```c
    int var = 1 < 2;

    if (var)
        var = 1;
    else
        var = 2;

    /* To pass this test, determine where the control flow will go. */
    cr_assert_eq(var, TODO, "If statements work just like other languages");

    /* Of course, C also has the familiar else-if */
    if (1 > 2)
        var = 1;
    else if (1 == 2)
        var = 3;
    else
        var = 4;

    cr_assert_eq(var, TODO, "Determine the control flow for this block, too");
    ```

### **Test switch_block**
---
+ **Тест 1**

    **Описание:**
    Условный оператор `switch`. По заданной конструкции и начальному значению переменной `var` необходимо определить фильное значение переменной.
    
    **Рандомизация:**
    Рандомизация значения `var`, при условии, что оно будет совместимо с конструкцией `switch`, иначе получается только 3 случайных значения: 1, 10, что-то другое.
    
    **Участок кода:**
    
    ```c
    int var = 1;
    switch (var) {
    case 1:
        var = 100;
    case 10:
        var = 200;
        break;
    default:
        break;
    }

    cr_assert_eq(var, TODO, "Determine the control flow for this block.");
    ```


### **Test loops**
---
+ **Тест 1**

    **Описание:**
    Циклы `while`, `for`, `do ..while`. Дан цикл, на каждом цикле которого происходит увеличение переменной `var`. Необходимо определить финальное значение перменной.
    
    **Рандомизация:**
    Количетсво итерации цикла.
    
    **Участок кода:**
    
    ```c
    int var = 0;
    while (true) {
        var++;
        if (var == 10)
            break;
    }

    cr_assert_eq(
        var, TODO, "Determine the result of the execution of this loop.");

    for (var = 0; var < 10; var++) {
        ;
    }
    cr_assert_eq(
        var, TODO, "Determine the result of the for loop's execution.");

    var = 0;
    do {
        var++;
    } while (var < 10);

    cr_assert_eq(
        var, TODO, "Determine the result of the do-while loop's execution");
    ```

### **Test goto_and_labels**
---
+ **Тест 1**

    **Описание:**
    Оператор `goto`. Необходимо определить, какое значение примет переменная `var`.
    
    **Рандомизация:**
    Значение переменной `var` до вызова `goto` и после.
    
    **Участок кода:**
    
    ```c
    int var = 10;

    goto label;

    var = 50;
    /*
        The label syntax is some name
        (the same as a variable name) followed by a colon.
    */
    label:
        cr_assert_eq(
            var, TODO, "Determine the result of the flow of the function.");
    ```
