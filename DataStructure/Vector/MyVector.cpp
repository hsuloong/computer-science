#include "MyVector.h"

#include <iostream>
#include <chrono>
#include <vector>
#include <ctime>
#include <numeric>
#include <random>

/*
Test Interface:
    MyVector(int capacity = DEFAULT_CAPACITY, int size = 0, T value = 0);
    MyVector(T const *inputArray, int start, int end);
    MyVector(T const *inputArray, int end);
    MyVector(MyVector<T> const& inputMyVector, int start, int end);
    MyVector(MyVector<T> const& inputMyVector);
    int size() const;
    bool empty() const;
    int disordered() const;
    int find(T const &elem) const;
    int find(T const &elem, int start, int end) const;
    int search(T const &elem) const;
    int search(T const &elem, int start, int end) const;
    T& operator[](int index) const;
    MyVector<T> & operator=(MyVector<T> const& inputMyVector);
    T remove(int index);
    int remove(int start, int end);
    int insert(int position, T const& elem);
    int insert(T const& elem);
    void sort(int start, int end);
    void sort();
    void unsort(int start, int end);
    void unsort();
    int deduplicate();
    int uniquify();
    void traverse(void(*visit)(T&));
    template<typename VST> void traverse(VST&visit);
*/

static void OneUnitTesting(const MyVector<int> &oneTestArray, const std::vector<int> &oneResultArray,
                           const char *funcName)
{
    bool correct = true;

    if (oneTestArray.size() != oneResultArray.size()) {
        correct = false;
    }

    if (oneTestArray.empty() != oneResultArray.empty()) {
        correct = false;
    }

    for (int i = 0; i < oneTestArray.size(); i++) {
        if (oneTestArray[i] != oneResultArray[i]) {
            correct = false; break;
        }
    }

    if (correct) {
        std::cout << "function[" << funcName << "\t]: \t\t|CORRECT|\n";
    }
    else {
        std::cout << "function[" << funcName << "\t]: \t\t|WRONG  |\n";
    }
}

static void OneUnitTesting(const MyVector<int> &oneTestArray, bool isOrdered, const char *funcName)
{
    bool correct = ((oneTestArray.disordered() <= 0) == isOrdered);

    if (correct) {
        std::cout << "function[" << funcName << "\t]: \t\t|CORRECT|\n";
    }
    else {
        std::cout << "function[" << funcName << "\t]: \t\t|WRONG  |\n";
    }
}

static void visit(int & item)
{
    item += 2;
}

struct functor
{
    void operator()(int &item) {
        item += 2;
    }
};

void MyVectorUnitTesting()
{
    const int testTimes = 10;

    std::default_random_engine randEngine(unsigned(time(nullptr)));
    std::uniform_int_distribution<int> capacityDistribution(int(3), int(10e3));
    std::uniform_int_distribution<int> sizeDistribution(int(1), int(10e3));
    std::uniform_int_distribution<int> valueDistribution(int(-10e6), int(10e6));

    /*Generate random array*/
    for (size_t i = 0; i < testTimes; i++) {
        int randomCapacity = capacityDistribution(randEngine);
        int randomSize = sizeDistribution(randEngine) % randomCapacity + 1;
        int randomValue = valueDistribution(randEngine);

        MyVector<int> testMyVector1(randomCapacity, randomSize, randomValue);
        std::vector<int> testVector1(randomSize, randomValue);
        OneUnitTesting(testMyVector1, testVector1, "MyVector(int,int,T)      ");

        int *randomArray = new int[randomSize];
        for (int j = 0; j < randomSize; j++) {
            randomArray[j] = valueDistribution(randEngine);
        }
        MyVector<int> testMyVector2(randomArray, randomSize);
        std::vector<int> testVector2(randomArray, randomArray+ randomSize);
        OneUnitTesting(testMyVector2, testVector2, "MyVector(T*,int)         ");

        int randomEnd = sizeDistribution(randEngine) % randomSize + 1;
        MyVector<int> testMyVector3(randomArray, 0, randomEnd);
        std::vector<int> testVector3(randomArray, randomArray + randomEnd);
        OneUnitTesting(testMyVector3, testVector3, "MyVector(T*,int,int)     ");

        MyVector<int> testMyVector4(testMyVector2, 0, randomEnd);
        std::vector<int> testVector4(testVector2.begin(), testVector2.begin() + randomEnd);
        OneUnitTesting(testMyVector4, testVector4, "MyVector(MyVector&,int,int)");

        MyVector<int> testMyVector5(testMyVector3);
        std::vector<int> testVector5(testVector3);
        OneUnitTesting(testMyVector5, testVector5, "MyVector(MyVector&)        ");

        testMyVector1.sort();
        std::sort(testVector1.begin(), testVector1.end());
        OneUnitTesting(testMyVector1, testVector1, "sort()                     ");

        testMyVector2.sort(0, testMyVector2.size());
        std::sort(testVector2.begin(), testVector2.end());
        OneUnitTesting(testMyVector2, testVector2, "sort()                     ");

        testMyVector3.unsort(); testMyVector3.sort();
        std::sort(testVector3.begin(), testVector3.end());
        OneUnitTesting(testMyVector3, testVector3, "sort()                     ");

        int randomSortEnd = sizeDistribution(randEngine) % testMyVector4.size() + 1;
        testMyVector4.sort(0, randomSortEnd);
        std::sort(testVector4.begin(), testVector4.begin() + randomSortEnd);
        OneUnitTesting(testMyVector4, testVector4, "sort(int,int)              ");

        int randomSortStart = sizeDistribution(randEngine) % testMyVector5.size();
        testMyVector5.sort(randomSortStart, testMyVector5.size());
        std::sort(testVector5.begin() + randomSortStart, testVector5.end());
        OneUnitTesting(testMyVector5, testVector5, "sort(int,int)              ");

        MyVector<int> testMyVector6; std::vector<int> testVector6;
        testMyVector6.insert(0); testVector6.insert(testVector6.end(), 0);
        int randomTimes = sizeDistribution(randEngine) + 1;
        for (int j = 0; j < randomTimes; j++) {
            int randomPosition = sizeDistribution(randEngine) % (testMyVector6.size() + 1);
            int randomValue = valueDistribution(randEngine);
            testMyVector6.insert(randomPosition, randomValue);
            testVector6.insert(testVector6.begin() + randomPosition, randomValue);
        }
        OneUnitTesting(testMyVector6, testVector6, "insert(int,T)              ");

        int randomRemoveTimes = sizeDistribution(randEngine) % (testMyVector6.size() + 1);
        for (int j = 0; j < randomRemoveTimes; j++) {
            int randomRemovePosition = sizeDistribution(randEngine) % testMyVector6.size();
            testMyVector6.remove(randomRemovePosition);
            testVector6.erase(testVector6.begin() + randomRemovePosition);
        }
        OneUnitTesting(testMyVector6, testVector6, "remove(int);              ");

        testMyVector6 = testMyVector5; testVector6 = testVector5;
        OneUnitTesting(testMyVector6, testVector6, "operator=(MyVector)       ");

        testMyVector6.traverse(visit); std::for_each(testVector6.begin(), testVector6.end(), visit);
        OneUnitTesting(testMyVector6, testVector6, "traverse(void(*)(T&))     ");

        MyVector<int> testMyVector7(randomArray, randomSize);
        std::vector<int> testVector7(randomArray, randomArray + randomSize);
        OneUnitTesting(testMyVector7, testVector7, "MyVector(T*,int)         ");
        for (int j = 0; j < randomSize; j++) {
            testMyVector7.insert(randomArray[i]);
            testVector7.push_back(randomArray[i]);
        }
        OneUnitTesting(testMyVector7, testVector7, "insert(int)              ");

        MyVector<int> testMyVector8 = testMyVector7;

        testMyVector7.sort(); testMyVector7.uniquify();
        std::sort(testVector7.begin(), testVector7.end());
        auto uniqueIter = std::unique(testVector7.begin(), testVector7.end());
        testVector7.erase(uniqueIter, testVector7.end());
        OneUnitTesting(testMyVector7, testVector7, "uniquify()               ");

        testMyVector8.deduplicate(); testMyVector8.sort();
        OneUnitTesting(testMyVector8, testVector7, "deduplicate()            ");

        MyVector<int> testMyVector9 = testMyVector8;
        std::vector<int> testVector9 = testVector7;
        int randomIndex = sizeDistribution(randEngine) % testMyVector9.size();
        testMyVector9.remove(0, testMyVector9.search(testMyVector9[randomIndex]));
        auto searchIter = std::lower_bound(testVector9.begin(), testVector9.end(), testVector9[randomIndex]);
        testVector9.erase(testVector9.begin(), searchIter);
        OneUnitTesting(testMyVector9, testVector9, "search(T)                ");

        MyVector<int> testMyVector10(randomArray, randomSize); testMyVector10.deduplicate();
        std::vector<int> testVector10;
        for (int j = 0; j < testMyVector10.size(); j++) {
            testVector10.push_back(testMyVector10[j]);
        }
        int randomIndex2 = sizeDistribution(randEngine) % testMyVector10.size();
        testMyVector10.remove(0, testMyVector10.find(testMyVector10[randomIndex]));
        auto findIter = std::find(testVector10.begin(), testVector10.end(), testVector10[randomIndex]);
        testVector10.erase(testVector10.begin(), findIter);
        OneUnitTesting(testMyVector10, testVector10, "find(T)                ");

        MyVector<int> testMyVector11(randomArray, randomSize); 
        testMyVector11.deduplicate(); testMyVector11.sort();
        OneUnitTesting(testMyVector11, true, "disordered()           ");

        testMyVector11.unsort();
        OneUnitTesting(testMyVector11, false, "disordered()           ");

        MyVector<int> testMyVector12(randomArray, randomSize);
        std::vector<int> testVector12(randomArray, randomArray + randomSize);
        functor visitFunctor; testMyVector12.traverse(visitFunctor);
        std::for_each(testVector12.begin(), testVector12.end(), visitFunctor);
        OneUnitTesting(testMyVector12, testVector12, "traverse(VST&)         ");

        delete[] randomArray; randomArray = nullptr;
    }
}