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
10. [`about_printing.c`](#файл-about_printingc)
11. [`about_io.c`](#файл-about_ioc)
12. [`about_linked_lists.c`](#файл-about_linked_listsc)
13. [`about_preprocessor.c`](#файл-about_preprocessorc)

## **[К Итогам](#итог)**

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
    Значения чисел, которые определяют значение `var`.
    
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
    Циклы `while`, `for`, `do ..while`. Дан цикл, на каждой итерации которого происходит увеличение переменной `var`. Необходимо определить финальное значение перменной.
    
    **Рандомизация:**
    Количетсво итерации цикла, начальное значение `var`, условие остановки.
    
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
    В начале кода определен прототип функции, после теста описана реализации функции. Необходимо определить, что вернет функция.
    
    **Рандомизация:**
    Случайные арифметические операции в функции прототипе и случайные значения, передаваемые в функцию.
    
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






## Файл `about_malloc.c`

### **Test malloc_intro**
---
+ **Тест 1-2**

    **Описание:**
    Знакомство с `malloc`. Необходимо определить, какое значение хранится в разыменованной переменной.
    
    **Рандомизация:**
    Рандомизация записываемых в переменные значений.
    
    **Участок кода:**
    
    ```c
    int *malloc_func()
    {
        int *return_ptr = malloc(sizeof(int));
        *return_ptr = 15;
        return return_ptr;
    }
    int *i = malloc(sizeof(int));
    *i = 5;
    cr_assert_eq(*i, TODO, "What is the value of i on the heap?");

    /*
        If you allocate space for a variable on the stack in a function call,
        it'll be allocated in the function's stack frame. This means the space
        won't be valid after the function returns.

        Space that was malloc'ed, however, is valid after functions return
        because it is allocated on the heap. Therefore, functions that need
        to return new pointers should allocate space for them using malloc.
    */
    int *return_ptr = malloc_func(); /* goto line 6 */
    cr_assert_eq(*return_ptr, TODO, "What is the value of return_ptr on the heap?");
    ```



### **Test free**
---
+ **Тест 1**

    **Описание:**
    Пользователю необходимо определить, что будет храниться в переменной `ip` после очистки функцией `free`.
    
    **Рандомизация:**
    Нечего.
    
    **Участок кода:**
    
    ```c
    int *ip = malloc(sizeof(int));

    *ip = 10;
    free(ip);
    ip = NULL;

    cr_assert_eq(
        ip, (void *)TODO_NZ, "What is ip now? What would happen if we \
        dereference ip?");
    ```




### **Test calloc**
---
+ **Тест 1-2**

    **Описание:**
    Необходимо определить длину строки, которая была создана с помощью `calloc`, затем длину строку после копирования туда другой строки.
    
    **Рандомизация:**
    Строка, которая копируется в массив и сама длина массива.
    
    **Участок кода:**
    
    ```c
     char *s = calloc(10, sizeof(char));

    /*
        Calloc is very useful for initializing strings, since the initalized
        memory will be a valid C-string of length 0.
    */

    cr_assert_eq(strlen(s), TODO_NZ, "What is the length of an empty string?");
    strcpy(s, "foo");

    cr_assert_eq(strlen(s), TODO, "What is the new length?");
    ```






### **Test realloc**
---
+ **Тест 1-2**

    **Описание:**
    Знакомство с функцией `realloc`. Необходимо определить, какое значение будет находится в переменной `ip`.
    
    **Рандомизация:**
    Начальное значение `ip`.
    
    **Участок кода:**
    
    ```c
    void *ip = malloc(sizeof(int));
    *(int *)ip = 0xDEADBEEF;

    ip = realloc(ip, sizeof(long));

    cr_assert_eq(
        *(unsigned long *)ip, TODO, "What bytes of ip were preserved \
        when it is increased in size?");

    ip = realloc(ip, sizeof(short));

    /* Hint: our VMs are little endian */
    cr_assert_eq(*(unsigned short *)ip, TODO, "What bytes were preserved now?");
    ```








## Файл `about_arrays.c`

### **Test what_is_an_array**
---
+ **Тест 1-5**

    **Описание:**
    Знакомство с массивом. Необходимо определить первое значение массива, определить индекс, который соответствует заданной арифметике указателей, определить размер массива.
    
    **Рандомизация:**
    Рандомизация начального массива `array` и арифметический сдвиг.
    
    **Участок кода:**
    
    ```c
    void func(int *array)
    {
        cr_assert_eq(sizeof(array), TODO,
            "That same array gives a different size "
            "when passed into this function");
    }
    int array[5];
    array[0] = 1;
    array[1] = 2;
    array[2] = 3;
    array[3] = 4;
    array[4] = 5;
    /* Change this to: 'cr_assert_not_null' */
    cr_assert_null(array,
        "An array declared in this way is a label meaning "
        "it has an address %p",
        array);
    cr_assert_eq(*array, TODO,
        "Dereferencing this label's address gives us the "
        "value at that point");

    cr_assert_eq(*(array + 2), array[TODO],
        "Dereferencing with an offset is the same as using the bracket notation"
        " to access");
    cr_assert_eq(sizeof(array), TODO,
        "sizeof an array can be tricky is it size "
        "of a pointer or sum of all memory the "
        "array takes up?");
    func(array);
    ```

+ **Тест 6**

    **Описание:**
    Новый способ задания массива. Необходимо опеределить значение по индексу.
    
    **Рандомизация:**
    Начальный массив и индекс элемента.
    
    **Участок кода:**
    
    ```c
    int another_array[5] = { 1, 2, 3, 4, 5 };
    cr_assert_eq(another_array[3], TODO,
        "We should be seeing the some element's value.");
    ```
+ **Тест 7**

    **Описание:**
    Задание динамического массива. Необходимо определить его значения.
    
    **Рандомизация:**
    Рандомизация данных, которыми заполняется массив, но тогда надо быть аккуратным с тестом внутри цикла.
    
    **Участок кода:**
    
    ```c
    const size_t INIT_ARR_SIZE = 5;
    int *yet_another_array = calloc(INIT_ARR_SIZE, sizeof(int));
    unsigned i;
    for (i = 0; i < INIT_ARR_SIZE; i++) {
        /*
            You can loop on arrays, as long as you handle the indexing logic
            correctly.
        */
        yet_another_array[i] = i + 1;
    }
    yet_another_array[INIT_ARR_SIZE] = 6;
    unsigned where = 0;
    for (i = 0; i < INIT_ARR_SIZE + 1; i++) {
        if (yet_another_array[i] == INIT_ARR_SIZE + 1) {
            where = i;
        }

        cr_assert_eq(yet_another_array[i], TODO,
            "Although we started with an "
            "array of 5 elements, we "
            "should be able to find a "
            "sixth element as well.");
    }
    cr_assert_eq(where, TODO,
        "We should be seeing a certain value, given the "
        "way we set these elements' values.");
    ```

+ **Тест 8-9**

    **Описание:**
    Строка в СИ - массив. Необходимо определить символ по заданному индексу.

    **Рандомизация:**
    Рандомизация входной строки и индекса.
    
    **Участок кода:**
    
    ```c
    const char a_string[13] = "hello world!"; /* This is a 'string' in C. */
     /* In C, a string is simply an array of characters. */
    cr_assert_eq(a_string[3], TODO,
        "We may be interested in a particular "
        "character of strings.");
    cr_assert_eq(a_string[12], TODO_NZ, "Null terminators are essential!");
    ```















## Файл `about_strings.c`

### **Test what_is_string**
---
+ **Тест 1-3**

    **Описание:**
    Необходимо определить символ, который вернется при разыменовании элемента строки.
    
    **Рандомизация:**
    Рандомизация начальной строки и сдвига для получения символа.
    
    **Участок кода:**
    
    ```c
    char *string = "CSE101 is awesome";
    /* Change this to: 'cr_assert_not_null' */
    cr_assert_null(
        string, "string contains value which is the address of first\
     character");

    /* Change it to 'C' */
    cr_assert_eq(
        'c', *string, "Dereferencing will give the first character of \
        the string");

    cr_assert_eq('s', *(string + 1), "Dereferencing with offset will give \
        character at offset");
    ```


### **Test reference_characters**
---
+ **Тест 1-3**

    **Описание:**
    Работа с индексами и арифметикой указателей на примере строки. Необходимо исправить символы на правильные.
    
    **Рандомизация:**
    Рандомизация начальной строки и сдвига для получения символа.
    
    **Участок кода:**
    
    ```c
    char *string = "CSE101 is awesome";

    /* Change it to 'E', indexing starts with 0 */
    cr_assert_eq('1', string[2], "String can be used as arrays");

    /*
        Can also add the can use both
        offset and bracket notation at the same time
    */
    cr_assert_eq(
        'E', (string + 1)[2], "Gets character at the sum of both numbers");

    /*
        *string + 1 will get first character and add 1 to the character, while
        *(string + 1) adds 1 to the pointer then
        dereferences it
    */
    cr_assert_eq(*string + 1, *(string + 1), "They are not equal");
    ```



### **Test assignment**
---
+ **Тест 1-3**

    **Описание:**
    Необходимо исправить строку так, чтобы она соответствовала внесенным изменениям.
    
    **Рандомизация:**
    Входную строку и способы изменения строки.
    
    **Участок кода:**
    
    ```c
    char string[] = "CSE 101";
    string[2] = 'S';
    cr_assert_str_eq("CSE 101", string, "String declared this way are mutable");

    *(string + 4) = '2'; /* forgetting () will give compiling error */
    cr_assert_str_eq("CSE 101", string, "String declared this way are mutable");

    (string + 4)[2] = '2';
    cr_assert_str_eq("CSE 101", string, "String declared this way are mutable");
    ```


### **Test declaration**
---
+ **Тест 1**

    **Описание:**
    Необходимо уровнять строки по байтам.
    
    **Рандомизация:**
    Рандомизация входных строк, но смысл, вроде, в добавлении символа завершения строки.
    
    **Участок кода:**
    
    ```c
    /* DOES NOT automatically add terminating character at the end */
    char string1[] = { 'C', 'S', 'E', '1', '0', '1' };
    char string2[] = "CSE101"; /* Adds terminating character at the end */

    cr_assert_eq(
        sizeof(string1), sizeof(string2), "Only one of them contains \\\
        0 at the end");
    ```


### **Test sizeof_strlen**
---
+ **Тест 1**

    **Описание:**
    Необходимо изменить строку так, чтобы она была равна значению strlen.
    
    **Рандомизация:**
    Рандомизация входной строки.
    
    **Участок кода:**
    
    ```c
    char string[] = { 'C', 'S', 'E', '\0', '1', '0', '1' };
    cr_assert_eq(sizeof(string), strlen(string), "strlen ends counting at \\0");
    ```

+ **Тест 2-3**

    **Описание:**
    Определить размеры и длины входных строк.
    
    **Рандомизация:**
    Рандомизация входных строк.
    
    **Участок кода:**
    ```c
    char *string2 = "Some String";
    char string3[10] = "CSE 101";

    cr_assert_eq(TODO, sizeof(string2), "sizeof string2 only shows size of the \
        char pointer");
    cr_assert_eq(TODO, sizeof(string3), "sizeof string3 shows memory used by \
        string3 array not string size");
    ```


### **Test copy**
---
+ **Тест 1-2**

    **Описание:**
    Необходимо определить, как изменяется строка при копировании через указатель и через функцию `strcpy`.
    
    **Рандомизация:**
    Входная строка и символ, который заменяется во входной строке через указатель.
    
    **Участок кода:**
    
    ```c
    char string1[] = "CSE 101";

    /* Only copies pointer, string2 and string1 now reference the same memory */
    char *string2 = string1;

    string1[4] = '2'; /* string1 = CSE 201 */

    cr_assert_str_eq(
        "CSE 101", string2, "Only copied pointer, did not copy the\
     string");

    /* Correct way to copy string */
    char string3[8];
    strcpy(string3, string1); /* copy all characters */

    /* Replace with cr_assert_str_eq */
    cr_assert_eq("CSE 101", string2, "Only copied pointer, did not copy the \
        string");
    ```

### **Test function_paramater**
---
+ **Тест 1-2**

    **Описание:**
    Вычисление количества байт, занимаемое строкой.
    
    **Рандомизация:**
    Рандомизация входной строки.
    
    **Участок кода:**
    
    ```c
    void test_a_string_length_with_sizeof(char *string)
    {
        /* Sizeof(string) is 8 because the size of pointer is 8 */
        cr_assert_eq(TODO, sizeof(string), "That same string gives a different size \
            when passed into this function, always use strlen function");
    }
    char string[] = { 'C', 'S', 'E', '\0' };
    cr_assert_eq(4, sizeof(string), "Sizeof gives correct output");
    test_a_string_length_with_sizeof(string);
    ```


### **Test formating_strings**
---
+ **Тест 1**

    **Описание:**
    Знакомство с форматированием строк. Необходимо определить, какая получится строка в результате форматирования.
    
    **Рандомизация:**
    Рандомизация условии форматирования.
    
    **Участок кода:**
    
    ```c
    char *string1 = malloc(12);
    sprintf(string1, "%s %s!", "CSE", "101!");

    cr_assert_str_eq("CSE 102!", string1, "Instead of printing to stdout we \
        print it to string1");
    free(string1);
    ```




## Файл `about_structs.c`

### **Test struct_basics**
---
+ **Тест 1-3**

    **Описание:**
    Необходимо определить заданные значения структуры и ее размер.
    
    **Рандомизация:**
    Рандомизация начальной структуры и значений полей.
    
    **Участок кода:**
    
    ```c
    struct point2d {
        int x;
        int y;
    };
    struct point2d p1;

    /* Their members are accessed very familiarly, with a '.' */
    p1.x = 10;
    p1.y = 2;
    cr_assert_eq(p1.x, TODO, "What has the x value been initialized to?");
    cr_assert_eq(sizeof p1, TODO, "What is the size of our two ints?");
    struct point2d p2 = { 10, 20 };

    cr_assert_eq(p2.y, TODO, "What has the y value been initialized to?");
    ```

+ **Тест 4-5**

    **Описание:**
    Необходимо определить значения вложенных структур.
    
    **Рандомизация:**
    Рандомизация новых полей во вложенных структурах.
    
    **Участок кода:**
    
    ```c
    struct point3d {
        struct point2d two_d;
        int z;
    } p3;

    p3.two_d.x = 10;
    p3.two_d.y = 20;
    p3.z = 40;

    cr_assert_eq(p3.two_d.y, TODO, "Member access is no different than usual");
    typedef struct {
        struct point3d three_d;
        int w;
    } point4d;

    point4d p4;
    p4.three_d.z = 2;
    p4.three_d.two_d.x = 1;

    cr_assert_eq(p4.three_d.two_d.x, TODO,
        "What is the value of x, after all the struct access?");
    ```




### **Test structs_and_functions_and_pointers**
---
+ **Тест 1**

    **Описание:**
    Необходимо разобраться с более сложной струтурой и определить значения ее полей.
    
    **Рандомизация:**
    Рандомизация начальных полей структуры и значений полей.
    
    **Участок кода:**
    
    ```c
    typedef struct {
        int month;
        int day;
        int year;
    } birthday;

    struct person {
        char *name;
        birthday bday;
    };
    struct person make_person(const char *name, int month, int day, int year)
    {
        struct person ret;

        /* is this a problem? What is the lifetime of this heap allocated memory? */
        ret.name = calloc(strlen(name), sizeof(char));
        strcpy(ret.name, name);

        ret.bday.month = month;
        ret.bday.day = day;
        ret.bday.year = year;

        return ret;
    }
    struct person person1;

    /* Examine this function in c_koans_helpers.c */
    person1 = make_person("Brian", 5, 14, 1996);

    cr_assert_str_eq(person1.name, "Brian", "What is the name of this person?");

    ```

+ **Тест 2**

    **Описание:**
    Необходимо определить значение заданного поля структуры и код завершения функции `make_person_better`.
    
    **Рандомизация:**
    Рандомизация входных данных для структуры.
    
    **Участок кода:**
    
    ```c
    int make_person_better(
    struct person *person, const char *name, int month, int day, int year)
    {

        /*
            The access operator for a pointer to a struct is different that usual
            Instead of having to type (*person).bday.month for accessing a pointer
            to a struct's fields, the '->' operator is sugar for the last expression
        */
        person->bday.month = month;
        person->bday.day = day;
        person->bday.year = year;

        /*
            Errno is a global variable that is set
            by library functions to indicate an
            an error occurred in that function. When we call calloc, an error might
            occur, such as the machine being out of memory.
        */
        errno = 0; /* we set it to zero because all error numbers are non zero. */

        /* When is this freed? */
        person->name = calloc(strlen(name), sizeof(char));

        /* We check if an error occurred */
        if (errno)
            return EXIT_FAILURE;

        return EXIT_SUCCESS;
        /*
            EXIT_SUCCESS and EXIT_FAILURE are predefined macros for typical success
            or failure. On our VM they are 0 and 1 respectively.
        */
    }
    struct person person2;

    /* Examine this function in c_koans_helpers.c */
    int success = make_person_better(&person2, "Bob", 10, 23, 1994);

    cr_assert_eq(success, EXIT_SUCCESS,
        "If the operation succeeded, what is the return value?");
    cr_assert_eq(
        person2.bday.month, 10, "What is the month for this person?");
    ```



### **Test arrays_of_structs**
---
+ **Тест 1-3**

    **Описание:**
    Необходимо определить размер массива структур, самой структуры с выравниванием и без.
    
    **Рандомизация:**
    Рандомизация длины массива структур и наполнения структур.
    
    **Участок кода:**
    
    ```c
    struct s1 {
        int i;
        int j;
    };

    struct s1 a1[5];

    cr_assert_eq(sizeof a1, TODO, "What is the size of this array in bytes?");
    struct s2 {
        int i;
        char c;
    };

    cr_assert_eq(
        sizeof(struct s2), TODO, "What is the size of the padded struct?");

    struct s3 {
        int i;
        char c;
    } __attribute__((packed));

    cr_assert_eq(
        sizeof(struct s3), DOTO, "What is the size of the packed struct?");
    ```


### **Test self_referential_structs**
---
+ **Тест 1**

    **Описание:**
    Необходимо определить значение поля структуры через указатели.
    
    **Рандомизация:**
    Рандомизация полей структуры и значений полей структуры.
    
    **Участок кода:**
    
    ```c
    struct s1 {
        int i;
        int j;
        struct s1 *s;
    };

    struct s1 sv1;
    struct s1 sv2;

    sv1.s = &sv2;

    sv1.s->i = 10;
    sv1.s->j = 20;

    cr_assert_eq(
        sv1.s->i, TODO, "What is the value of the nested struct's value i?");
    ```




## Файл `about_dataclasses.c`

### **Test unions**
---
+ **Тест 1-3**

    **Описание:**
    Знакомство с `union`. Необходимо определить значения указанных полей.
    
    **Рандомизация:**
    Рандомизация различных типов `union` и значений полей.
    
    **Участок кода:**
    
    ```c
    union first_union {
        double d;
        int i;
        short s;
        char c;
    } u; /* Here we initialize a union variable, just like a struct. */

    u.d = 1.01;

    cr_assert_float_eq(u.d, TODO, 0.01, "What is the value of d that we assigned?");
    cr_assert_eq(sizeof u, TODO,
        "What is the size of the largest data type in "
        "the union?");

    /*
        Since a union holds its data in one place, it could be interpreted
        differently depending on how it is accessed.
    */

    u.i = 0xDEADCAFE;

    cr_assert_eq(u.s, TODO,
        "What is the value stored inside the union, "
        "interpreted as a short?");
    ```


### **Test enums**
---
+ **Тест 1-3**

    **Описание:**
    Знакомство с `enum`. Необходимо определить значения заданных `enum` структурами переменных.
    
    **Рандомизация:**
    Рандомизация полей и значении `enum`.
    
    **Участок кода:**
    
    ```c
    enum boolean { TRUE, FALSE };

    cr_assert_eq(FALSE, TODO, "What will the enum FALSE be?");

    /* enum declarations follow a similar format as structs */
    enum month {
        JAN = 1,
        FEB,
        MAR,
        AP,
        MAY,
        JUN,
        JUL,
        AUG,
        SEP,
        OCT,
        NOV,
        DEC
    };

    /* enums can be assigned variables in the same fashion as structs */
    enum month current = AUG;

    cr_assert_eq(current, TODO,
        "What is the current month? (This was written "
        "in August)");

    /* enums may even be typedef'd */

    typedef enum {
        ONE = 0x1,
        TWO = 0x2,
        THREE = 0x4,
        FOUR = 0x8,
        FIVE = 0x10,
        SIX = 0x20,
        SEVEN = 0x40,
        EIGHT = 0X80
    } bit_mask;

    bit_mask mask_four = FOUR;

    cr_assert_eq(mask_four, TODO, "What is the value of FOUR in this enum?");
    ```


### **Test bit_fields**
---
+ **Тест 1-4**

    **Описание:**
    Необходимо определить размер и значения битовых структур.
    
    **Рандомизация:**
    Рандомизация полей структуры, размера байт и значений полей.
    
    **Участок кода:**
    
    ```c
    struct course_number {
        unsigned int n : 10;
    } cnum;

    cnum.n = 101;
    cr_assert_eq(sizeof cnum, TODO, "What is the size of the struct?");

    struct course {
        unsigned int n : 10;
        unsigned int c3 : 7;
        unsigned int c2 : 7;
        unsigned int c1 : 7;
        unsigned int is_offered : 1;
    };

    struct course cse101 = { 101, 'E', 'S', 'C', 1 };

    cr_assert_eq(*(unsigned int *)(&cse101), TODO,
        "Determine the hex value of "
        "the bit vector for cse101!");

    cr_assert_eq(sizeof cse101, TODO, "What is the size of our variable?");
    struct mmio_cell {
        unsigned char background_color : 4;
        unsigned char background_char : 4;
        unsigned char foreground_color : 4;
        unsigned char foreground_char : 4;
    };
    cr_assert_eq(sizeof(struct mmio_cell), TODO,
        "What would the size of this "
        "struct?");
    ```



### **Test about_const**
---
+ **Тест 1-4**

    **Описание:**
    Необходимо определить значения констант, указателей и константных указателей.
    
    **Рандомизация:**
    Рандомизация значений констант.
    
    **Участок кода:**
    
    ```c
    const int i = 10;
    /* i = 4; ERROR! */
    cr_assert_eq(i, TODO,
        "Attempting to reassign i will result in a compiler "
        "error.");

    /* A const pointer points to an unchangeable space of memory */
    int j = 100;
    const int *jp = &j;

    /* *jp = 10; ERROR! */
    cr_assert_eq(*jp, TODO,
        "Attemping to change the value jp pointer to will "
        "result in a compiler error.");

    /*
        A const after the '*' in a pointer declaration defines a pointer that
        can not point anywhere else.
    */
    int *const kp = &j;

    /* jp2 = &i; ERROR! */

    cr_assert_eq(kp, TODO,
        "Attempting to point kp elsewhere will result in a "
        "compiler error.");

    /* Using both instances of const will result in a const pointer to const! */
    const int l = 400;
    const int *const lp = &l;

    cr_assert_eq(*lp, TODO,
        "Attempting to do any of the previous options to "
        "lp will result in a compiler error.");
    ```







## Файл `about_printing.c`

### **Test basic_printing, printf**
---
+ **Тест 1-2**

    **Описание:**
    Знакомство с базовым выводом. Необходимо вывести заданные строки в `stdout`.
    
    **Рандомизация:**
    Рандомизация строк, которые необходимо вывести.
    
    **Участок кода:**
    
    ```c
    putchar(TODO);

    cr_assert_file_contents_eq_str(stdout, "A");
    puts(TODO_S);

    cr_assert_file_contents_eq_str(stdout, "Foo\n\n");
    char *string = TODO_S;
    printf("Hello %s\n", string);

    cr_assert_file_contents_eq_str(stdout, "Hello World\n");
    cr_assert_file_contents_eq_str(stdout,
        "char: J\nint: -1\nunsigned int: 4294967295\nhexadecimal unsigned int: "
        "ffffffff\nfloat: 3.140000\nlong: 3735928559\npointer: 0x400\n");
    ```





## Файл `about_io.c`

### **Test streams**
---
+ **Тест 1-3**

    **Описание:**
    Необходимо внести наименование различных потоков.
    
    **Рандомизация:**
    Нечего.
    
    **Участок кода:**
    
    ```c
    cr_assert_str_eq("stdin", "stdin", "The standard input stream is...");
    cr_assert_str_eq("stdout", "stdout", "The standard output stream is...");
    cr_assert_str_eq("stderr", "stderr",
		     "The output stream for error messages is...");
    ```


### **Test using_streams**
---
+ **Тест 1-2**

    **Описание:**
    Необходимо указать правильные потоки.
    
    **Рандомизация:**
    Нечего.

    **Участок кода:**
    
    ```c
    fputs("Hello World", TODO_FP);
    fputs("Hello World", TODO_FP);

    cr_assert_file_contents_eq_str(stdout, "Hello World");
    cr_assert_file_contents_eq_str(stderr, "Hello World");
    ```


### **Test file_io**
---
+ **Тест 1**

    **Описание:**
    Необходимо указать, что написано в указанном файле.
    
    **Рандомизация:**
    Рандомизация содержимого файла.

    **Участок кода:**
    
    ```c
    FILE *f;
    char buf[1024];
    f = fopen("rsrc/file.txt", "r");
    fgets(buf, 1024, f);

    cr_assert_str_eq(buf, TODO_S, "view rsrc/file.txt to see what buf should be");
    ```

### **Test buffered_io**
---
+ **Тест 1**

    **Описание:**
    Необходимо указать необходимый поток и сообщение для вывода.
    
    **Рандомизация:**
    Рандомизация потока вывода и сообщения для вывода.

    **Участок кода:**
    
    ```c
    fputs(TODO_S, TODO_FP);
    fflush(stdout);
    cr_assert_file_contents_eq_str(stdout, "foo");
    ```



## Файл `about_linked_lists.c`

### **Test linked_list_basics**
---
+ **Тест 1-3**

    **Описание:**
    Знакомство со связанным списком. Необходимо указать размер головы и значения некоторых элементов.
    
    **Рандомизация:**
    Рандомизация значений узлов.
    
    **Участок кода:**
    
    ```c
    struct linked_list {
        int data;
        struct linked_list *next;
    };
    struct linked_list head = { 10 };
    struct linked_list list_node = { 12 };

    head.next = &list_node;

    cr_assert_eq(head.next, TODO, "What is the `next` value of head?");
    cr_assert_eq(head.next->data, TODO, "What `data` does it hold?");
    cr_assert_eq(sizeof(head), TODO, "How much memory does `head` occupy?");
    ```


### **Test traversing_linked_list**
---
+ **Тест 1-2**

    **Описание:**
    Обход связанного списка. Необходимо определить значение указанного узла.

    **Рандомизация:**
    Рандомизация исходного связанного списка и его значений. <br>
    Возможно, можно добавить полноценное участие итерации для тестов, просто тут их показали, но в тестах они не участвуют.    
    **Участок кода:**
    
    ```c
    struct linked_list {
        int data;
        struct linked_list *next;
    };
    struct linked_list nodes[5] = { { 1 }, { 2, &nodes[0] }, { 3, &nodes[1] },
        { 4, &nodes[2] }, { 5, &nodes[3] } };
    struct linked_list *temp_head = &nodes[4];

    /* Traversing a linked list using a while loop. */
    while (temp_head) {
        /* Do some operations ... */
        temp_head = temp_head->next;
    }

    /* Traversing a linked list using a for loop. */
    for (struct linked_list *i = &nodes[4]; i; i = i->next) {
        /* Do some operations ... */
    }

    cr_assert_eq(nodes[3].next, TODO, "What is nodes[3] pointing to?");
    cr_assert_eq(nodes[3].next->data, TODO, "What is the data contained?");
    ```

### **Test insert_into_linked_list**
---
+ **Тест 1-3**

    **Описание:**
    Необходимо определить значения связанного списка после добавления нового узла.

    **Рандомизация:**
    Рандомизация изначального связанного списка и значений нового узла.

    **Участок кода:**
    
    ```c
    struct linked_list *insert(struct linked_list *head, int val)
    {
        struct linked_list *new_node, *temp;

        for (temp = head; temp && temp->next; temp = temp->next)
            ;

        new_node = malloc(sizeof(*new_node));
        new_node->data = val;
        new_node->next = NULL;

        if (temp)
            temp->next = new_node;

        return new_node;
    }
    struct linked_list head = { 1 };

    /*
        It's nice to create functions to insert/delete from linked list.
        Make sure to keep track of allocated memory.
    */
    struct linked_list *new_node = insert(&head, 2);

    cr_assert_eq(new_node->next, TODO, "What is the new node pointing to?");
    cr_assert_eq(head.next, TODO, "Where is head.next pointing to?");
    cr_assert_eq(
        head.next->data, TODO, "What data is stored in the node after `head`?");
    ```


### **Test delete_from_linked_list**
---
+ **Тест 1-3**

    **Описание:**
    Необходимо определить значения связанного списка после удаления узла.

    **Рандомизация:**
    Рандомизация начальных значений связанного списка и удаляемого узла.

    **Участок кода:**
    
    ```c
    struct linked_list *delete (struct linked_list *head, int val)
    {
        struct linked_list *prev, *i;

        prev = NULL;
        i = head;
        while (i && i->data != val) {
            prev = i;
            i = i->next;
        }

        if (prev && i)
            prev->next = i->next;

        return i;
    }
    struct linked_list nodes[5] = { { 1, NULL }, { 2, &nodes[0] },
        { 3, &nodes[1] }, { 4, &nodes[2] }, { 5, &nodes[3] } };

    /* Do something with removed node .. */
    struct linked_list *deleted_node = delete (&nodes[4], 3);

    cr_assert_eq(
        deleted_node->next, TODO, "What was the deleted node pointing to?");
    cr_assert_eq(nodes[3].next, TODO, "What is the next node after nodes[3]?");
    cr_assert_eq(
        nodes[3].next->data, TODO, "What data is contained in that node?");
    ```



### **Test helpful_pointers**
---
+ **Тест 1-4**

    **Описание:**
    Необходимо определить значения головы и хвоста в связанном списке.

    **Рандомизация:**
    Рандомизация исходного связанного списка.

    **Участок кода:**
    
    ```c
    struct list_node {
        int data;
        struct list_node *next;
    };

    struct _linked_list {
        struct list_node *head;
        struct list_node *tail;
    };

    cr_assert_eq(
        sizeof(struct _linked_list), TODO, "How much memory does it occupy?");

    struct list_node nodes[5] = { { 5, NULL }, { 4, &nodes[0] },
        { 3, &nodes[1] }, { 2, &nodes[2] }, { 1, &nodes[3] } };

    struct _linked_list list = { &nodes[4], &nodes[0] };

    cr_assert_eq(list.head, TODO, "Where is head pointing to?");
    cr_assert_eq(
        list.head->data, TODO, "What is the data contained in the head?");

    cr_assert_eq(list.tail, TODO, "Where is tail pointing to?");
    cr_assert_eq(
        list.tail->data, TODO, "What is the data contained in the tail?");
    ```


### **Test doubly_linked_list**
---
+ **Тест 1-3**

    **Описание:**
    Необходимо определить значения узлов двусвязного списка.

    **Рандомизация:**
    Рандомизация входного двусвязного списка и его значений.

    **Участок кода:**
    
    ```c
    struct dbl_linked_list {
        int data;
        struct dbl_linked_list *next;
        struct dbl_linked_list *prev;
    };

    cr_assert_eq(sizeof(struct dbl_linked_list), TODO,
        "How much memory does it occupy?");

    struct dbl_linked_list n1 = { 1 }, n2 = { 2 }, n3 = { 3 };
    n1.next = &n2;
    n2.next = &n3;
    n2.prev = &n1;
    n3.prev = &n2;

    cr_assert_eq(n2.prev, TODO, "What is the `prev` node of n2?");
    cr_assert_eq(n2.next, TODO, "What is the `next` node of n2?");
    ```







## Файл `about_preprocessor.c`

### **Test macro_definitions**
---
+ **Тест 1-2**

    **Описание:**
    Знакомство с макросами. Необходимо изменить значения переменных, чтобы они соответствовали указанным макросам.
    
    **Рандомизация:**
    Рандомизация значений макросов и данных переменных.
    
    **Участок кода:**
    
    ```c
    #define JOKER "JOKER"

    #define MAX(a, b) (a)
    /* Fix the string we are comparing with what JOKER will be replaced with. */
    const char *CHANGE_ME = "MONA";
    cr_assert(strcmp(CHANGE_ME, JOKER) == 0,
        "Macro JOKER not compared with what it was replaced with!");
    int i = 1;
    int j = 2;
    cr_assert(MAX(i, j) == 2, "Max incorrect!");
    ```


### **Test conditional_defines**
---
+ **Тест 1-2**

    **Описание:**
    Необходимо обьявить и переместить макросы, чтобы они обьявляли необходимые значения переменных.
    
    **Рандомизация:**
    Рандомизация названии необходимых макросов.

    **Участок кода:**
    
    ```c
    #ifndef DEFINE_ME
    #define FIVE 0
    #else
    #define FIVE 5
    #endif /* DEFINE_ME */

    #ifndef MOVE_ME
    #define SEVEN 0
    #else
    #define SEVEN 7
    #endif /* MOVE_ME */

    #define MOVE_ME
     /* Define the macro DEFINE_ME */
    cr_assert_eq(5, FIVE, "FIVE incorrectly defined!");

    /*
        The Preprocessor does a linear scan, so things are defined in the order
        they appear in the file.
        For the next test, define MOVE_ME in a place such that it will pass.
    */

    cr_assert_eq(7, SEVEN, "SEVEN incorrectly defined!");
    ```



### **Test stringizing**
---
+ **Тест 1**

    **Описание:**
    Необходимо указать правильный аргумент макроса, чтобы он соответствовал заданной строке.
    
    **Рандомизация:**
    Рандомизация проверяемой строки.

    **Участок кода:**
    
    ```c
    #define STRINGIZE(arg) #arg
    /*
        To complete this test, replace put the correct argument into STRINGIZE
        such that it will match the string literal.
    */
    cr_assert_eq("my string", STRINGIZE(TODO), "Stringizing not completed.");
    ```


### **Test macro_concatination**
---
+ **Тест 1**

    **Описание:**
    Необходимо указать правильный аргумент для макроса в соответствии с указанными макросами.
    
    **Рандомизация:**
    Нечего.

    **Участок кода:**
    
    ```c
    #define ALWAYS_FALSE false
    #define ALWAYS_TRUE true

    #define THIS_IS(b) ALWAYS_##b
    /*
        To complete this test, assert that THIS_IS(TRUE)!
        Be wary of your usage of capital letters.
    */
    cr_assert(THIS_IS(FALSE), "Concatenation not completed.");
    ```


### **Test variadic_macros**
---
+ **Тест 1**

    **Описание:**
    Необходимо указать верный набор переменных в макросе.
    
    **Рандомизация:**
    Рандомизация входных аргументов.

    **Участок кода:**
    
    ```c
    #define VARIADIC_ARGUMENTS(...) #__VA_ARGS__

    /*
        To pass this test, put the correct argument into the macro call.
        Note that the macro takes advantage of stringizing. Your argument is not
        going to be a string.
    */
    cr_assert_eq("varable,args,with,commas", VARIADIC_ARGUMENTS(TODO),
        "Variadic macros not yet completed");
    ```


# Итог
Рандомизируются в основном значения тестовых переменных. Некоторая часть индексов массивов и входных строк. При желании можно рандомизировать наполнение тестовых функции и структур.
