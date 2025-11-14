#!/usr/bin/env bash

set -euo pipefail

dconf dump /org/gnome/shell/keybindings/ > ~/dotfiles/gnome_keybinds.txt


