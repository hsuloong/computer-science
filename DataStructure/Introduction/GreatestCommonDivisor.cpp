/*
This file is a practice for Deng Junhui's book: "data structure[ISBN:9787302330646]"

Question:
Calculate the greatest common divisor of two integer .
*/
#include <iostream>
#include <chrono>
#include <algorithm>

typedef unsigned int(*funcPtr)(unsigned int, unsigned int);

/*A O(n) Algorithm, n = min(number1,number2)*/
static unsigned int greatestCommonDivisor_n(unsigned int number1, unsigned int number2)
{
    if (number1 > number2) {
        std::swap(number1, number2);
    }
    for (unsigned int i = number1; i > 0; --i) {
        if ((number2 % i == 0) && (number1 % i == 0)) {
            return i;
        }
    }
    return 1;
}

/*A O(logn) Algorithm, n = number1+number2*/
/*
number1 = n*a,
number2 = m*a,  a is greatest common divisor.
*/
static unsigned int greatestCommonDivisor_logn(unsigned int number1, unsigned int number2)
{
    unsigned int p = 1;

    while (!(number1 & 1) && !(number2 & 1)) {
        p *= 2; number1 /= 2; number2 /= 2;
    }

    while (true) {
        unsigned int t = number1 > number2 ? number1 - number2 : number2 - number1;
        if (t == 0) {
            return number1 * p;
        }

        while (!(t & 1)) {
            t /= 2;
        }
        
        number1 >= number2 ? number1 = t : number2 = t;
    }
    return 1;
}

/*Another O(logn) Algorithm, Euclidean algorithm*/
static unsigned int greatestCommonDivisor_logn2(unsigned int number1, unsigned int number2)
{
    unsigned int remainder = 1;
    while (number2 > 0) {
        remainder = number1 % number2;
        number1 = number2;
        number2 = remainder;
    }
    return number1;
}


static void OneUnitTesting(const unsigned int oneTestArray[3], const char *funcName, const funcPtr testFunction)
{
    auto start = std::chrono::system_clock::now();

    auto result = testFunction(oneTestArray[0], oneTestArray[1]);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = end - start;

    if (result == oneTestArray[2]) {
        std::cout << "function[" << funcName << "]: \t|CORRECT|\t|input = (" << oneTestArray[0] << ", "
                  << oneTestArray[1] << ")\toutput = " << result << "|\t" << elapsedSeconds.count() * 1000 << "ms.\n";
    }
    else {
        std::cout << "function[" << funcName << "]: \t|WRONG  |\t|input = (" << oneTestArray[0] << ", "
                  << oneTestArray[1] << ")\toutput = " << result << "|\t" << elapsedSeconds.count() * 1000 << "ms.\n";
    }
}


void GreatestCommonDivisorUnitTesting()
{
    unsigned int testArray[][3] = { {15107, 66074, 1}, {35562, 88928, 2}, {62853, 4555, 1},{25, 5, 5},
                                    {124, 124, 124}, {10248, 1024, 8}, {96, 69, 3}, {1, 1000000, 1} };

    for (int i = 0; i < sizeof(testArray) / sizeof(testArray[0]); i++) {

        OneUnitTesting(testArray[i], "greatestCommonDivisor_n", greatestCommonDivisor_n);

        OneUnitTesting(testArray[i], "greatestCommonDivisor_logn", greatestCommonDivisor_logn);

        OneUnitTesting(testArray[i], "greatestCommonDivisor_logn2", greatestCommonDivisor_logn2);

        std::cout << std::endl;

    }
}