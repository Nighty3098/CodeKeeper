#!/bin/bash

cd src/CodeKeeper || { echo “Failed to go to src/CodeKeeper directory”; exit 1; }

qmake CodeKeeper.pro

echo Start compilation...
{ time make; } 2> compilation_time.txt

echo “Compilation complete.”
echo “Compilation time:”
cat compilation_time.txt
rm compilation_time.txt

cd ../.. || { echo “Failed to go to root directory”; exit 1; }