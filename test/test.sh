#!/bin/bash

# finds all files named *.in, stores them in infiles
# executes command ../minishell < infiles[i]
# and compares the output with the corresponding *.out file
# if the output is different, prints the name of the test
# and the diff between the output and the *.out file
# if the output is the same, prints the name of the test
# and "OK"
# if the *.out file does not exist, prints the name of the test
# and "NO OUT FILE"

make re -C ..

infiles=$(find . -name "*.in")
for file in $infiles
do
    echo -en "\e[33mTesting: \e[35m$file\e[33m: \e[0m"
    ../minishell < $file > tmp
    if cmp -s tmp "${file%.in}.out"
    then
        echo -e "\e[32mOK\e[0m"
    else
        echo
		diff --color=auto tmp "${file%.in}.out"
        echo -e "\e[31mKO\e[0m"
    fi
done