#include <string>
#include <map>
#include <iostream>
#include <cstdio>

typedef void(*funcPtr)();

/*Finished*/
void CountOnesUnitTesting();               /*Unit test function from CountOnes.cpp*/
void Power2UnitTesting();                  /*Unit test function from Power2.cpp*/
void MaxElementUnitTesting();              /*Unit test function from MaxElement.cpp*/
void FibonacciUnitTesting();               /*Unit test function from Fibonacci.cpp*/
void HanoiTowerUnitTesting();              /*Unit test function from HanoiTower.cpp*/
void SumUnitTesting();                     /*Unit test function from Sum.cpp*/
void ReverseUnitTesting();                 /*Unit test function from Reverse.cpp*/
void GreatestCommonDivisorUnitTesting();   /*Unit test function from GreatestCommonDivisor.cpp*/
void ShiftLeftUnitTesting();               /*Unit test function from ShiftLeft.cpp*/

/*Unfinished*/

void AckermannUnitTesting();               /*Unit test function from Ackermann.cpp*/
void ChessboardCoverUnitTesting();         /*Unit test function from ChessboardCover.cpp*/


int main(int argc, char *argv[])
{
    static std::map<std::string, funcPtr> funcPtrMap;

    /*Add your unit test function*/
    funcPtrMap["CountOnes"] = CountOnesUnitTesting;
    funcPtrMap["Power2"] = Power2UnitTesting;
    funcPtrMap["MaxElement"] = MaxElementUnitTesting;
    funcPtrMap["Fibonacci"] = FibonacciUnitTesting;
    funcPtrMap["HanoiTower"] = HanoiTowerUnitTesting;
    funcPtrMap["Sum"] = SumUnitTesting;
    funcPtrMap["Reverse"] = ReverseUnitTesting;
    funcPtrMap["GreatestCommonDivisor"] = GreatestCommonDivisorUnitTesting;
    funcPtrMap["ShiftLeft"] = ShiftLeftUnitTesting;
    
    funcPtrMap["Ackermann"] = AckermannUnitTesting;
    funcPtrMap["ChessboardCover"] = ChessboardCoverUnitTesting;
    

    for (int i = 1; i < argc; i++) {
        if (funcPtrMap.find(argv[i]) != funcPtrMap.end()) {
            funcPtrMap[argv[i]]();
        }
        else {
            std::cout << "Unit Test Fucntion [" << argv[i] << "] Not Found." << std::endl;
        }
    }
    std::cout << "Test Finished!(Press 'q' to quit)" << std::endl;

    while (getchar() != 'q') {
        ;
    }
    return 0;
}