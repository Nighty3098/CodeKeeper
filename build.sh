#!/bin/bash

mkdir src/CodeKeeper/build || { echo Failed to create build directory; }
cd src/CodeKeeper/build || { echo Failed to go to src/CodeKeeper directory; }

qmake ../CodeKeeper.pro

echo Start compilation...
make

notify-send "CodeKeeper" "Build complete!"
echo Compilation complete.

cd ../../.. || { echo “Failed to go to root directory”; exit 1; }
