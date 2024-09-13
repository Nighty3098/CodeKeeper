#!/bin/bash

cd src/CodeKeeper || { echo Failed to go to src/CodeKeeper directory; exit 1; }

qmake CodeKeeper.pro

echo Start compilation...
make

notify-send "CodeKeeper" "Build complete!"
echo Compilation complete.

cd ../.. || { echo “Failed to go to root directory”; exit 1; }
