#!/bin/fish
echo "g++ -O1 -m64:" 
echo "g++ -O1 -m64:" > m64.txt
g++ lab_1_benchmark.cpp -O1 -m64
./a.out >> m64.txt

echo "g++ -O1 -m32:" 
echo "g++ -O1 -m32:" > m32.txt
g++ lab_1_benchmark.cpp -O1 -m32
./a.out >> m32.txt