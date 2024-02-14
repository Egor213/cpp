#!/bin/bash 
logfile=$1
dopwritter=$2
username="$USER"
hostname="$HOSTNAME"
current_directory="$(pwd)"

if [[ $dopwritter == "--dop" ]]; then
    echo "Continue work: $(date)" >> "$logfile"
else
    >"$logfile"
    echo "Started work: $(date)" >> "$logfile"
fi



while true; do
    read -p "$username@$hostname:$current_directory$ " command
    if [[ $command == "exit" ]]; then
        echo "Work is finished: $(date)" >> "$logfile"
        exit 0
    else
        echo "--------$(date +%T)-------- \$ $command" >> "$logfile"
        eval "$command" >> "$logfile"
        eval "$command"
        
        
    fi
done
