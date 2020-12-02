#!/bin/bash
OUT=./out
if [ ! -d "$OUT" ]; then
    mkdir $OUT
fi
echo "Compiling day $1..."
if g++ -std=c++11 ./src/day$1.cpp -o ./out/day$1; then
	echo "Compilation successful"
	echo "Running executable..."
	./out/day$1
else
	echo "Compilation failed: Exit code $?"
fi
