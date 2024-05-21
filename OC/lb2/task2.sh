#!/bin/bash

#данный не обрабатывается некорректные пути или несуществующие файлы, нужно указываь полный путь!

file=$1 #получаем путь к файлу или директории

get_inode=$(sudo ls -di1 "$file" | awk '{print $1}')                         #получаем номер inode
mapfile -t my_array < <(sudo ls -Rlia / 2>/dev/null | grep "^$get_inode ") #производим поиск всех файлов с таким же номером inode и записываем в массив

for element in "${my_array[@]}"; do #с помощью цикла выводим содержимое массива
    echo "$element"
done


sudo find / -inum $get_inode 2>/dev/null