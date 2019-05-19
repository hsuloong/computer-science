#ifndef COMPUTER_SCIENCE_DATASTRUCTURE_MYSTRING_H
#define COMPUTER_SCIENCE_DATASTRUCTURE_MYSTRING_H

class MyString
{
public:
    MyString() : _CString(new char[1]) { _CString[0] = '\0'; }
    MyString(const char *initString);
    MyString(const MyString &initMyString);
    MyString& operator=(MyString const& copyMyString);
    ~MyString() { delete []_CString; }

    bool operator<(MyString const& inputMyString) const;
    bool operator==(MyString const& inputMyString) const;

    const char * c_str() const;

private:
    char *_CString; /*above C++17*/
};


#endif /*COMPUTER_SCIENCE_DATASTRUCTURE_MYSTRING_H*/
