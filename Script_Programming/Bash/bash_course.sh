#!/usr/bin/env/bash  

# to run any custom bash script we first need to make it executable via 
# chmod +x file.sh or +ux for a user and group execution permission. 

set -euo pipefail # this lines set bash to strict mode. Means that if errors occurrs then 
# execution of the script is aborted
# e for exit on error 
# u for exit for undefined references
# o pipefail for pipefail 

# Every Script starts with the "shebang". This tells the binary that we are using bash. 

# To run type: bash file.sh in the command line 

# Everything that is going to come can be also just be typed into the terminal and then be executed.
# You have all commands available which are installed in your system.

# The final goal is to automate certain tasks using bash. This file only contains syntax but in another file I will 
# write a bash script for dowloading all the packages I need in my system for development. This way I make the system more 
# reproducible.


# this is the header for the interpreter to use
echo Hello World!           # print

NAME=`whoami`                # command substitution with backticks (old syntax)

echo "$NAME"

#Variables
MY_VAR=Migu             # Capital camel Case for variables. No spaces between name and equal sign
echo Hello $MY_VAR      # $ for referencing Variables
echo Hello ${MY_VAR}    # $ for referencing Variables with nested functionality

# Printing the a variable in a string 
NAME="Migu"
echo "Hello, ${NAME}!" # this syntax with the curly braces allows inline manipulation of the varable 
echo "Hello, ${#NAME}!" # prints the lenght of the variavle 
echo "Hello, ${NAME:- "Value"}!" # default value if name is undefined 

# User input
echo Say
read FIRST_NAME         # ask for input
echo $FIRST_NAME

# Postional arguments
echo Say $1 $2   # Placeholders for arguments entered from the command line
# we can also create variables for the arguments 
FIRST=$1

# Subshell 
# This feature allows us to run commands our scripts without actually having the effects in the main 
# enviroment
# Example: Using command output as values
USER=$(whoami)
echo $user

# Command substitution vs Process substitution vs Subshell
#
# Proces substitution: <(command) or >(command)  # this is used to treat the output of a command as a file and then compare them.
# Subshell: (command)  # this is used to run commands in a subshell without actually having the effects in the main enviroment.
# Command substitution: $(command)  # this is used to use the output of a command as a value in a variable or in a command.

# Example: Basic
cd ; pwd # changes the directory and the prints the name  
(cd ..; pwd) # does not actually change the directory 

# Example: Arithmetic
echo $((4 + 4))

# Example:Process substitution 
# we treat the output of a command as a file and then compare them.
diff < $(ls ./v1) < $(ls ./v2) # treating the ouput of a command as a file and then comparing them

# Piping
#This is used for redirecting output of a programm to anoter as input, parameter, etc.

# | redirect  Example: ls -l /usr/bin | grep bash
# > overwrite to file
# >> append to a file
# < get content of file
# << 'EOF' multiple line of text to command unti a specific word is found Example: cat << EOF 
# <<< " " Single String of text

# Test

#To evaluate if a expression is true.
#Example 
#/$: [hello = hello]  
#/$: echo $?

#if elif else
# in between [[ ]] we need to use spaces for the test expression.
if [ ${1,,}=herbert ]; then  #take a positional argument (first) {,,} for ignoring case in the test expression
        echo "Moin"
elif [ ${1,,}=help ]; then   ##same
        echo "Help needed"
else 
    echo "Sike"
fi 

# Exit codes
# 0 for succes and anything else is a failure 

# Conditionals 
# [[ ]]
# String comparasion 
VAL="a"
[[ "$VAL" == "a" ]]
[[ "$VAL" != "b" ]]
#
# There is also the `=~` operator, which tests a string against the Regex pattern:
EMAIL=me@example.com
if [[ "$EMAIL" =~ [a-z]+@[a-z]{2,}\.(com|net|org) ]]
then
    echo "Valid email!"
fi
# Numeriacal comparasion 
NUM=1
[[ "$num" -eq 1 ]]
[[ "$num" -ne 1 ]]
[[ "$num" -lt 1 ]]
[[ "$num" -le 1 ]]
[[ "$num" -ge 1 ]]
[[ "$num" -gt 1 ]]
#
# Variable existence 
VAL=""
[[ -z $VAL ]] # var is null 
[[ -n $VAL ]] # var is not-null 
#
#File checks 
FILE="./hellot.txt"
[[ -f $FILE ]] # file exists
[[ -d $FILE ]]  # dir exists 
[[ -e $FILE ]] # file/dir exists 

SECOND_NAME="Alice"

echo "--- Internal Logical Operators with [[ ... ]] ---"

# Internal AND (&& / -a): Both conditions must be true
if [[ "John" == "John" && "$SECOND_NAME" == "Alice" ]]; then
    echo "Internal AND: Both names match."
fi

# Internal OR (|| / -o): At least one condition must be true
if [[ "Bob" == "Charlie" || "$SECOND_NAME" == "Alice" ]]; then
    echo "Internal OR: At least one condition is true."
fi

# External AND (&&): Command on the right runs ONLY if command on the left succeeds (exit status 0)
echo "Command 1 succeeded" && echo "External AND: This message also appears."

# External OR (||): Command on the right runs ONLY if command on the left fails (non-zero exit status)
false || echo "External OR: The 'false' command failed, so this message appears."

# Case Statements
case ${1,,} in
    herbert | admin) 
        echo "Digga";;
    help)
        echo "Help";;
    *)
        echo "Sike";;

esac

# Arrays
MY_LIST=(one two three)

echo $MY_LIST      # print first only
echo "${MY_LIST[@]}" # print all
echo ${MY_LIST[0]} # print at index

# For Loops

# Loop through the array
for item in "${MY_LIST[@]}"; do 
    echo -n $item | wc -c; 
done

# C-style
for ((i=0; i < 10; i++)); do 
    echo "$i"; 
done

# Range
for i in {1..10}; do 
    echo "$i"; 
done

# Pattern matching
for item in ./content/*.md; do 
    echo "$item"; 
done # with pattern matching

# Loop through the output of a command
for i in $(globs); do 
    echo "$i"; 
done # command result

# While loops 

while read line; do 
    echo "$line"; 
done < file.txt # read from file

while [[ $COUNT -lt 10 ]]; do 
    echo "$COUNT"; 
    ((COUNT++)); 
done # while loop with condition

# Multiple files 
# Bash has no concepts of namespaces or modules. we want to 
# use other scripts we call them with the source command or the dot command `./other_script.sh` or `source other_script.sh`.
# we can also source the script by prefixig with a dot and a space `. other_script.sh` (put all the contents of the other script 
# into the current script).


# Functions
# functions do not have parameters properly we just pass them as positional arguments.
function showuptime() {
    echo Hello $1
    local up=$(uptime - p  | cut -c4-) # declaring local var
    local since=$(uptime -s)
    cat << EOF
---
This machine has been up for ${up}
It has been running since ${since}
---
EOF
}


showuptime Herbert #function plus "parameter"

# AWK
awk -F,'{print $1}' test.txt #get firt word after coma

# Find all log files modified in the last 24 ours 
find . -name "*.log" -mtime -1




