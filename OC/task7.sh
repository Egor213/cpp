#!/bin/bash

file="test_size"
$(rm -fr $file)
$(mkdir $file)
echo "File is "$file""
echo "Start size : $(ls -ld $file | awk '{print $5}')"

create_file(){
    file_name="$1/file$2.txt"
    $(touch $file_name)
    echo "testinggggg" >> $file_name
}

create_dir(){
    dir_name="$1/dir$2"
    $(mkdir $dir_name)
}

clean_all(){
    $(rm -rf $1/*)
}
max_entries=0
for i in {1..114}; do
    create_file "$file" "$i"
    create_dir "$file" "$i"
done

echo "After add file and folder size : $(ls -ld $file | awk '{print $5}')"
clean_all "$file"
echo "After delete all file and folder size : $(ls -ld $file | awk '{print $5}')"


