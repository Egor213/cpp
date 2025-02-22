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
2. [`about_control_statements.c`](#файл-about_control_statementsc)
3. [`about_functions.c`](#файл-about_functionsc)
4. [`about_pointers.c`](#файл-about_pointersc)
5. [`about_malloc.c`](#файл-about_mallocc)
6. [`about_arrays.c`](#файл-about_arraysc)
7. [`about_strings.c`](#файл-about_stringsc)
8. [`about_structs.c`](#файл-about_structsc)
9. [`about_dataclasses.c`](#файл-about_dataclassesc)
10. [`about_printing.c`](#файл-about_printingс)
11. [`about_io.c`](#файл-about_ioc)
12. [`about_linked_lists.c`](#файл-about_linked_listsc)
13. [`about_preprocessor.c`](#файл-about_preprocessorc)

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
+ **Тест 1-3**

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


## Файл `about_functions.c`

### **Test function_basics**
---
+ **Тест 1-2**

    **Описание:**
    Знакомство с функциями. Необходимо определить, что вернет заданая функция. Код функции представлен.
    
    **Рандомизация:**
    Возможно, создать ряд функции и случайным образом их выдавать в тест.
    
    **Участок кода:**
    
    ```c
    int return_5() { return 5; }

    int fib(int n)
    {
        if (n == 0)
            return 0;
        if (n == 1)
            return 1;
        else
            return fib(n - 1) + fib(n - 2);
    }

    cr_assert_eq(return_5(), TODO, "What does this function return?");

    /* Of course, functions can be recursive */
    cr_assert_eq(fib(5), TODO, "What is the 5th fibonacci number?");
    ```
### **Test function_prototypes**
---
+ **Тест 1**

    **Описание:**
    В начале кода определн прототип функции, после теста описана реализации функции. Необходимо определить, что вернет функция.
    
    **Рандомизация:**
    Случайные арифметические операции в функции прототипе.
    
    **Участок кода:**
    
    ```c
    int function_prototype(int, int);

    Test(about_functions, function_prototypes)
    {
        /* We will test if our function can be called since it has been declared */
        cr_assert_eq(
            function_prototype(1, 2), TODO, "What does the function return?");
    }

    /* Here is the implementation for our prototype. */
    int function_prototype(int i, int j) { return i + j; }
    ```



### **Test function_scope_and_vars**
---
+ **Тест 1-3**

    **Описание:**
    Знакомство с областями видимости. В `c_koans_helpers.c` описаны функции для изменения глобальной, локальной и статической переменной. По ряду вызовов данных функции необходимо определить результат их работы.
    
    **Рандомизация:**
    Значения, которые прибавляются к переменной в ходе вызова функции.
    Возможно, рандомизация нескольких арифметических операции, не только сложения.
    **Участок кода:**
    
    ```c
    // c_koans_helpers.c
    int global_var = 0;
    int modify_global()
    {
        /*
            We modify the global variable, located in the .data section,
            visible to the entire program.
        */
        global_var++;
        return global_var;
    }
    int modify_local()
    {
        /*
            We modify the local variable, located and initialized on the stack.
            every call, it will be initialized and modified in the same fashion.
        */
        int i = 0;
        i++;
        return i;
    }
    int modify_local_static()
    {
        /*
            Local static variables will be initialized only once and be located
            in the .data section. Local static variables can only be referenced
            inside the function because the name will be known inside the function.
            This causes the value of the variable to be preserved across function
            calls.

            The static qualifier has a double meaning depending on the scope it
            appears in; the next function will show this
        */
        static int i = 0;
        i++;
        static_function(0); /* we are calling this to avoid a compiler warning */
        return i;
    }

    // about_functions.c

    modify_global();
    modify_global();
    cr_assert_eq(modify_global(), TODO,
        "What is the value of global_var after the third call?");

    modify_local();
    modify_local();
    cr_assert_eq(modify_local(), TODO,
        "What is the value of the local variable after the third call?");

    modify_local_static();
    modify_local_static();
    cr_assert_eq(modify_local_static(), TODO,
        "What is the value of the local static variable after the third call?");
    ```




## Файл `about_pointers.c`

### **Test pointers_and_addresses**
---
+ **Тест 1-4**

    **Описание:**
    Знакомство с указателями. Пользователю необходимо узнать, сколько байт занимает тип переменной int, int*, познакомиться с разыменованием указателей.
    
    **Рандомизация:**
    Значение, которое имеет переменная при разыменовании.
    
    **Участок кода:**
    
    ```c
    int i = 10;
    int j = 20;

    /* This is the syntax of the pointer declaration. It is a type name
     * followed by a '*' somewhere between the type name and the variable name.
     *
     * The '&' operator gives the address of a variable.
    */
    int *iptr = &i;
    int *jptr = &j;

    cr_assert_eq(
        sizeof(i), TODO, "What is the size of an int on a 64 bit machine?");
    cr_assert_eq(sizeof(iptr), TODO,
        "What is the size of an address on a 64 bit machine?");

    /* The '*' operator has another meaning when used not in a declaration to
     * 'dereference' a pointer, and give the value at that address.
    */

    cr_assert_eq(*jptr,TODO, "What is the value that jptr 'points' to?");
    
    /*
     * Multi-variable declarations mixing pointers and the type it points to
     * can be hard to interpret depending on your choice of position for the
     * '*'.
    */

    /* DON'T DELETE THE CLANG-FORMAT LINES */
    /* clang-format off */
    int k, *l;
    int* m, n;
    /* clang-format on */

    cr_assert_eq(sizeof(k), TODO, "What type is k?");
    cr_assert_eq(sizeof(l), TODO, "What type is l?");
    cr_assert_eq(sizeof(m), TODO, "What type is m?");
    cr_assert_eq(sizeof(n), TODO, "What type is n?");
    ```


### **Test pointers_as_function_arguments**
---
+ **Тест 1**

    **Описание:**
    Передача переменной в функцию по указателю. Необходимо определить, какое значение примет переменная `i`
    
    **Рандомизация:**
    Начальное значение переменной `i`, арифметическое действие по ее изменению в функции.
    
    **Участок кода:**
    
    ```c
    // c_koans_helpers.c
    void double_an_int(int *i)
    {
        /*
            The '*' operator for dereference has a higher precedence than the other
            arithmetic operators, therefore it will be multiplying and assigning the
            int that is pointer to by i.
        */
        *i *= 2;
    }

    // about_pointers.c

    int i = 10;

    double_an_int(&i);

    cr_assert_eq(i, TODO, "What is the new value of i?");
    ```



### **Test pointers_arrays_and_arithmetic**
---
+ **Тест 1-3**

    **Описание:**
    Знакомство с указателями на массив данных. Необходимо определить, какие значения принимают переменные при разыменовании.
    
    **Рандомизация:**
    Рандомизация массива данных, случайные индексы в указателях.
    
    **Участок кода:**
    
    ```c
    int a[5] = { 1, 2, 3, 4, 5 };
    int *p1 = &a[0];
    int *p2 = &a[1];

    cr_assert_eq(*a, TODO, "Remember what the ");
    cr_assert_eq(*p1, TODO, "What does p1 point to?");
    cr_assert_eq(*p2, TODO, "What does p2 point to?");
    ```

+ **Тест 4-5**

    **Описание:**
    Знакомство с арифметикой указателей. Необходимо определить, какие значения вернут разыменованные указатели, при увеличении их на некоторое число.
    
    **Рандомизация:**
    Рандомизация сдвигов при арифметике указателей.
    
    **Участок кода:**
    
    ```c
    cr_assert_eq(*(p1 + 1), TODO, "What is the value at this address?");

    cr_assert_eq(p1[1], TODO,
        "Bracket notation is just syntactic sugar for pointer arithmetic.");
    ```

+ **Тест 6-7**

    **Описание:**
    Необходимо определить, какое количество байт между двумя указателями.
    
    **Рандомизация:**
    Рандомизация индексов в указателях.
    
    **Участок кода:**
    
    ```c
    cr_assert_eq((long)((long)p2 - (long)p1), TODO,
        "What is the number of bytes difference?");

    cr_assert_eq(
        (int)(p2 - p1), TODO, "What is the number of ints difference?");
    ```

### **Test function_pointers**
---
+ **Тест 1**

    **Описание:**
    Необходимо с помощью qsort отсортировать массив `names`.
    
    **Рандомизация:**
    Можно массив `names`, но действие сортировки всегда одно, так что особого смысла от разного `names` нет.
    
    **Участок кода:**
    
    ```c
    // c_koans_helpers.c
    int string_compare(const void *s1, const void *s2)
    {
        /*
            The comparison function must match the declaration in the prototype
            exactly. This is why, even though we are comparing 2 strings, the
            arguments must be void pointers.

            The actual arguments passed into this function is the address of each
            element in the array, which in this case is a char **, this is why we
            must cast the argument to a char ** and dereference it once for strcmp
            to work.
        */
        return strcmp(*(char **)s1, *(char **)s2);
    }


    // about_pointer.c

    const size_t array_size = 5;
    char *names[] = { "Spike", "Ein", "Jet", "Ed", "Faye" };
    char *sorted_names[] = { "Ed", "Ein", "Faye", "Jet", "Spike" };
    (void)array_size; /* to avoid a compiler error */
        /*
        Write the line of code to sort names here.
        the comparison function to use can be found found in c_koans_helpers.c,
        named string_compare
    */

    /* qsort(); */

    cr_assert_arr_eq_cmp(sorted_names, names, array_size, string_compare,
        "The names are not sorted.");
    ```
