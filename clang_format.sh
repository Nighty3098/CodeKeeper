#!/bin/bash

find . -type f -name "*.cpp" | while read -r file; do
    clang-format -i "$file"
    echo "Formatted $file"
done
