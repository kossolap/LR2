#include <iostream>
#include <string>
#include "array.h" // Подключаем наш массив из ЛР1
using namespace std;

// Структура хеш-таблицы на основе нашего MyArray
struct HashTable {
    MyArray* table; // Используем массив из ЛР1 для хранения ключей (в виде строк)
    int capacity;
    int size;
};

// Создание таблицы (используем createArray из ЛР1)
HashTable* createTable(int capacity) {
    HashTable* ht = new HashTable;
    ht->capacity = capacity;
    ht->size = 0;
    ht->table = createArray(capacity); // Создаем массив из ЛР1
    
    // Заполняем массив пустыми строками (означает "ячейка свободна")
    for (int i = 0; i < capacity; i++) {
        pushBack(ht->table, "");
    }
    return ht;
}

// === МЕТОД СВЕРТКИ (из задания 6.2) ===
int foldingHash(int key, bool showSteps = false) {
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
        cout << "Свертка: " << steps << " = " << sum << endl;
    }
    return sum;
}

// Вторая хеш-функция для двойного хеширования
int secondHash(int key, int capacity) {
    return 1 + (key % (capacity - 1));
}

// === ЛИНЕЙНОЕ АПРОБИРОВАНИЕ ===
void insertLinear(HashTable* ht, int key) {
    int index = foldingHash(key) % ht->capacity;
    int startIndex = index;
    
    // Ищем свободную ячейку (пустую строку)
    while (getElement(ht->table, index) != "") {
        index = (index + 1) % ht->capacity;
        if (index == startIndex) {
            cout << "Таблица заполнена!" << endl;
            return;
        }
    }
    
    // Вставляем ключ (превращаем число в строку)
    replaceElement(ht->table, index, to_string(key));
    ht->size++;
    cout << "  Вставлено (Линейное): " << key << " -> индекс " << index << endl;
}

// === ДВОЙНОЕ ХЕШИРОВАНИЕ ===
void insertDouble(HashTable* ht, int key) {
    int index = foldingHash(key) % ht->capacity;
    int step = secondHash(key, ht->capacity);
    int startIndex = index;
    
    while (getElement(ht->table, index) != "") {
        index = (index + step) % ht->capacity;
        if (index == startIndex) {
            cout << "Таблица заполнена!" << endl;
            return;
        }
    }
    
    replaceElement(ht->table, index, to_string(key));
    ht->size++;
    cout << "  Вставлено (Двойное): " << key << " -> индекс " << index << endl;
}

// Вывод таблицы
void printTable(HashTable* ht) {
    cout << "Содержимое таблицы (индекс: ключ):" << endl;
    for (int i = 0; i < ht->capacity; i++) {
        string val = getElement(ht->table, i);
        if (val != "") {
            cout << "  [" << i << "]: " << val << endl;
        }
    }
}

void printAnalysis() {
    cout << "=== Эмпирический анализ ===" << endl;
    cout << "1. Линейное апробирование: при коллизии идем на index+1." << endl;
    cout << "   Плюсы: простота. Минусы: кластеризация." << endl;
    cout << "2. Двойное хеширование: шаг по второй функции." << endl;
    cout << "   Плюсы: нет кластеризации. Минусы: дольше считать." << endl;
}

int main() {
    printAnalysis();
    
    int userKey;
    cout << "\nВведите число для проверки метода свертки: ";
    cin >> userKey;
    
    cout << "\n--- Работа метода свертки для числа " << userKey << " ---" << endl;
    int hashVal = foldingHash(userKey, true);
    cout << "Хеш-значение (сумма): " << hashVal << endl;
    cout << "Индекс в таблице (по модулю 10): " << (hashVal % 10) << endl;
    
    // Создаем две таблицы на нашем массиве (размер 10)
    int capacity = 10;
    HashTable* htLinear = createTable(capacity);
    HashTable* htDouble = createTable(capacity);
    
    cout << "\n--- Тест Линейного апробирования (вставляем 10, 20, 30, 40, 10) ---" << endl;
    insertLinear(htLinear, 10);
    insertLinear(htLinear, 20);
    insertLinear(htLinear, 30);
    insertLinear(htLinear, 40);
    insertLinear(htLinear, 10); // Коллизия
    printTable(htLinear);
    
    cout << "\n--- Тест Двойного хеширования (вставляем 10, 20, 30, 40, 10) ---" << endl;
    insertDouble(htDouble, 10);
    insertDouble(htDouble, 20);
    insertDouble(htDouble, 30);
    insertDouble(htDouble, 40);
    insertDouble(htDouble, 10); // Коллизия
    printTable(htDouble);
    
    return 0;
}