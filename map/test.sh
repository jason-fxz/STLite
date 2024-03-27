#!/usr/bin/bash

tests=("one" "two" "three" "four" "five")
args="-fmax-errors=10 -O2 -DONLINE_JUDGE -lm -std=c++20"
memargs="-fmax-errors=10 -DONLINE_JUDGE -lm -std=c++20 -fsanitize=address,undefined,leak -g"

run_test() {
    mkdir testdir -p
    rm testdir/*
    cp src/*.hpp testdir
    cp data/class-bint.hpp testdir
    cp data/class-integer.hpp testdir
    cp data/class-matrix.hpp testdir
    for test in "${tests[@]}"
    do
        echo
        echo ">>> Test $test"
        cp "data/$test/code.cpp" testdir
        cp "data/$test/answer.txt" testdir
        g++ testdir/code.cpp -o testdir/code $args
        if [ $? -eq 0 ]; then
            echo "Test $test compiled successfully"
        else
            echo "Test $test compiled failed"
            exit 2
        fi
        echo "Running"
        time -p ./testdir/code > testdir/output.txt
        diff testdir/output.txt testdir/answer.txt
        if [ $? -eq 0 ]; then
            echo "Test $test passed"
        else
            echo "Test $test failed"
            echo "see files at \"./testdir/\""
            exit 1
        fi
    done
}


run_test_memcheck() {
    mkdir testdir -p
    rm testdir/*
    cp src/*.hpp testdir
    cp data/class-bint.hpp testdir
    cp data/class-integer.hpp testdir
    cp data/class-matrix.hpp testdir
    for test in "${tests[@]}"
    do
        echo
        echo ">>> Memory Check Test $test"
        cp "data/$test/code.cpp" testdir
        cp "data/$test/answer.txt" testdir
        g++ testdir/code.cpp -o testdir/code $memargs
        if [ $? -eq 0 ]; then
            echo "Test $test compiled successfully"
        else
            echo "Test $test compiled failed"
            exit 2
        fi
        echo "Running"
        time -p ./testdir/code > testdir/output.txt
        diff testdir/output.txt testdir/answer.txt
        if [ $? -eq 0 ]; then
            echo "Test $test passed"
        else
            echo "Test $test failed"
            echo "see files at \"./testdir/\""
            exit 1
        fi
    done
}

run_test
# run_test_memcheck

