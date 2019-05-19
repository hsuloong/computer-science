#include "MyString.h"

#include <cstring>
#include <iostream>

MyString::MyString(const char * initString) : _CString(new char[strlen(initString) + 1])
{
    strcpy_s(_CString, strlen(initString) + 1, initString);
}

MyString::MyString(const MyString &initMyString) : _CString(new char[strlen(initMyString._CString) + 1])
{
    strcpy_s(_CString, strlen(initMyString._CString) + 1, initMyString._CString);
}

MyString& MyString::operator=(MyString const& copyMyString)
{
    if (_CString == copyMyString._CString) {
        return *this;
    }
    this->~MyString();
    _CString = new char[strlen(copyMyString._CString) + 1];
    strcpy_s(_CString, strlen(copyMyString._CString) + 1, copyMyString._CString);
    return *this;
}

bool MyString::operator<(MyString const& inputMyString) const
{
    auto compareResult = strcmp(_CString, inputMyString._CString);
    return compareResult < 0;
}

bool MyString::operator==(MyString const& inputMyString) const
{
    auto compareResult = strcmp(_CString, inputMyString._CString);
    return compareResult == 0;
}

const char * MyString::c_str() const
{
    return _CString;
}

static void OneUnitTesting(const MyString &oneTestMyString, const char *correctResult, const char *funcName)
{
    if (strcmp(oneTestMyString.c_str(), correctResult) == 0) {
        std::cout << "function[" << funcName << "\t]: \t\t|CORRECT|\n";
    }
    else {
        std::cout << "function[" << funcName << "\t]: \t\t|WRONG  |\n";
    }
}

static void OneUnitTesting(bool testResult, bool correctResult, const char *funcName)
{
    if (testResult == correctResult) {
        std::cout << "function[" << funcName << "\t]: \t\t|CORRECT|\n";
    }
    else {
        std::cout << "function[" << funcName << "\t]: \t\t|WRONG  |\n";
    }
}

void MyStringUnitTesting()
{
    MyString testMyString1;
    OneUnitTesting(testMyString1, "", "MyString()\t\t\t");

    MyString testMyString2("Hello, world!");
    OneUnitTesting(testMyString2, "Hello, world!", "MyString(const char *)\t\t");

    MyString testMyString3(testMyString2);
    OneUnitTesting(testMyString3, "Hello, world!", "MyString(const MyString&)\t");

    testMyString1 = testMyString3;
    OneUnitTesting(testMyString1, "Hello, world!", "MyString& operator=(MyString const&)");

    const char *compareStrings[5][2] = { {"abcdefgh", "acdefghl"}, {"abcd", "abcde"}, 
                                        {"", "a"}, {"a", "b"}, {"a", "a "} };
    for (size_t i = 0; i < 5; i++) {
        MyString testMyString4(compareStrings[i][0]), testMyString5(compareStrings[i][1]);
        bool testResult = testMyString4 < testMyString5;
        OneUnitTesting(testResult, true, "bool operator<(MyString const&) const");

        testResult = testMyString5 < testMyString4;
        OneUnitTesting(testResult, false, "bool operator<(MyString const&) const");

        testResult = testMyString4 == testMyString5;
        OneUnitTesting(testResult, false, "bool operator==(MyString const&) const");
    }
    MyString  testMyString6("Hello, world!"), testMyString7("Hello, world!");
    bool testResult = testMyString6 == testMyString7;
    OneUnitTesting(testResult, true, "bool operator<(MyString const&) const");
}