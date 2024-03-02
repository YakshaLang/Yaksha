#!/usr/bin/env bash
#-- This is to run inside docker container --#
cd /app || exit 1
mkdir build
mkdir bin
mkdir bin/fuzz
cp /app/test.txt bin/test.txt
find . -type f -exec dos2unix {} \;
set -e
cd build || exit 1
# Build project
cmake -G Ninja -S .. -B . -DCMAKE_CXX_FLAGS="-fprofile-arcs -ftest-coverage -fPIC -O0 -fsanitize=address -static-libasan -g"
cmake --build . -- -j 24
# Run test cases
echo "██    ██ ███    ██ ██ ████████     ████████ ███████ ███████ ████████"
echo "██    ██ ████   ██ ██    ██           ██    ██      ██         ██"
echo "██    ██ ██ ██  ██ ██    ██           ██    █████   ███████    ██"
echo "██    ██ ██  ██ ██ ██    ██           ██    ██           ██    ██"
echo " ██████  ██   ████ ██    ██           ██    ███████ ███████    ██"
ninja test
# Build carpntr
cd ../carpntr
rm -rf build
mkdir build
python3 bootstrap_me.py
# Disable exit on error so we can run the rest of the commands
set +e
cd ../scripts
# Run e2e tests
python3 e2e.py
# Run yaksha ast
../bin/yaksha ast ../carpntr/main.yaka
# Run libdocs.py
mkdir ../comp_output_test
python3 libdocs.py
# Run Fuzzy testing
echo "██   ██  █████  ██████   █████  ██████   █████  ██    ██  █████ "
echo "██  ██  ██   ██ ██   ██ ██   ██ ██   ██ ██   ██  ██  ██  ██   ██"
echo "█████   ███████ ██████  ███████ ██████  ███████   ████   ███████"
echo "██  ██  ██   ██ ██   ██ ██   ██ ██   ██ ██   ██    ██    ██   ██"
echo "██   ██ ██   ██ ██████  ██   ██ ██   ██ ██   ██    ██    ██   ██"
echo "--------------------- Simple Fuzzy Testing ---------------------"
cd ../scripts && python3 kabaraya.py && cd ../bin
# Calculate code coverage
gcovr -r .. --exclude ../build --exclude ../tests --exclude ../3rd --html --html-details -o /coverage/index.html
