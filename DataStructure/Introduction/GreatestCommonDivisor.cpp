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
    return 0;
}

/*A O(logn) Algorithm, n = number1+number2*/
/*
number1 = n*a,
number2 = m*a,  a is greatest common divisor.
number1-number2 = (n-m)*a, assume number1 >= number2
if a is not number1-number2 and  number2 greatest common divisor
then assume n-m = k*d, m = x*d,(d > 1)
which can get n = (k+x)*d=>number1=(k+x)*d*a, number2=x*d*a, get a paradox.
*/
static unsigned int greatestCommonDivisor_logn(unsigned int number1, unsigned int number2)
{
    unsigned int product = 1;
    while (!(number1 & 1) && !(number2 & 1)) {
        product <<= 1; number1 >>= 1; number2 >>= 1;
    }
    while (true) {
        unsigned int diff = number1 > number2 ? number1 - number2 : number2 - number1;
        if (diff == 0) {
            return number1 * product;
        }

        while (!(diff & 1)) {
            diff >>= 1;
        }
        number1 >= number2 ? number1 = diff : number2 = diff;
    }
    return 0;
}

/*Another O(logn) Algorithm, Euclidean algorithm*/
/*
greatestCommonDivisor(a,b) = greatestCommonDivisor(b,a mod b)
*/
static unsigned int greatestCommonDivisor_logn2(unsigned int number1, unsigned int number2)
{
    unsigned int remainder = 0;
    while (number2 > 0) {
        remainder = number1 % number2;
        number1 = number2;
        number2 = remainder;
    }
    return number1;
}

/*Another O(logn) Algorithm, Euclidean algorithm*/
/*
greatestCommonDivisor(a,b) = greatestCommonDivisor(b,a mod b)
*/
static unsigned int greatestCommonDivisor_logn3(unsigned int number1, unsigned int number2)
{
    if (number2 == 0) {
        return number1;
    }
    return greatestCommonDivisor_logn3(number2, number1 % number2);
}

/*Another O(logn) Algorithm, Stein algorithm*/
/*
Same as greatestCommonDivisor_logn
*/
static unsigned int greatestCommonDivisor_logn4(unsigned int number1, unsigned int number2)
{
    if (number1 == 0) {
        return number2;
    }
    if (number2 == 0) {
        return number1;
    }
    if (number1 % 2 == 0 && number2 % 2 == 0) {
        return 2 * greatestCommonDivisor_logn4(number1 >> 1, number2 >> 1);
    }
    else if (number1 % 2 == 0) {
        return greatestCommonDivisor_logn4(number1 >> 1, number2 );
    }
    else if (number2 % 2 == 0) {
        return greatestCommonDivisor_logn4(number1, number2 >> 1);
    }
    else {
        if (number1 > number2) {
            std::swap(number1, number2);
        }
        return greatestCommonDivisor_logn4(number2 - number1, number1);
    }
}

/*Another O(logn) Algorithm*/
/*
Same as greatestCommonDivisor_logn
*/
static unsigned int greatestCommonDivisor_logn5(unsigned int number1, unsigned int number2)
{
    unsigned int r = 0;
    while (number1 % 2 == 0 && number2 % 2 == 0) {
        number1 >>= 1; number2 >>= 1; ++r;
    }
    while (true) {
        while (number1 % 2 == 0) {
            number1 >>= 1;
        }
        while (number2 % 2 == 0) {
            number2 >>= 1;
        }
        number1 > number2 ? number1 = number1 - number2 : number2 = number2 - number1;
        if (number1 == 0) {
            return number2 << r;
        }
        if (number2 == 0) {
            return number1 << r;
        }
    }
    return 0;
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

        OneUnitTesting(testArray[i], "greatestCommonDivisor_logn3", greatestCommonDivisor_logn3);

        OneUnitTesting(testArray[i], "greatestCommonDivisor_logn4", greatestCommonDivisor_logn4);

        OneUnitTesting(testArray[i], "greatestCommonDivisor_logn5", greatestCommonDivisor_logn5);

        std::cout << std::endl;

    }
}