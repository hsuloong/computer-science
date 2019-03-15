/*
This file is a practice for Deng Junhui's book: "data structure[ISBN:9787302330646]"

Question:
Solve the problem: tower of hanoi.
*/
#include <iostream>
#include <chrono>

typedef unsigned int(*funcPtr)(unsigned int);


/*A O(2^n) Algorithm*/
static void hanoiTower_power2n_core(unsigned int number, char src, char assist, char dst, unsigned int &steps)
{
    if (number > 0) {
        hanoiTower_power2n_core(number - 1, src, dst, assist, steps);
        ++steps;
        hanoiTower_power2n_core(number - 1, assist, src, dst, steps);
    }
}

static unsigned int hanoiTower_power2n(unsigned int number)
{
    unsigned int steps = 0;
    hanoiTower_power2n_core(number, 'X', 'Z', 'Y', steps);
    return steps;
}


static void OneUnitTesting(const unsigned int oneTestArray[2], const char *funcName, const funcPtr testFunction)
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

void HanoiTowerUnitTesting()
{
    unsigned int testArray[][2] = { {0, 0}, {1, 1}, {2, 3},{9, 511},
                                    {17, 131071}, {10, 1023}, {28, 268435455}};
    for (int i = 0; i < sizeof(testArray) / sizeof(testArray[0]); i++) {

        OneUnitTesting(testArray[i], "hanoiTower_power2n", hanoiTower_power2n);

        std::cout << std::endl;

    }
}
