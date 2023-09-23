#!/bin/bash

infiles=$(find . -name "*.in")
for file in $infiles
do
    echo -en "\e[33mTesting: \e[35m$file\e[33m: \e[0m"
    while IFS= read -r line || [ -n "$line" ]; do
        echo minishell'$' "$line"
        eval "$line"
    done < "$file" > "${file%.in}.out"
    echo "minishell$ exit" >> "${file%.in}.out"
    echo -e "\e[32mOK\e[0m"
done