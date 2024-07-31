#!/bin/bash

# Remove unnecessary files
echo "Removing unnecessary files..."
rm -rf src/CodeKeeper/.qtc_clangd
rm -rf src/CodeKeeper/build
rm src/CodeKeeper/CodeKeeper.pro.user
rm src/CodeKeeper/CodeKeeper.pro.user.1f90c22
rm src/CodeKeeper/main.o
rm src/CodeKeeper/Makefile
rm src/CodeKeeper/markdownhighlighter.o
rm src/CodeKeeper/moc_linenumberarea.cpp
rm src/CodeKeeper/moc_linenumberarea.o
rm src/CodeKeeper/moc_mainwindow.cpp
rm src/CodeKeeper/moc_mainwindow.o
rm src/CodeKeeper/moc_markdownhighlighter.cpp
rm src/CodeKeeper/moc_markdownhighlighter.o
rm src/CodeKeeper/moc_predefs.h
rm src/CodeKeeper/moc_qmarkdowntextedit.cpp
rm src/CodeKeeper/moc_qmarkdowntextedit.o
rm src/CodeKeeper/moc_qplaintexteditsearchwidget.cpp
rm src/CodeKeeper/moc_qplaintexteditsearchwidget.o
rm src/CodeKeeper/moc_settingswindow.cpp
rm src/CodeKeeper/moc_settingswindow.o
rm src/CodeKeeper/moc_syncwindow.cpp
rm src/CodeKeeper/moc_syncwindow.o
rm src/CodeKeeper/qmake_qmake_immediate.qrc
rm src/CodeKeeper/qmarkdowntextedit.o
rm src/CodeKeeper/qownlanguagedata.o
rm src/CodeKeeper/qplaintexteditsearchwidget.o
rm src/CodeKeeper/qrc_media.cpp
rm src/CodeKeeper/qrc_media.o
rm src/CodeKeeper/qrc_qmake_qmake_immediate.cpp
rm src/CodeKeeper/qrc_qmake_qmake_immediate.o
rm src/CodeKeeper/qrc_resources.cpp
rm src/CodeKeeper/qrc_resources.o
rm src/CodeKeeper/settings.json
rm src/CodeKeeper/settingswindow.o
rm src/CodeKeeper/syncwindow.o
rm src/CodeKeeper/ui_qplaintexteditsearchwidget.h
rm src/CodeKeeper/accountwindow.o
rm src/CodeKeeper/moc_accountwindow.cpp
rm src/CodeKeeper/moc_accountwindow.o
rm src/CodeKeeper/object_script.CodeKeeper.Debug
rm src/CodeKeeper/object_script.CodeKeeper.Release
rm src/CodeKeeper/CircledProgressBar.o
rm src/CodeKeeper/moc_CircledProgressBar.o
rm src/CodeKeeper/moc_CircledProgressBar.cpp
rm src/CodeKeeper/moc_ProgressCircle.cpp
rm src/CodeKeeper/moc_ProgressCircle.o
rm src/CodeKeeper/ProgressCircle.o
rm src/CodeKeeper/moc_CircleChart.cpp
rm src/CodeKeeper/moc_ColorValueDisplay.cpp
rm src/CodeKeeper/moc_CircleChart.o
rm src/CodeKeeper/moc_ColorValueDisplay.o

# Format all .cpp files
echo "Formatting all .cpp files..."
find src/CodeKeeper -type f -name "*.cpp" | while read -r file; do
    clang-format -i "$file"
    echo "Formatted $file"
done

# Change to the project directory
cd src/CodeKeeper || { echo "Failed to go to src/CodeKeeper directory"; exit 1; }

# Run qmake
qmake CodeKeeper.pro

# Compile the project and measure time
echo "Start compilation..."
{ time make; } 2> compilation_time.txt

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation complete."
    echo "Compilation time:"
    cat compilation_time.txt
    rm compilation_time.txt

    # Ask for commit message and push changes
    read -p "Enter commit message: " commit_message
    git add .
    git commit -m "$commit_message"
    git push
else
    echo "Compilation failed. Please check the errors above."
    rm compilation_time.txt
fi

# Change back to the root directory
cd ../.. || { echo "Failed to go to root directory"; exit 1; }
