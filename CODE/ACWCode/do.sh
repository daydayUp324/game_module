#! /bin/bash

g++ -c main.cpp -std=c++17

# g++ -c main.cpp

g++ main.o -o main

cat data.txt | ./main
