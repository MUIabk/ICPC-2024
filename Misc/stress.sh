g++ $1.cpp -o $1.o
g++ $2.cpp -o $2.o
g++ $3.cpp -o $3.o
for ((testNum=0;testNum<$4;testNum++))
do
    ./$3.o > input
    ./$2.o < input > outSlow
    # python3 $2.py < input > outSlow
    ./$1.o < input > outWrong
    echo "Test case ${testNum} passed"
    if !(cmp -s "outWrong" "outSlow")
    then
        echo "Error found!"
        echo "Input:"
        cat input
        echo "Wrong Output:"
        cat outWrong
        echo "Slow Output:"
        cat outSlow
        exit
    fi
done
echo Passed $4 tests

//run.sh
g++ $1.cpp -std=c++17 -O2 -Wall -o $1.out && ./$1.out
