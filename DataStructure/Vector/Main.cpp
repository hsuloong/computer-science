#include <string>
#include <map>
#include <iostream>
#include <cstdio>

typedef void(*funcPtr)();

/*Finished*/
void MyVectorUnitTesting();               /*Unit test function from MyVector.cpp*/

/*Unfinished*/

/*void ChessboardCoverUnitTesting();*/         /*Unit test function from ChessboardCover.cpp*/


int main(int argc, char *argv[])
{
    static std::map<std::string, funcPtr> funcPtrMap;

    /*Add your unit test function*/
    funcPtrMap["MyVector"] = MyVectorUnitTesting;

    /*funcPtrMap["ChessboardCover"] = ChessboardCoverUnitTesting;*/


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