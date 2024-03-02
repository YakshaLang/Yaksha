#!/usr/bin/env bash
#-- This is to run inside docker container --#
cd /app || exit 1
mkdir build
mkdir bin
mkdir bin/fuzz
cp /app/test.txt bin/test.txt
find . -type f -exec dos2unix {} \;
cd test_data || exit 1
dos2unix *
cd ..
# Run LibFuzzer fuzzy testing
echo "██      ██      ██    ██ ███    ███"
echo "██      ██      ██    ██ ████  ████"
echo "██      ██      ██    ██ ██ ████ ██"
echo "██      ██       ██  ██  ██  ██  ██"
echo "███████ ███████   ████   ██      ██"
echo "---------------FUZZER--------------"
mkdir fuzz-build
cd fuzz-build
export YAKSHA_FUZZ=1
CC=clang-12 CXX=clang++-12 cmake -S .. -B .
cmake --build . --target YakshaFuzz
cd ../bin
./YakshaFuzz -fork=2 ../test_data
cp crash-* /fuzz
cp leak-* /fuzz
cp timeout-* /fuzz