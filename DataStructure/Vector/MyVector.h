/*
This file is a practice for Deng Junhui's book: "data structure[ISBN:9787302330646]"

Question:
Design your own vector.
*/
#ifndef COMPUTER_SCIENCE_DATASTRUCTURE_VECTOR_H
#define COMPUTER_SCIENCE_DATASTRUCTURE_VECTOR_H

#include <cstdlib>
#include <algorithm>

template<typename T>
class MyVector
{
protected:
    static const int DEFAULT_CAPACITY = 3;
    int _capacity, _size; T* _elem;
    void copyFrom(T const *inputArray, int start, int end);
    void expand();
    void shrink();
    int max(int start, int end);

    bool bubble(int start, int end);
    void bubbleSort(int start, int end);
    void selectionSort(int start, int end);
    void merge(int start, int middle, int end);
    void mergeSort(int start, int end);

    int binarySearch(T const &elem, int start, int end) const;
    int binarySearch2(T const &elem, int start, int end) const;
    int binarySearch3(T const &elem, int start, int end) const;
    int fibonacciSearch(T const &elem, int start, int end) const;

    class Fib {
    private:
        int f, g;
    public:
        Fib(int n) {
            f = 1; g = 0;
            while (g < n) {
                next();
            }
        }
        int get() {
            return g;
        }
        int next() {
            g += f; f = g - f;
            return g;
        }
        int prev() {
            f = g - f; g -= f;
            return g;
        }
    };
public:
    /*Constructor & Destructor*/
    MyVector(int capacity = DEFAULT_CAPACITY, int size = 0, T value = 0);
    MyVector(T const *inputArray, int start, int end);
    MyVector(T const *inputArray, int end);
    MyVector(MyVector<T> const& inputMyVector, int start, int end);
    MyVector(MyVector<T> const& inputMyVector);
    ~MyVector();

    /*Read Only Interface*/
    int size() const;
    bool empty() const;
    int disordered() const;
    int find(T const &elem) const;
    int find(T const &elem, int start, int end) const;
    int search(T const &elem) const;
    int search(T const &elem, int start, int end) const;

    /*Read & Write Interface*/
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

    /*Traverse*/
    void traverse(void(*visit)(T&));
    template<typename VST> void traverse(VST&visit);
};

template<typename T>
MyVector<T>::MyVector(int capacity, int size, T value) : _capacity(0), _size(0), _elem(nullptr)
{
    if (capacity > 0 && size > 0) {
        _elem = new T[_capacity = capacity > DEFAULT_CAPACITY ? capacity : DEFAULT_CAPACITY];
        _size = _capacity < size ? _capacity : size;
        for (int i = 0; i < _size; ++i) {
            _elem[i] = value;
        }
    }
}


template<typename T>
MyVector<T>::MyVector(T const *inputArray, int start, int end) : _capacity(0), _size(0), _elem(nullptr)
{
    if (inputArray != nullptr && start >= 0) {
        copyFrom(inputArray, start, end);
    }
}

template<typename T>
MyVector<T>::MyVector(T const *inputArray, int end) : _capacity(0), _size(0), _elem(nullptr)
{
    if (inputArray != nullptr) {
        copyFrom(inputArray, 0, end);
    }
}

template<typename T>
MyVector<T>::MyVector(MyVector<T> const& inputMyVector, int start, int end) : _capacity(0), _size(0), _elem(nullptr)
{
    if (inputMyVector._elem != nullptr && start >= 0 && end <= inputMyVector._size) {
        copyFrom(inputMyVector._elem, start, end);
    }
}

template<typename T>
MyVector<T>::MyVector(MyVector<T> const& inputMyVector) : _capacity(0), _size(0), _elem(nullptr)
{
    if (inputMyVector._elem != nullptr) {
        copyFrom(inputMyVector._elem, 0, inputMyVector._size);
    }
}

template<typename T>
MyVector<T>::~MyVector()
{
    delete[] _elem; _capacity = 0; _size = 0; _elem = nullptr;
}

template<typename T>
int MyVector<T>::size() const
{
    return _size;
}

template<typename T>
bool MyVector<T>::empty() const
{
    return _size == 0;
}

/*Assume array[i]<=array[i+1]*/
template<typename T>
int MyVector<T>::disordered() const
{
    int reverseOrderNum = 0;
    if (_elem != nullptr) {
        for (int i = 1; i < _size; i++) {
            if (_elem[i - 1] > _elem[i]) {
                ++reverseOrderNum;
            }
        }
    }
    return reverseOrderNum;
}

template<typename T>
int MyVector<T>::find(T const &elem) const
{
    return find(elem, 0, _size);
}

template<typename T>
int MyVector<T>::find(T const &elem, int start, int end) const
{
    if (start >= 0 && _elem != nullptr) {
        for (int i = start; i < end; i++) {
            if (_elem[i] == elem) {
                return i;
            }
        }
    }
    return -1;
}

template<typename T>
int MyVector<T>::search(T const &elem) const
{
    return search(elem, 0, _size);
}

template<typename T>
int MyVector<T>::search(T const &elem, int start, int end) const
{
    if (_elem != nullptr && start >= 0 && end <= _size) {
        switch (rand() % 3) {
            case 1: return binarySearch(elem, start, end);
            case 2: return fibonacciSearch(elem, start, end);
            default: return binarySearch2(elem, start, end);
        }
    }
    return -1;
}

template<typename T>
T& MyVector<T>::operator[](int index) const
{
    return _elem[index];
}

template<typename T>
MyVector<T> & MyVector<T>::operator=(MyVector<T> const& inputMyVector)
{
    if (_elem != nullptr) {
        delete[] _elem; _capacity = 0; _size = 0; _elem = nullptr;
    }
    if (inputMyVector._elem != nullptr && inputMyVector._size > 0) {
        copyFrom(inputMyVector._elem, 0, inputMyVector._size);
    }
    return *this;
}

template<typename T>
T MyVector<T>::remove(int index)
{
    T tmp = _elem[index];
    remove(index, index + 1);
    return tmp;
}

template<typename T>
int MyVector<T>::remove(int start, int end)
{
    if (start >= 0 && end <= _size) {
        while (end < _size) {
            _elem[start++] = _elem[end++];
        }
        _size = start;
        shrink();
        return end - start;
    }
    return 0;
}

template<typename T>
int MyVector<T>::insert(int position, T const& elem)
{
    if (position >= 0 && position <= _size) {
        expand();
        for (int i = _size; i > position; --i) {
            _elem[i] = _elem[i - 1];
        }
        _elem[position] = elem; ++_size;
    }
    return position;
}

template<typename T>
int MyVector<T>::insert(T const& elem)
{
    return insert(_size, elem);
}


template<typename T>
void MyVector<T>::sort(int start, int end)
{
    if (_elem != nullptr && start >= 0 && end <= _size) {
        switch (rand() % 3) {
            case 1: bubbleSort(start, end); break;
            case 2: selectionSort(start, end); break;
            default: mergeSort(start, end); break;
        }
    }
}

template<typename T>
void MyVector<T>::sort()
{
    sort(0, _size);
}

template<typename T>
void MyVector<T>::unsort(int start, int end)
{
    T *tmpElem = _elem + start; end -= start;
    for (int i = end; i > 0; --i) {
        std::swap(tmpElem[i - 1], tmpElem[rand() % i]);
    }
}

template<typename T>
void MyVector<T>::unsort()
{
    unsort(0, _size);
}

template<typename T>
int MyVector<T>::deduplicate()
{
    int oldSize = _size;

    for (int i = 1; i < _size; ) {
        find(_elem[i], 0, i) == -1 ? ++i : remove(i);
    }
    return oldSize - _size;
}

template<typename T>
int MyVector<T>::uniquify()
{
    int slow = 0, fast = 0;
    while (++fast < _size) {
        if (_elem[slow] != _elem[fast]) {
            _elem[++slow] = _elem[fast];
        }
    }
    _size = (++slow); shrink();
    return fast - slow;
}

template<typename T>
void MyVector<T>::traverse(void(*visit)(T&))
{
    for (int i = 0; i < _size; i++) {
        visit(_elem[i]);
    }
}

template<typename T>
template<typename VST>
void MyVector<T>::traverse(VST&visit)
{
    for (int i = 0; i < _size; i++) {
        visit(_elem[i]);
    }
}

template<typename T>
void MyVector<T>::copyFrom(T const *inputArray, int start, int end)
{
    if (end > start) {
        _elem = new T[_capacity = 2 * (end - start)]; _size = 0;
        while (start < end) {
            _elem[_size++] = inputArray[start++];
        }
    }
}

template<typename T>
void MyVector<T>::expand()
{
    if (_size < _capacity) {
        return;
    }
    if (_capacity < DEFAULT_CAPACITY) {
        _capacity = DEFAULT_CAPACITY;
    }
    T *oldElem = _elem; _elem = new T[_capacity <<= 1];

    for (int i = 0; i < _size; i++) {
        _elem[i] = oldElem[i];
    }
    delete[] oldElem; oldElem = nullptr;
}

template<typename T>
void MyVector<T>::shrink()
{
    if (_capacity < DEFAULT_CAPACITY) {
        return;
    }
    if (_size * 2 > _capacity) {
        return;
    }
    T *oldElem = _elem; _elem = new T[_capacity >>= 1];

    for (int i = 0; i < _size; i++) {
        _elem[i] = oldElem[i];
    }
    delete[] oldElem; oldElem = nullptr;
}

template<typename T>
int MyVector<T>::max(int start, int end)
{
    if (_elem != nullptr && start >= 0 && end <= _size) {
        int maxIndex = start;
        for (int i = start + 1; i < end; i++) {
            if (_elem[i] > _elem[maxIndex]) {
                maxIndex = i;
            }
        }
        return maxIndex;
    }
    return -1;
}

template<typename T>
bool MyVector<T>::bubble(int start, int end)
{
    bool sorted = true;
    for (int i = start + 1; i < end; i++) {
        if (_elem[i] < _elem[i - 1]) {
            std::swap(_elem[i], _elem[i - 1]);
            sorted = false;
        }
    }
    return sorted;
}

template<typename T>
void MyVector<T>::bubbleSort(int start, int end)
{
    while (!bubble(start, end--)) {
        ;
    }
}

template<typename T>
void MyVector<T>::selectionSort(int start, int end)
{
    while (start < end--) {
        int maxIndex = max(start, end + 1);
        std::swap(_elem[maxIndex], _elem[end]);
    }
}

/*Assume array[i]<=array[i+1]*/
template<typename T>
void MyVector<T>::merge(int start, int middle, int end)
{
    T *tmpArray = new T[middle - start];
    for (int i = start; i < middle; i++) {
        tmpArray[i - start] = _elem[i];
    }
    for (int i = start, j = 0, k = middle; i < end || j < middle - start || k < end; i++) {
        if (j < middle - start && k < end) {
            if (_elem[k] < tmpArray[j]) {
                _elem[i] = _elem[k++];
            }
            else {
                _elem[i] = tmpArray[j++];
            }
        }
        else if (j < middle - start) {
            _elem[i] = tmpArray[j++];
        }
        else {
            _elem[i] = _elem[k++];
        }
    }
    delete[] tmpArray; tmpArray = nullptr;
}

template<typename T>
void MyVector<T>::mergeSort(int start, int end)
{
    if (start + 1 >= end) {
        return;
    }
    int middle = start + (end - start) / 2;
    mergeSort(start, middle);
    mergeSort(middle, end);
    merge(start, middle, end);
}

/*Assume array[i]<=array[i+1]*/
template<typename T>
int MyVector<T>::binarySearch(T const &elem, int start, int end) const
{
    while (start < end) {
        int middle = start + (end - start) / 2;
        if (_elem[middle] < elem) {
            start = middle + 1;
        }
        else if (_elem[middle] > elem) {
            end = middle;
        }
        else {
            return middle;
        }
    }
    return -1;
}

/*Assume array[i]<=array[i+1]*/
template<typename T>
int MyVector<T>::binarySearch2(T const &elem, int start, int end) const
{
    while (start + 1 < end) {
        int middle = start + (end - start) / 2;
        if (elem < _elem[middle]) {
            end = middle;
        }
        else {
            start = middle;
        }
    }
    return (elem == _elem[start]) ? start : -1;
}

/*
Assume array[i]<=array[i+1]
Return insert position if failed.
*/
template<typename T>
int MyVector<T>::binarySearch3(T const &elem, int start, int end) const
{
    while (start < end) {
        int middle = start + (end - start) / 2;
        if (elem < _elem[middle]) {
            end = middle;
        }
        else {
            start = middle + 1;
        }
    }
    return (start - 1);
}

/*Assume array[i]<=array[i+1]*/
template<typename T>
int MyVector<T>::fibonacciSearch(T const &elem, int start, int end) const
{
    Fib fib(end - start);
    while (start < end) {
        while (end - start < fib.get()) {
            fib.prev();
        }
        int middle = start + fib.get() - 1;
        if (elem < _elem[middle]) {
            end = middle;
        }
        else if (elem > _elem[middle]) {
            start = middle + 1;
        }
        else {
            return middle;
        }
    }
    return -1;
}

#endif /*COMPUTER_SCIENCE_DATASTRUCTURE_VECTOR_H*/


