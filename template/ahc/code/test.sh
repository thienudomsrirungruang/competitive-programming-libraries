#!/bin/sh
echo Clearing;
rm -rfv in/*
rm -rfv vis/*
> seeds.txt;
> scores.txt;

echo Compiling;
g++ $1.cpp -O2 -Wshadow -Wall -o $1.exe -Wl,--stack,268435456;

echo Preparing seeds;
i=0;
while [ "$i" -lt "$2" ]; do
    echo $i >> seeds.txt;
    i=$(($i + 1));
done
echo Running generator;
cargo run --manifest-path ../tools/Cargo.toml --release --bin gen seeds.txt;

echo Evaluating;
sum=0;
maxtime=0;
num=0;
for i in in/*
do
    time1=$(date +%s%N);
    ./$1.exe < $i > out.txt;
    time2=$(date +%s%N);
    diff=$((($time2-$time1)/1000000));
    cargo run --manifest-path ../tools/Cargo.toml --release --bin vis $i out.txt > result.txt;
    score=$(cat result.txt);
    # echo $score;
    echo $i: $score \($diff ms\) >> scores.txt;
    sum=$((sum + score));
    if [ "$diff" -gt "$maxtime" ]
    then
        maxtime=$((diff));
    fi
    cp out.svg vis/$num.svg;
    num=$((num+1));
done
echo Total: $sum Average: $((sum / $2)) Time: $maxtime ms;

echo Total: $sum Average: $((sum / $2)) Time: $maxtime ms >> scores.txt;
