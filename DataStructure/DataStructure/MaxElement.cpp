/*
This file is a practice for Deng Junhui's book: "data structure"

Question:
Find max element from an array with size n.
*/
#include <iostream>
#include <chrono>
#include <vector>
#include <ctime>
#include <algorithm>
#include <random>

typedef int(*funcPtr)(const std::vector<int> &);

/*A O(n) Algorithm*/
static int maxElement_n(const std::vector<int> &inputArray)
{
    if (inputArray.size() <= 0) {
        return -1;
    }
    int result = inputArray[0];
    for (size_t i = 0; i < inputArray.size(); i++) {
        result = inputArray[i] > result ? inputArray[i] : result;
    }
    return result;
}


static void OneUnitTesting(const std::vector<int> &oneTestArray, int maxElement, 
                           const char *funcName, const funcPtr testFunction)
{
    auto start = std::chrono::system_clock::now();

    auto result = testFunction(oneTestArray);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = end - start;

    if (result == maxElement) {
        std::cout << "function[" << funcName << "\t]: \t|CORRECT|\t"
                  << elapsedSeconds.count() * 1000 << "ms.\n";
    }
    else {
        std::cout << "function[" << funcName << "\t]: \t|WRONG  |\t"
                  << elapsedSeconds.count() * 1000 << "ms.\n";
    }
}

void MaxElementUnitTesting()
{
    std::vector<std::vector<int>> testArray(10);
    std::vector<int> maxElements(10, 0);

    std::default_random_engine randEngine(unsigned(time(nullptr)));
    std::uniform_int_distribution<int> valueDistribution(int(-10e6), int(10e6));
    std::uniform_int_distribution<int> sizeDistribution(int(1), int(1000));

    /*Generate random array*/
    for (size_t i = 0; i < testArray.size(); i++) {
        int tmpArraySize = sizeDistribution(randEngine);
        for (int j = 0; j < tmpArraySize; j++) {
            testArray[i].push_back(valueDistribution(randEngine));
        }
        maxElements[i] = *std::max_element(testArray[i].begin(), testArray[i].end());
    }
    
    for (size_t i = 0; i < testArray.size(); i++) {

        OneUnitTesting(testArray[i], maxElements[i], "maxElement_n", maxElement_n);

        std::cout << std::endl;

    }
}

