#pragma once
#include <iostream>
#include <string>
using namespace std;

struct MyArray {
    string* data;
    int size;
    int capacity;
};

MyArray* createArray(int initialCapacity);
void pushBack(MyArray* arr, string value);
void pushIndex(MyArray* arr, int index, string value);
string getElement(MyArray* arr, int index);
void deleteElement(MyArray* arr, int index);
void replaceElement(MyArray* arr, int index, string newValue);
int getLength(MyArray* arr);
void printArray(MyArray* arr);