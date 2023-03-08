#!/bin/sh
rm test_out.csv
gcc main.c -lm -o main
./main >> test_out.csv
