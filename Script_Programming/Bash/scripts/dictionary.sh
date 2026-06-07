#!/usr/bin/bash

word=$1
query=$(curl -s "https://api.dictionaryapi.dev/pi/v2/entries/en_US/$word")
echo "$query" | jq -e '.[0]' >/dev/null 2>&1 || { echo "Invalid Word"; exit 1; }

def=$(echo "$query" | jq -r '
    [.[0].meanings[].definitions[].definition]
    | .[:3]
    | join("\n")
')
printf '%s\n' "$def"
