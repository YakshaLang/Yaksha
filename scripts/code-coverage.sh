#!/usr/bin/env bash
#-- This is to run inside docker container --#
cd /app || exit 1
mkdir build
mkdir bin
mkdir bin/fuzz
set -e
cd build || exit 1
# Build project
cmake -S .. -B . -DCMAKE_CXX_FLAGS="-fprofile-arcs -ftest-coverage -fPIC -O0 -fsanitize=address -static-libasan -g"
cmake --build .
# Fix test data by converting them all to unix format
cd ../test_data || exit 1
dos2unix *
cd ../bin || exit 1
# Run test cases
./YakshaTests
# Run Fuzzy testing
cd ../scripts && python3 kabaraya.py && cd ../bin
# Run sample
./Yaksha ../test_data/sample1.yaka
# Calculate code coverage
gcovr -r .. --exclude ../build --exclude ../tests --exclude ../3rd --html --html-details -o /coverage/index.html