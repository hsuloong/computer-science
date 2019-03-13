/*
This file is a practice for Deng Junhui's book: "data structure[ISBN:9787302330646]"

Question:
Give a number n(>=0), calculate 2^n.
*/
#include <iostream>
#include <chrono>
#include <stack>

typedef unsigned long long(*funcPtr)(unsigned int);

/*A O(n) or O(2^r, r=log2(n)) Algorithm*/
static unsigned long long power2_n(unsigned int number)
{
    unsigned long long result = 1;
    while (number-- > 0) {
        result <<= 1;
    }
    return result;
}


/*Another O(n) or O(2^r, r=log2(n)) Algorithm*/
static unsigned long long power2_n2(unsigned int number)
{
    if (number == 0) {
        return 1;
    }
    return power2_n(number - 1) << 1;
}


/*A O(logn) Algorithm*/
static unsigned long long power2_logn(unsigned int number)
{
    if (number <= 0) {
        return 1;
    }
    auto result = power2_logn(number >> 1);
    if (number & 1) {
        return (result * result) << 1;
    }
    else {
        return result * result;
    }
}

/*Another O(logn) Algorithm*/
static unsigned long long power2_logn2(unsigned int number)
{
    unsigned long long result = 1;

    std::stack<unsigned int> assistantStack;
    while (number > 0) {
        assistantStack.push(number & 1); number >>= 1;
    }

    while (!assistantStack.empty()) {
        if (assistantStack.top() == 1) {
            result *= (result << 1);
        }
        else {
            result *= result;
        }
        assistantStack.pop();
    }
    return result;
}

/*Another O(logn) Algorithm*/
static unsigned long long power2_logn3(unsigned int number)
{
    unsigned long long result = 1;
    unsigned long long accumulator = 2;
    while (number > 0) {
        if (number & 1) {
            result *= accumulator;
        }
        number >>= 1;
        accumulator *= accumulator;
    }
    return result;
}


static void OneUnitTesting(const unsigned long long oneTestArray[2], const char *funcName, const funcPtr testFunction)
{
    auto start = std::chrono::system_clock::now();

    auto result = testFunction(unsigned int(oneTestArray[0]));

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = end - start;

    if (result == oneTestArray[1]) {
        std::cout << "function[" << funcName << "\t]: \t|CORRECT|\t|input = "
            << oneTestArray[0] << "\toutput = " << result << "|\t" << elapsedSeconds.count() * 1000 << "ms.\n";
    }
    else {
        std::cout << "function[" << funcName << "\t]: \t|WRONG  |\t|input = "
            << oneTestArray[0] << "\toutput = " << result << "|\t" << elapsedSeconds.count() * 1000 << "ms.\n";
    }
}

void Power2UnitTesting()
{
    unsigned long long testArray[][2] = { {8, 256}, {13, 8192}, {34, 17179869184},{41, 2199023255552}, {0, 1},
                                          {63, 9223372036854775808}, {25, 33554432}, {57,144115188075855872} };
    for (int i = 0; i < sizeof(testArray) / sizeof(testArray[0]); i++) {

        OneUnitTesting(testArray[i], "power2_n", power2_n);

        OneUnitTesting(testArray[i], "power2_n2", power2_n2);

        OneUnitTesting(testArray[i], "power2_logn", power2_logn);

        OneUnitTesting(testArray[i], "power2_logn2", power2_logn2);

        OneUnitTesting(testArray[i], "power2_logn3", power2_logn3);

        std::cout << std::endl;

    }
}