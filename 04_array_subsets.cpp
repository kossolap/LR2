#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "array.h" 
using namespace std;

int main() {
    string inputLine;
    cout << "Введите элементы массива через пробел: ";
    getline(cin, inputLine);

    MyArray* arr = createArray(10);
    
    istringstream iss(inputLine);
    string token;
    while (iss >> token) {
        pushBack(arr, token);
    }

    int n = getLength(arr);
    int totalSubsets = 1 << n;  

    cout << "[";
    for (int mask = 0; mask < totalSubsets; mask++) {
        cout << "{";
        bool first = true;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {  
                if (!first) cout << ", ";
                cout << getElement(arr, i);
                first = false;
            }
        }
        cout << "}";
        if (mask < totalSubsets - 1) cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}