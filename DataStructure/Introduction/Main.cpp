#include <string>
#include <map>
#include <iostream>
#include <cstdio>
typedef void(*funcPtr)();

void CountOnesUnitTesting();               /*Unit test function from CountOnes.cpp*/
void Power2UnitTesting();                  /*Unit test function from Power2.cpp*/
void MaxElementUnitTesting();              /*Unit test function from MaxElement.cpp*/
void FibonacciUnitTesting();               /*Unit test function from Fibonacci.cpp*/
void HanoiTowerUnitTesting();              /*Unit test function from HanoiTower.cpp*/
void GreatestCommonDivisorUnitTesting();   /*Unit test function from GreatestCommonDivisor.cpp*/


int main(int argc, char *argv[])
{
    static std::map<std::string, funcPtr> funcPtrMap;

    /*Add your unit test function*/
    funcPtrMap["CountOnes"] = CountOnesUnitTesting;
    funcPtrMap["Power2"] = Power2UnitTesting;
    funcPtrMap["MaxElement"] = MaxElementUnitTesting;
    funcPtrMap["Fibonacci"] = FibonacciUnitTesting;
    funcPtrMap["HanoiTower"] = HanoiTowerUnitTesting;
    funcPtrMap["GreatestCommonDivisor"] = GreatestCommonDivisorUnitTesting;

    for (int i = 1; i < argc; i++) {
        if (funcPtrMap.find(argv[i]) != funcPtrMap.end()) {
            funcPtrMap[argv[i]]();
        }
        else {
            std::cout << "Unit Test Fucntion [" << argv[i] << "] Not Found." << std::endl;
        }
    }

    while (getchar() != 'q') {
        ;
    }
    return 0;
}