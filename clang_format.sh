#!/bin/bash

GREEN="\e[1;32m"
YELLOW="\e[1;33m"
RED="\e[1;31m"
RESET="\e[0m"

find . -type f -name "*.cpp" | while read -r file; do
    if clang-format -i "$file"; then
        printf "${GREEN}Formatted: %s${RESET}\n" "$file"
    else
        printf "${RED}Failed to format: %s${RESET}\n" "$file"
        exit 1
    fi
done
