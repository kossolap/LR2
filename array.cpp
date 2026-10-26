#include "array.h"

MyArray* createArray(int initialCapacity) {
    MyArray* arr = new MyArray;
    arr->data = new string[initialCapacity];
    arr->size = 0;
    arr->capacity = initialCapacity;
    return arr;
}

void pushBack(MyArray* arr, string value) {
    if (arr->size == arr->capacity) {
        int newCapacity = arr->capacity * 2;
        string* newData = new string[newCapacity];
        for (int i = 0; i < arr->size; i++) newData[i] = arr->data[i];
        delete[] arr->data;
        arr->data = newData;
        arr->capacity = newCapacity;
    }
    arr->data[arr->size] = value;
    arr->size++;
}

void pushIndex(MyArray* arr, int index, string value) {
    if (index < 0 || index > arr->size) return;
    if (arr->size == arr->capacity) {
        int newCapacity = arr->capacity * 2;
        string* newData = new string[newCapacity];
        for (int i = 0; i < arr->size; i++) newData[i] = arr->data[i];
        delete[] arr->data;
        arr->data = newData;
        arr->capacity = newCapacity;
    }
    for (int i = arr->size; i > index; i--) arr->data[i] = arr->data[i - 1];
    arr->data[index] = value;
    arr->size++;
}

string getElement(MyArray* arr, int index) {
    if (index < 0 || index >= arr->size) return "";
    return arr->data[index];
}

void deleteElement(MyArray* arr, int index) {
    if (index < 0 || index >= arr->size) return;
    for (int i = index; i < arr->size - 1; i++) arr->data[i] = arr->data[i + 1];
    arr->size--;
}

void replaceElement(MyArray* arr, int index, string newValue) {
    if (index < 0 || index >= arr->size) return;
    arr->data[index] = newValue;
}

int getLength(MyArray* arr) { return arr->size; }

void printArray(MyArray* arr) {
    cout << "[ ";
    for (int i = 0; i < arr->size; i++) cout << arr->data[i] << " ";
    cout << "]" << endl;
}