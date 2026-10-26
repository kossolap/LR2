#include <iostream>
#include <string>
#include "array.h"
using namespace std;

struct HashTable {
    MyArray* keys;
    MyArray* values;
    int capacity;
    int size;
};

HashTable* createHashTable(int capacity) {
    HashTable* ht = new HashTable;
    ht->capacity = capacity;
    ht->size = 0;
    ht->keys = createArray(capacity);
    ht->values = createArray(capacity);
    return ht;
}

int hashFolding(int key, int capacity, bool showSteps = false) {
    int sum = 0;
    int tempKey = key;
    string steps = "";
    
    while (tempKey > 0) {
        int part = tempKey % 1000;
        sum += part;
        if (showSteps) {
            if (!steps.empty()) steps = "+" + steps;
            steps = to_string(part) + steps;
        }
        tempKey /= 1000;
    }
    
    if (showSteps) {
        cout << "Вывод: " << steps << " = " << sum << endl;
    }
    
    return sum % capacity;
}

void printAnalysis() {
    cout << "=== Эмпирический анализ хеширования ===" << endl;
    cout << "Метод: Двойное хеширование (открытая адресация)." << endl;
    cout << "Описание: При коллизии шаг смещения вычисляется по второй хеш-функции." << endl;
    cout << "Достоинства: Отсутствие первичной и вторичной кластеризации." << endl;
    cout << "Недостатки: Требует вычисления двух хеш-функций, таблица должна быть больше числа элементов." << endl;
    cout << "=========================================" << endl;
}

int main() {
    printAnalysis();
    
    HashTable* ht = createHashTable(100);
    int key;
    
    cout << "Введите число: ";
    cin >> key;
    
    int hashValue = hashFolding(key, ht->capacity, true);
    cout << "Хеш-значение (индекс в таблице): " << hashValue << endl;
    
    return 0;
}