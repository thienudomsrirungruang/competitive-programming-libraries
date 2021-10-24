for((i = 1; i <= 10000000; ++i)); do
    echo $i
    python egen.py > int
    ./e.exe < int > out1
    ./eold.exe < int > out2
    diff -w out1 out2 || break
done
