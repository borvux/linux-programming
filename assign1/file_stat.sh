#!/bin/bash

#to print the header
header() {
    printf "Filename\t\t\t\t\t\tSize\tLast Modified\n"
    printf "==============================                         =====   ===============\n"
}

#to print the output
details() {
    #go through all the files in the directory $1
    for file in $(find "$1" -type f)
    do
        #cut the file name
        file_name=$(echo $file | sed 's/\.\.\/Hands-on-System-Programming-with-Linux-master\///g')

        #get the file size
        size=$(stat -c %s "$file")

        #get the file date
        date=$(stat -c %y "$file")

        #print the file name, file size, file date
        printf "%-55s %-7d %s\n" "./$file_name" "$size" "$date"
    done
}

#checking the directory
directory_check() {

    #if the directory is not found
    if [ $# -eq 0 ]; then

        #ask user for directory
        printf "Enter name of directory to scan: "
        read directory

        #if the directory is not found, then output error message
        if [ ! -d "$directory" ]; then
            echo "$directory is not a directory."
            exit 1
        fi

        #print the directory information
        echo "$directory"
        header
        details "$directory"
    
    #if the directory is provided
    else
        #if the directory is not found, then output error message
        if [ ! -d "$1" ]; then
            echo "$1 is not a directory."
            exit 1
        fi

        #print the directory information
        echo "$1"
        header
        details "$1"
    fi
}

#call the funtion 
directory_check "$@"

exit 0
