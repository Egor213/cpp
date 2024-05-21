#!/bin/bash

file="test_size"
#$(rm -fr $file) # удаляем директорию, если она есть
#$(mkdir $file)  #создаем папку
echo "File is "$file""
echo "Start size : $(ls -ld $file | awk '{print $5}')" #выводим стартовый размер

create_file() {                     #функция для создания файла
    file_name="$1/file$2.txt"       #полное имя файла
    $(touch $file_name)             #создание файла
    echo "testinggggg" >>$file_name #запись информации в файл
}

create_dir() {          #функция для создания папки
    dir_name="$1/dir$2" #полное имя
    $(mkdir $dir_name)  #создание директории
}

clean_all() { #функция для полной очистки директории
    $(rm -rf $1/*)
}
max_entries=0
for i in {1..1140}; do #цикл создания папок и файлов
    create_file "$file" "$i"
    create_dir "$file" "$i"
done

echo "After add file and folder size : $(ls -ld $file | awk '{print $5}')" #конечный вывод
clean_all "$file"
echo "After delete all file and folder size : $(ls -ld $file | awk '{print $5}')" #вывод после удаления всех файлов и директории
