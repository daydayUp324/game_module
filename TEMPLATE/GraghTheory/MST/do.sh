#! /bin/bash

g++ -c mst.cpp -std=c++17

g++ mst.o -o main

cat data.txt | ./main
