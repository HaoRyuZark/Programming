#!/bin/bash

# Declare an array of directories
DIRECTORIES=(
    "$HOME/Homo_Deus/Mathematica_Compendium"
    "$HOME/Homo_Deus/Cheat_Sheets"
    "$HOME/Homo_Deus/Computer_Science_Compendium"
    "$HOME/Homo_Deus/Programming/Bash/"
    "$HOME/Homo_Deus/Programming/DSA/"
)

# Loop through each directory and run git commands

for item in "${DIRECTORIES[@]}"; do
    if [ -d "$item/.git" ]; then
        echo "Processing $item"
        cd "$item" || continue
        git pull
    else
        echo "Skipping $item (not a git repo)"
    fi
done
