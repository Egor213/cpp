#!/bin/bash                                                         
                                                                    #указываем интерпретатор 
temp=$1                                                             #переменная для считывания названия файла для логгирования
logfile="/home/egor/OC/$temp"                                       #записываем полный путь, чтобы при переходе в другие директории файл логов оставлся по прежнему пути

dopwritter=$2                                                       #переменная для флага --dop
username="$USER"                                                    #переменная для сохранения имени пользователя
hostname="$HOSTNAME"                                                #переменная для сохранения хостового имени (используется для идентификации устройства в сети)


if [[ $dopwritter == "--dop" ]]; then                               #проверяем условие установлен ли флаг --dop, чтобы дописывать логи в файл, а не создавать новый
    echo "Continue work: $(date)" >> "$logfile"                     #записываем в лог файл запись о продолжении работы и устанавливаем дату с помощью $(date)
else
    >"$logfile"                                                     #создаем файл с именем, которое находится в переменной logfile
    echo "Started work: $(date)" >> "$logfile"                      #записываем в лог файл запись о начале работы и устанавливаем дату с помощью $(date)
fi



while true; do
    current_directory="$(pwd)"
    
    read -p "$username@$hostname:$current_directory$ " command
    first_two="${command:0:2}"
    first_three="${command:0:3}"
    if [[ $command == "exit" ]]; then
        echo "Work is finished: $(date)" >> "$logfile"
        exit 0
    elif [[ $first_two == "cd" ]]; then
        echo "--------$(date +%T)-------- \$ $command" >> "$logfile"
        eval "$command"
    elif [[ $first_three == "vim" ]]; then
        echo "--------$(date +%T)-------- \$ $command" >> "$logfile"
        eval "$command"
    else
        echo "--------$(date +%T)-------- \$ $command" >> "$logfile"
        eval "$command 2>&1 | tee -a $logfile"
        
        
    fi
done
