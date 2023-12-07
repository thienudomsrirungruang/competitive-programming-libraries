#!/usr/bin/bash

for((i = 1; i <= 10000000; ++i)); do
    echo $i
    python gen.py > int
    ./foo.exe < int > out1
    ./bar.exe < int > out2
    diff -w out1 out2 || break
done
