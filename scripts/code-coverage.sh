#!/usr/bin/env bash
# --- Runs inside docker container ---
cd /app || exit 1
mkdir build
mkdir bin
mkdir bin/fuzz
set -e
cd build || exit 1
# Build Project
cmake -S .. -B . -DCMAKE_CXX_FLAGS="-fprofile-arcs -ftest-coverage -fPIC -O0"
cmake --build .
cd ../test_data || exit 1
dos2unix *
# Run tests
cd ../bin || exit 1
./YakshaTests
# Run Fuzzy testing
cd ../scripts && python3 fuzzer.py && cd ../bin
# Run sample1
./Yaksha ../test_data/sample1.yaka
# Calculate code coverage
gcovr -r .. --exclude ../build --exclude ../tests --exclude ../3rd --html --html-details -o /coverage/index.html
