g++ $1.cpp -O2 -Wshadow -Wall -o $1.exe -Wl,--stack,268435456 $3

./$1.exe < $2 > out.txt

cargo run --manifest-path ../tools/Cargo.toml --release --bin vis $2 out.txt