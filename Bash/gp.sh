#!/usr/bin/env bash

set -euo pipefail

MODE="$1"
PATHS=(
  "$HOME/Homo_Deus/Programming"
  "$HOME/Homo_Deus/Mathematica_Compendium"
  "$HOME/Homo_Deus/Computer_Science_Compedium"
  "$HOME/dotfiles"
)

if [[ "$MODE" == "push" ]]; then
    echo "Pushing all repositories"
    read -p "Enter a commit message: " MESSAGE
    DATE="$(date)"

    for path in "${PATHS[@]}"; do
        cd "$path"
        git add .
        git commit -m "$MESSAGE ($DATE)" || echo "Nothing to commit in $path"
        git push -u origin main
    done

elif [[ "$MODE" == "pull" ]]; then
    echo "Pulling all repositories"
    for path in "${PATHS[@]}"; do
        cd "$path"
        git pull
    done

else
    echo "Invalid option selected. Enter either 'push' or 'pull'."
fi
