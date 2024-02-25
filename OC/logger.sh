#!/bin/bash 
temp=$1
logfile="/home/egor/OC/$temp"

dopwritter=$2
username="$USER"
hostname="$HOSTNAME"


if [[ $dopwritter == "--dop" ]]; then
    echo "Continue work: $(date)" >> "$logfile"
else
    >"$logfile"
    echo "Started work: $(date)" >> "$logfile"
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
