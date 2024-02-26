#!/bin/bash                                                         
                                                                    #указываем интерпретатор 
temp=$1                                                             #переменная для считывания названия файла для логгирования
logfile="/home/egor/OC/$temp"                                       #записываем полный путь, чтобы при переходе в другие директории файл логов оставлся по прежнему пути

dopwritter=$2                                                       #переменная для флага --dop
username="$USER"                                                    #переменная для сохранения имени пользователя
hostname="$HOSTNAME"                                                #переменная для сохранения хостового имени (используется для идентификации устройства в сети)


if [[ $dopwritter == "--dop" ]]; then                               #проверяем условие установлен ли флаг --dop, чтобы дописывать логи в файл, а не создавать новый
    echo "Continue work: $(date)" >> "$logfile"                     #записываем в лог файл запись о продолжении работы и устанавливаем дату с помощью $(date)
else                                                                #выполняем в случае, если основное условие не выполнилось
    >"$logfile"                                                     #создаем файл с именем, которое находится в переменной logfile
    echo "Started work: $(date)" >> "$logfile"                      #записываем в лог файл запись о начале работы и устанавливаем дату с помощью $(date)
fi



while true; do                                                      #запускаем бесконечный цикл
    current_directory="$(pwd)"                                      #записываем в переменную путь к текущей директории, для того, чтобы знать, в какой директории находимся
    
    read -p "$username@$hostname:$current_directory$ " command      #выводим в терминал имя пользователя, имя хоста и текущую директорию, затем считываем комманду в переменную command
    first_two="${command:0:2}"                                      #записываем в переменную первые две буквы из переменной command для дальнейшей проверки на cd для корректного перехода между директориями
    first_three="${command:0:3}"                                    #записываем в переменную первые три буквы из переменной command для дальнейшей проверки на открытие редактора vim
    if [[ $command == "exit" ]]; then                               #проверка на завершение данного скрипта
        echo "Work is finished: $(date)" >> "$logfile"              #записываем в лог файл информацию о завершии работы 
        exit 0                                                      #завершаем работу скрипта
    elif [[ $first_two == "cd" ]]; then                             #проверяем на комманду cd
        echo "--------$(date +%T)-------- \$ $command" >> "$logfile"#если команда cd, то записываем ее в лог файл
        eval "$command"                                             #выполняем команду cd
    elif [[ $first_three == "vim" ]]; then                          #проверяем на комманду vim
        echo "--------$(date +%T)-------- \$ $command" >> "$logfile"#если команда vim, то записываем ее в лог файл
        eval "$command"                                             #выполняем команду vim
    else                                                            #если не попали внутри условных операторов
        echo "--------$(date +%T)-------- \$ $command" >> "$logfile"#заносим наименование команды в лог файл
        eval "$command 2>&1 | tee -a $logfile"                      #выполняем комманду, содержащуюся в переменной command, так же здесь происходит перенаправление из потока ошибок (2>) в стандартный поток вывода (&1).
                                                                    #затем с помощью "|" в утилиту tee передаются данные после использования комманды, данная утилита записывает вывод команды в файл и одновременно с эти выводит их на экран
        
        
    fi
done
