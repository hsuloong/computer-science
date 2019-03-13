/*
This file is a practice for Deng Junhui's book: "data structure[ISBN:9787302330646]"

Question:
Calculate Fibonacci sequence.
F(0) = 0, F(1) = 1...F(n) = F(n-1) + F(n-2).
*/
#include <iostream>
#include <chrono>

typedef unsigned long long(*funcPtr)(unsigned int);

/*A O(2^n) Algorithm*/
static unsigned long long fibonacci_power2n(unsigned int index)
{
    if (index <= 1) {
        return unsigned long long(index);
    }
    return fibonacci_power2n(index - 1) + fibonacci_power2n(index - 2);
}

/*A O(n) Algorithm*/
static unsigned long long fibonacci_n_core(unsigned int index, unsigned long long &prevFib)
{
    if (index == 0) {
        prevFib = 1;
        return unsigned long long(index);
    }
    unsigned long long prevPrevFib = 0;
    prevFib  = fibonacci_n_core(index - 1, prevPrevFib);
    return prevFib + prevPrevFib;
}

static unsigned long long fibonacci_n(unsigned int index)
{
    unsigned long long prevFib = 0;
    return fibonacci_n_core(index, prevFib);
}


/*Another O(n) Algorithm*/
static unsigned long long fibonacci_n2(unsigned int index)
{
    if (index <= 1) {
        return unsigned long long(index);
    }
    unsigned long long fib0 = 0, fib1 = 1, fibn = 0;
    
    for (unsigned int i = 2; i <= index; i++) {
        fibn = fib1 + fib0;
        fib0 = fib1; fib1 = fibn;
    }
    return fibn;
}

/*A O(logn) Algorithm*/
static void matrixMultiply(const unsigned long long inputMatrix1[2][2], const unsigned long long inputMatrix2[2][2],
                           unsigned long long outputMatrix[2][2])
{
    unsigned long long tmpMatrix[2][2] =
    {
        {
            inputMatrix1[0][0] * inputMatrix2[0][0] + inputMatrix1[0][1] * inputMatrix2[1][0],
            inputMatrix1[0][0] * inputMatrix2[0][1] + inputMatrix1[0][1] * inputMatrix2[1][1],
        },
        {
            inputMatrix1[1][0] * inputMatrix2[0][0] + inputMatrix1[1][1] * inputMatrix2[1][0],
            inputMatrix1[1][0] * inputMatrix2[0][1] + inputMatrix1[1][1] * inputMatrix2[1][1],
        }
    };

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            outputMatrix[i][j] = tmpMatrix[i][j];
        }
    }
}

static unsigned long long fibonacci_logn(unsigned int index)
{
    if (index <= 1) {
        return unsigned long long(index);
    }
    unsigned long long resultMatrix[2][2] = { {1, 0},{0, 1} };
    unsigned long long assistMatrix[2][2] = { {0, 1},{1, 1} };

    while (index > 0) {
        if (index & 1) {
            matrixMultiply(resultMatrix, assistMatrix, resultMatrix);
        }
        matrixMultiply(assistMatrix, assistMatrix, assistMatrix);
        index >>= 1;
    }
    return resultMatrix[0][1];
}


static void OneUnitTesting(unsigned int index, unsigned long long fibonacciNumber, 
                           const char *funcName, const funcPtr testFunction)
{
    auto start = std::chrono::system_clock::now();

    auto result = testFunction(index);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = end - start;

    if (result == fibonacciNumber) {
        std::cout << "function[" << funcName << "\t]: \t|CORRECT|\t|input = "
            << index << "\toutput = " << result << "|\t" << elapsedSeconds.count() * 1000 << "ms.\n";
    }
    else {
        std::cout << "function[" << funcName << "\t]: \t|WRONG  |\t|input = "
            << index << "\toutput = " << result << "|\t" << elapsedSeconds.count() * 1000 << "ms.\n";
    }
}

void FibonacciUnitTesting()
{
    unsigned long long testArray[][2] = { {0, 0}, {1, 1}, {2,1},{3,2}, {13,233}, {53,53316291173}, 
                                          {45,1134903170}, {34, 5702887}, {22, 17711}, {64, 10610209857723} };

    for (int i = 0; i < sizeof(testArray) / sizeof(testArray[0]); i++) {

        OneUnitTesting(unsigned int(testArray[i][0]), testArray[i][1], "fibonacci_n", fibonacci_n);

        OneUnitTesting(unsigned int(testArray[i][0]), testArray[i][1], "fibonacci_n2", fibonacci_n2);

        OneUnitTesting(unsigned int(testArray[i][0]), testArray[i][1], "fibonacci_logn", fibonacci_logn);

        //OneUnitTesting(unsigned int(testArray[i][0]), testArray[i][1], "fibonacci_power2n", fibonacci_power2n);

        std::cout << std::endl;

    }
}