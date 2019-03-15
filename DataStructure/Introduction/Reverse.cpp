/*
This file is a practice for Deng Junhui's book: "data structure[ISBN:9787302330646]"

Question:
reverse an array.
*/
#include <iostream>
#include <chrono>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm>

typedef void(*funcPtr)(std::vector<int> &);

/*A O(n) Algorithm*/
void reverse_n_core(std::vector<int> &inputArray, size_t low, size_t high)
{
    if (low + 1 >= high) {
        return;
    }
    std::swap(inputArray[low], inputArray[high-1]);
    reverse_n_core(inputArray, low + 1, high - 1);
}

static void reverse_n(std::vector<int> &inputArray)
{
    if (inputArray.size() > 0) {
        reverse_n_core(inputArray, 0, inputArray.size());
    }
}


/*Another O(n) Algorithm*/
static void reverse_n2(std::vector<int> &inputArray)
{
    if (inputArray.size() > 0) {
        size_t low = 0, high = inputArray.size()-1;
        while (low < high) {
            std::swap(inputArray[low++], inputArray[high--]);
        }
    }
}


static void OneUnitTesting(std::vector<int> oneTestArray, const std::vector<int> &oneResultArray,
                           const char *funcName, const funcPtr testFunction)
{
    auto start = std::chrono::system_clock::now();

    testFunction(oneTestArray);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = end - start;

    if (oneTestArray == oneResultArray) {
        std::cout << "function[" << funcName << "]: \t|CORRECT|\t"
            << elapsedSeconds.count() * 1000 << "ms.\n";
    }
    else {
        std::cout << "function[" << funcName << "]: \t|WRONG  |\t"
            << elapsedSeconds.count() * 1000 << "ms.\n";
    }
}

void ReverseUnitTesting()
{
    std::vector<std::vector<int>> testArray(10);
    std::vector<std::vector<int>> resultArray(10);

    std::default_random_engine randEngine(unsigned(time(nullptr)));
    std::uniform_int_distribution<int> valueDistribution(int(-10e6), int(10e6));
    std::uniform_int_distribution<int> sizeDistribution(int(1), int(100));

    /*Generate random array*/
    for (size_t i = 0; i < testArray.size(); i++) {
        int tmpArraySize = sizeDistribution(randEngine);
        for (int j = 0; j < tmpArraySize; j++) {
            testArray[i].push_back(valueDistribution(randEngine));
            resultArray[i].insert(resultArray[i].begin(), testArray[i][j]);
        }
    }

    for (size_t i = 0; i < testArray.size(); i++) {

        OneUnitTesting(testArray[i], resultArray[i], "reverse_n", reverse_n);

        OneUnitTesting(testArray[i], resultArray[i], "reverse_n2", reverse_n2);

        std::cout << std::endl;

    }
}

