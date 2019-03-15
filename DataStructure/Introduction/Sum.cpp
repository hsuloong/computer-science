/*
This file is a practice for Deng Junhui's book: "data structure[ISBN:9787302330646]"

Question:
Calculate elements sum of an array.
*/
#include <iostream>
#include <chrono>
#include <vector>
#include <ctime>
#include <numeric>
#include <random>

typedef int(*funcPtr)(const std::vector<int> &);

/*A O(n) Algorithm*/
static int sum_n(const std::vector<int> &inputArray)
{
    int result = 0;
    for (size_t i = 0; i < inputArray.size(); i++) {
        result += inputArray[i];
    }
    return result;
}

/*Another O(n) Algorithm*/
static int sum_n2_core(const std::vector<int> &inputArray, size_t index)
{
    if (index >= inputArray.size()) {
        return 0;
    }
    return inputArray[index] + sum_n2_core(inputArray, index + 1);
}

static int sum_n2(const std::vector<int> &inputArray)
{
    return sum_n2_core(inputArray, 0);
}

/*Another O(n) Algorithm*/
static int sum_n3_core(const std::vector<int> &inputArray, size_t start, size_t end)
{
    if (start + 1 >= end) {
        return inputArray[start];
    }
    size_t middle = start + (end - start) / 2;
    int sumLeft = sum_n3_core(inputArray, start, middle);
    int sumRight = sum_n3_core(inputArray, middle, end);
    return sumLeft + sumRight;
}

static int sum_n3(const std::vector<int> &inputArray)
{
    return sum_n3_core(inputArray, 0, inputArray.size());
}


static void OneUnitTesting(const std::vector<int> &oneTestArray, int arraySum,
                           const char *funcName, const funcPtr testFunction)
{
    auto start = std::chrono::system_clock::now();

    auto result = testFunction(oneTestArray);

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = end - start;

    if (result == arraySum) {
        std::cout << "function[" << funcName << "]: \t|CORRECT|\t"
            << elapsedSeconds.count() * 1000 << "ms.\n";
    }
    else {
        std::cout << "function[" << funcName << "]: \t|WRONG  |\t"
            << elapsedSeconds.count() * 1000 << "ms.\n";
    }
}

void SumUnitTesting()
{
    std::vector<std::vector<int>> testArray(10);
    std::vector<int> sumElements(10, 0);

    std::default_random_engine randEngine(unsigned(time(nullptr)));
    std::uniform_int_distribution<int> valueDistribution(int(-10e6), int(10e6));
    std::uniform_int_distribution<int> sizeDistribution(int(1), int(100));

    /*Generate random array*/
    for (size_t i = 0; i < testArray.size(); i++) {
        int tmpArraySize = sizeDistribution(randEngine);
        for (int j = 0; j < tmpArraySize; j++) {
            testArray[i].push_back(valueDistribution(randEngine));
        }
        sumElements[i] = std::accumulate(testArray[i].begin(), testArray[i].end(), 0);
    }

    for (size_t i = 0; i < testArray.size(); i++) {

        OneUnitTesting(testArray[i], sumElements[i], "sum_n", sum_n);

        OneUnitTesting(testArray[i], sumElements[i], "sum_n2", sum_n2);

        OneUnitTesting(testArray[i], sumElements[i], "sum_n3", sum_n3);


        std::cout << std::endl;

    }
}