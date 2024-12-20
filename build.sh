#!/bin/bash

# Define color codes for better readability
GREEN="\e[1;32m"
YELLOW="\e[1;33m"
RED="\e[1;31m"
RESET="\e[0m"

#bash clang_format.sh

# Change to the CodeKeeper source directory
echo -e "${GREEN}Navigating to the CodeKeeper source directory...${RESET}"
cd src/CodeKeeper/ || { echo -e "${RED}Error: Failed to change directory to src/CodeKeeper.${RESET}"; exit 1; }

# Run qmake and check for success
echo -e "${GREEN}Running qmake...${RESET}"
qmake6 CodeKeeper.pro
if [ $? -ne 0 ]; then
    echo -e "${RED}Error: qmake6 command failed. Please check the .pro file and dependencies.${RESET}"
    exit 1;
fi

# Start the compilation process
echo -e "${GREEN}Starting compilation...${RESET}"
make
if [ $? -ne 0 ]; then
    echo -e "${RED}Error: make command failed. Compilation was not successful.${RESET}"
    exit 1;
fi

# Notify user upon successful build
echo -e "${GREEN}Compilation successful, sending notification...${RESET}"
notify-send "CodeKeeper" "Build complete!"
echo -e "${GREEN}Compilation complete.${RESET}"

echo -e "${GREEN}Copying bin file to main directory...${RESET}"
chmod +x CodeKeeper
cp CodeKeeper ../../ || { echo -e "${RED}Error: Failed to copy bin file to the root directory.${RESET}"; exit 1; }

# Return to the root directory
echo -e "${GREEN}Navigating back to the root directory...${RESET}"
cd ../.. || { echo -e "${RED}Error: Failed to return to the root directory.${RESET}"; exit 1; }

echo -e "${GREEN}"
echo -e " ▄████▄   ▒█████  ▓█████▄ ▓█████  ██ ▄█▀▓█████ ▓█████  ██▓███  ▓█████  ██▀███"
echo -e "▒██▀ ▀█  ▒██▒  ██▒▒██▀ ██▌▓█   ▀  ██▄█▒ ▓█   ▀ ▓█   ▀ ▓██░  ██▒▓█   ▀ ▓██ ▒ ██▒"
echo -e "▒▓█    ▄ ▒██░  ██▒░██   █▌▒███   ▓███▄░ ▒███   ▒███   ▓██░ ██▓▒▒███   ▓██ ░▄█ ▒"
echo -e "▒▓▓▄ ▄██▒▒██   ██░░▓█▄   ▌▒▓█  ▄ ▓██ █▄ ▒▓█  ▄ ▒▓█  ▄ ▒██▄█▓▒ ▒▒▓█  ▄ ▒██▀▀█▄"
echo -e "▒ ▓███▀ ░░ ████▓▒░░▒████▓ ░▒████▒▒██▒ █▄░▒████▒░▒████▒▒██▒ ░  ░░▒████▒░██▓ ▒██▒"
echo -e "░ ░▒ ▒  ░░ ▒░▒░▒░  ▒▒▓  ▒ ░░ ▒░ ░▒ ▒▒ ▓▒░░ ▒░ ░░░ ▒░ ░▒▓▒░ ░  ░░░ ▒░ ░░ ▒▓ ░▒▓░"
echo -e "  ░  ▒     ░ ▒ ▒░  ░ ▒  ▒  ░ ░  ░░ ░▒ ▒░ ░ ░  ░ ░ ░  ░░▒ ░      ░ ░  ░  ░▒ ░ ▒░"
echo -e "░        ░ ░ ░ ▒   ░ ░  ░    ░   ░ ░░ ░    ░      ░   ░░          ░     ░░   ░"
echo -e "░ ░          ░ ░     ░       ░  ░░  ░      ░  ░   ░  ░            ░  ░   ░"
echo -e "░                  ░${RESET}"

echo -e ""
echo -e "${YELLOW}"
echo -e "                                CodeKeeper"
echo -e "                           Created by Nighty3098"
echo -e "                              Copyright 2024"


