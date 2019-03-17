/*
This file is a practice for Deng Junhui's book: "data structure[ISBN:9787302330646]"

Question:
Shift an array[0....n-1] to left for k times.
*/
#include <iostream>
#include <chrono>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm>

typedef void(*funcPtr)(std::vector<int>&, unsigned int);

/*A O(n) Algorithm*/
void shiftLeft_n_core(std::vector<int>& inputArray, size_t start, size_t end)
{
    if (start + 1 >= end) {
        return;
    }
    while (start + 1 < end) {
        std::swap(inputArray[start], inputArray[end - 1]);
        ++start; --end;
    }
}

void shiftLeft_n(std::vector<int>& inputArray, unsigned int k)
{
    if (inputArray.size() <= 1 || k % inputArray.size() == 0) {
        return;
    }
    k %= inputArray.size();
    shiftLeft_n_core(inputArray, 0, inputArray.size());
    shiftLeft_n_core(inputArray, 0, inputArray.size()-k);
    shiftLeft_n_core(inputArray, inputArray.size() - k, inputArray.size());
}


/*Another O(n) Algorithm*/
void shiftLeft_n2(std::vector<int>& inputArray, unsigned int k)
{
    if (inputArray.size() <= 1 || k % inputArray.size() == 0) {
        return;
    }
    k %= inputArray.size();
    shiftLeft_n_core(inputArray, 0, k);
    shiftLeft_n_core(inputArray, k, inputArray.size());
    shiftLeft_n_core(inputArray, 0, inputArray.size());
}

static void OneUnitTesting(std::vector<int> oneTestArray, const std::vector<int> &oneResultArray, unsigned int k,
                           const char *funcName, const funcPtr testFunction)
{
    auto start = std::chrono::system_clock::now();

    testFunction(oneTestArray, k);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = end - start;

    if (oneTestArray == oneResultArray) {
        std::cout << "function[" << funcName << "\t]: \t|CORRECT|\t"
            << elapsedSeconds.count() * 1000 << "ms.\n";
    }
    else {
        std::cout << "function[" << funcName << "\t]: \t|WRONG  |\t"
            << elapsedSeconds.count() * 1000 << "ms.\n";
    }
}

void ShiftLeftUnitTesting()
{
    std::vector<std::vector<int>> testArray(10);
    std::vector<std::vector<int>> resultArray(10);
    std::vector<unsigned int> kArray(10, 0);

    std::default_random_engine randEngine(unsigned(time(nullptr)));
    std::uniform_int_distribution<int> valueDistribution(int(-10e6), int(10e6));
    std::uniform_int_distribution<int> sizeDistribution(int(1), int(100));

    /*Generate random array*/
    for (size_t i = 0; i < testArray.size(); i++) {
        int tmpArraySize = sizeDistribution(randEngine);
        for (int j = 0; j < tmpArraySize; j++) {
            testArray[i].push_back(valueDistribution(randEngine));
        }
        kArray[i] = unsigned int(sizeDistribution(randEngine));
        auto index = kArray[i] % testArray[i].size();
        resultArray[i].assign(testArray[i].begin() + index, testArray[i].end());
        resultArray[i].insert(resultArray[i].end(), testArray[i].begin(), testArray[i].begin() + index);
    }

    for (size_t i = 0; i < testArray.size(); i++) {

        OneUnitTesting(testArray[i], resultArray[i], kArray[i], "shiftLeft_n", shiftLeft_n);

        OneUnitTesting(testArray[i], resultArray[i], kArray[i], "shiftLeft_n2", shiftLeft_n2);

        std::cout << std::endl;

    }
}