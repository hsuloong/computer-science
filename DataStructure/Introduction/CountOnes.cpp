/*
This file is a practice for Deng Junhui's book: "data structure[ISBN:9787302330646]"

Question:
Count number of 1s in binary representation of an integer.
*/
#include <iostream>
#include <chrono>

typedef unsigned int(*funcPtr)(unsigned int);

/*A O(logn) Algorithm, n=bits number of the integer*/
static unsigned int counterOnes_logn(unsigned int number)
{
    unsigned int counter = 0;
    while (number > 0) {
        if (number & 1) {
            ++counter;
        }
        number >>= 1;
    }
    return counter;
}

/*Another O(logn) Algorithm, n=bits number of the integer*/
static unsigned int counterOnes_logn2(unsigned int number)
{
    unsigned int counter = 0;
    while (number > 0) {
        counter += (number & 1);
        number >>= 1;
    }
    return counter;
}

/*A O(r) Algorithm, r=actually 1s of the integer*/
static unsigned int counterOnes_logr(unsigned int number)
{
    unsigned int counter = 0;

    while (number > 0) {
        ++counter;
        number &= (number - 1);
    }
    return counter;
}

/*Another O(r) Algorithm, r=actually 1s of the integer*/
static unsigned int counterOnes_logr2(unsigned int number)
{
    unsigned int counter = 0;
    long long longNumer = (long long)number;
    while (longNumer > 0) {
        ++counter;
        longNumer -= (longNumer & -longNumer);
    }
    return counter;
}

/*A O(log2(w)) Algorithm, w=bits number of the integer, assume 32bit*/
#define POW(c) (1 << (c))
/*
MASK(0) = 0x55555555
MASK(1) = 0x33333333
MASK(2) = 0x0f0f0f0f
MASK(3) = 0x00ff00ff
MASK(4) = 0x0000ffff
*/
#define MASK(c) (((unsigned long)-1)/(POW(POW(c))+1))
#define ROUND(n,c) (((n) & MASK(c))+((n) >> POW(c) & MASK(c)))
static unsigned int counterOnes_log2w(unsigned int number)
{
    number = ROUND(number, 0);
    number = ROUND(number, 1);
    number = ROUND(number, 2);
    number = ROUND(number, 3);
    number = ROUND(number, 4);
    return number;
}
#undef ROUND
#undef MASK
#undef POW

/*modify counterOnes_log2w, assume 32bit*/
static unsigned int counterOnes_log2w2(unsigned int number)
{
    number = (number & 0x55555555) + ((number >> 1) & 0x55555555);
    number = (number & 0x33333333) + ((number >> 2) & 0x33333333);
    number = (number & 0x0f0f0f0f) + ((number >> 4) & 0x0f0f0f0f);
    number = (number & 0x00ff00ff) + ((number >> 8) & 0x00ff00ff);
    number = (number & 0x0000ffff) + ((number >> 16) & 0x0000ffff);
    return number;
}


static void OneUnitTesting(const unsigned int oneTestArray[2], const char *funcName,const funcPtr testFunction)
{
    auto start = std::chrono::system_clock::now();

    auto result = testFunction(oneTestArray[0]);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = end - start;

    if (result == oneTestArray[1]) {
        std::cout << "function[" << funcName << "]: \t|CORRECT|\t|input = "
            << oneTestArray[0] << "\toutput = " << result << "|\t" << elapsedSeconds.count() * 1000 << "ms.\n";
    }
    else {
        std::cout << "function[" << funcName << "]: \t|WRONG  |\t|input = "
            << oneTestArray[0] << "\toutput = " << result << "|\t" << elapsedSeconds.count() * 1000 << "ms.\n";
    }
}


void CountOnesUnitTesting()
{
    unsigned int testArray[][2] = { {0, 0}, {0x01, 1}, {0x03,2},{0x07,3},
                                    {0x0F,4}, {0x1F,5}, {0x3F,6}, {0x7F, 7}, {0xFF, 8} };
    for (int i = 0; i < sizeof(testArray) / sizeof(testArray[0]); i++) {

        OneUnitTesting(testArray[i], "counterOnes_logn", counterOnes_logn);

        OneUnitTesting(testArray[i], "counterOnes_logn2", counterOnes_logn2);

        OneUnitTesting(testArray[i], "counterOnes_logr", counterOnes_logr);

        OneUnitTesting(testArray[i], "counterOnes_logr2", counterOnes_logr2);

        OneUnitTesting(testArray[i], "counterOnes_log2w", counterOnes_log2w);

        OneUnitTesting(testArray[i], "counterOnes_log2w2", counterOnes_log2w2);

        std::cout << std::endl;

    }
}
