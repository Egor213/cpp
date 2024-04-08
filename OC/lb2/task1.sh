#!/bin/bash

get_path_by_type() { #функция для получения пути к файлу по его имени и расширению
    local name="$1"  #записываем входные аргументы в переменные
    local type_file="$2"
    search_command="sudo find / -name "$name""   #производим поиск по заданному имени
    mapfile -t result_array < <($search_command) #записываем все найденные пути в массив result_array
    for file in "${result_array[@]}"; do         #запускаем цикл по содержимому массива (всем найденным путям к файлу)
        temp="$(ls -l "$file")"                  #получаем рассширенную информацию про файл по его пути
        if [[ "$type_file" == "d" ]]; then       #если тип файла директория
            temp="$(ls -ld "$file")"             #используем дополнительный флаг -d для получения информации о директории
        fi
        first_symbol_temp="${temp:0:1}"                    #обрезаем первый символ, чтобы узнать тип файла
        if [[ "$first_symbol_temp" = "$type_file" ]]; then #проверяем, если тип найденного файла соответствует заданному типу
            echo "$temp  ------>   $file"                  #выводим информацию о файле и путь до него
            return                                         #выходи из функции
        fi
    done

}

find_file() {                                                            #функция нахождения файла по типу и получения его имени
    local pattern="$1"                                                   #записываем тип входного файла в переменную
    local direct_find="$2"                                               # записываем путь до директории, в которой будем осуществлять поиск
    file=$(sudo ls -lR $direct_find 2>/dev/null | grep "^$pattern" -m 1) #производим поиск файла с помощью утилиты ls и grep.
    #Поиск происходит рекурсивно по всем внутренним директориям заданной директории.
    #Стандартный поток ошибок перенаправлен в пустоту.
    if [ "$pattern" == "l" ]; then #частный случай, если тип файла символьная сыллка, это необходимо,
        #потому что при таком типе ls -l выводит на 2 столбца больше и последний столбец указывает на файл, на который указывает ссылка
        name_file=$(echo "$file" | awk '{print $9}') # записываем в переменную название найденного файла
    else    
        name_file=$(echo "$file" | awk '{print $NF}') # записываем в переменную название найденного файла
    fi
    if [ -z "$file" ]; then #в случае, если файл заданного типа не найдем, выводим сообщение
        echo "Файл типа: ${pattern} не найден в директории: ${direct_find}"
        return
    fi
    get_path_by_type "$name_file" "$pattern" #вызываем функцию поиска пути к заданному файлу по его имени и типу
}

find_file "-" "/" #вызываем функцию поиска с заданным типом файла и директорией для поиска
find_file "b" "/"
find_file "c" "/"
find_file "d" "/"
find_file "l" "/"
find_file "p" "/"
find_file "s" "/"