mkdir testdir
cp src/priority_queue.hpp testdir
cp src/exceptions.hpp testdir
cp src/utility.hpp testdir
cp data/class-bint.hpp testdir
cp data/class-integer.hpp testdir
cp data/class-matrix.hpp testdir


echo "Running test one"
cp data/one/code.cpp testdir
cp data/one/answer.txt testdir
g++ testdir/code.cpp -o testdir/code -fmax-errors=10 -O2 -DONLINE_JUDGE -lm -std=c++20
if [ $? -eq 0 ]; then
    echo "Test one compiled successfully"
else
    echo "Test one compiled failed"
    exit 2
fi
./testdir/code > testdir/output.txt
diff testdir/output.txt testdir/answer.txt
if [ $? -eq 0 ]; then
    echo "Test one passed"
else
    echo "Test one failed"
    exit 1
fi


echo "Running test two"
cp data/two/code.cpp testdir
cp data/two/answer.txt testdir
g++ testdir/code.cpp -o testdir/code -fmax-errors=10 -O2 -DONLINE_JUDGE -lm -std=c++20
if [ $? -eq 0 ]; then
    echo "Test two compiled successfully"
else
    echo "Test two compiled failed"
    exit 2
fi
./testdir/code > testdir/output.txt
diff testdir/output.txt testdir/answer.txt
if [ $? -eq 0 ]; then
    echo "Test two passed"
else
    echo "Test two failed"
    exit 1
fi


echo "Running test three"
cp data/three/code.cpp testdir
cp data/three/answer.txt testdir
g++ testdir/code.cpp -o testdir/code -fmax-errors=10 -O2 -DONLINE_JUDGE -lm -std=c++20 -fsanitize=address
if [ $? -eq 0 ]; then
    echo "Test three compiled successfully"
else
    echo "Test three compiled failed"
    exit 2
fi
./testdir/code > testdir/output.txt
diff testdir/output.txt testdir/answer.txt
if [ $? -eq 0 ]; then
    echo "Test three passed"
else
    echo "Test three failed"
    exit 1
fi

echo "Running test four"
cp data/four/code.cpp testdir
cp data/four/answer.txt testdir
g++ testdir/code.cpp -o testdir/code -fmax-errors=10 -O2 -DONLINE_JUDGE -lm -std=c++20
if [ $? -eq 0 ]; then
    echo "Test four compiled successfully"
else
    echo "Test four compiled failed"
    exit 2
fi
./testdir/code > testdir/output.txt
diff testdir/output.txt testdir/answer.txt
if [ $? -eq 0 ]; then
    echo "Test four passed"
else
    echo "Test four failed"
    exit 1
fi

echo "Running test five"
cp data/five/code.cpp testdir
cp data/five/answer.txt testdir
g++ testdir/code.cpp -o testdir/code -fmax-errors=10 -O2 -DONLINE_JUDGE -lm -std=c++20
if [ $? -eq 0 ]; then
    echo "Test five compiled successfully"
else
    echo "Test five compiled failed"
    exit 2
fi
./testdir/code > testdir/output.txt
diff testdir/output.txt testdir/answer.txt
if [ $? -eq 0 ]; then
    echo "Test five passed"
else
    echo "Test five failed"
    exit 1
fi