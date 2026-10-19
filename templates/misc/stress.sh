#!/bin/bash
# stress test: compares sol.cpp with brute.cpp on random inputs from gen.cpp
# gen.cpp reads a seed from argv[1] and prints one test. usage: bash stress.sh 1000
g++ -std=c++14 -O2 -o sol sol.cpp || exit
g++ -std=c++14 -O2 -o brute brute.cpp || exit
g++ -std=c++14 -O2 -o gen gen.cpp || exit
for ((i = 1; i <= ${1:-1000}; i++)); do
    ./gen $i > in.txt
    ./sol < in.txt > out1.txt
    ./brute < in.txt > out2.txt
    if ! cmp -s out1.txt out2.txt; then
        echo "mismatch on test $i"; cat in.txt
        echo "sol:"; cat out1.txt
        echo "brute:"; cat out2.txt
        exit
    fi
done
echo "all $1 tests passed"
