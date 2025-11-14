#!/usr/bin/env bash

set -euo pipefail

dconf dump /org/gnome/shell/extensions/ > gnome_extensions.txt

