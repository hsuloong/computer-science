/*
This file is a practice for Deng Junhui's book: "data structure[ISBN:9787302330646]"

Question:
Calculate ackermann function.
                  |---n+1 when m = 0
Ackermann(m,n) =  |---Ackermann(m-1, 1) when m > 0 and n = 0;
                  |---Ackermann(m-1, Ackermann(m, n-1)) when m > 0 and n > 0;
*/
#include <iostream>
#include <chrono>

typedef unsigned long long(*funcPtr)(unsigned long long, unsigned long long);


static unsigned long long ackermann(unsigned long long m, unsigned long long n)
{
    if (m == 0) {
        return n + 1;
    }
    if (m > 0 && n == 0) {
        return ackermann(m - 1, 1);
    }
    if (m > 0 && n > 0) {
        return ackermann(m - 1, ackermann(m, n - 1));
    }
    return 0;
}

static void OneUnitTesting(const unsigned long long oneTestArray[3], const char *funcName, const funcPtr testFunction)
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


void AckermannUnitTesting()
{
    unsigned long long testArray[][3] = { {0, 0, 1}, {0, 1, 2}, {1, 1, 3}, {1, 2, 4},{2, 2, 7},
                                          {2, 3, 9}, {2, 4, 11}, {3, 4, 125}, {3, 5, 253}, {2, 8, 19},
                                          {2,1000, 2003} };

    for (int i = 0; i < sizeof(testArray) / sizeof(testArray[0]); i++) {

        OneUnitTesting(testArray[i], "ackermann", ackermann);

        std::cout << std::endl;

    }
}