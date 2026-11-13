#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <cstdio>
#include "array.h"
using namespace std;

struct HashTable {
    MyArray* table;
    int capacity;
    int size;
};

HashTable* createTable(int capacity) {
    HashTable* ht = new HashTable;
    ht->capacity = capacity;
    ht->size = 0;
    ht->table = createArray(capacity);
    for (int i = 0; i < capacity; i++) pushBack(ht->table, "");
    return ht;
}

int foldingHash(int key) {
    string s = to_string(key);
    int sum = 0;
    for (int i = s.length(); i > 0; i -= 3) {
        int start = (i - 3 < 0) ? 0 : i - 3;
        sum += stoi(s.substr(start, i - start));
    }
    return sum;
}

int secondHash(int key, int capacity) {
    return 1 + (key % (capacity - 1));
}

int findKey(HashTable* ht, int key) {
    int index = foldingHash(key) % ht->capacity;
    int startIndex = index;
    int step = secondHash(key, ht->capacity);
    while (getElement(ht->table, index) != "") {
        string entry = getElement(ht->table, index);
        size_t pos = entry.find(':');
        int existingKey = stoi(entry.substr(0, pos));
        if (existingKey == key) return index;
        index = (index + step) % ht->capacity;
        if (index == startIndex) break;
    }
    return -1;
}

void insert(HashTable* ht, int key, string value) {
    int existingIndex = findKey(ht, key);
    if (existingIndex != -1) {
        replaceElement(ht->table, existingIndex, to_string(key) + ":" + value);
        cout << "  Обновлено: ключ " << key << " -> новое значение " << value << endl;
        return;
    }
    int index = foldingHash(key) % ht->capacity;
    int step = secondHash(key, ht->capacity);
    int startIndex = index;
    while (getElement(ht->table, index) != "") {
        index = (index + step) % ht->capacity;
        if (index == startIndex) { cout << "Таблица заполнена!" << endl; return; }
    }
    replaceElement(ht->table, index, to_string(key) + ":" + value);
    ht->size++;
    cout << "  Вставлено: ключ " << key << " -> значение " << value << " (индекс " << index << ")" << endl;
}

void printTable(HashTable* ht) {
    cout << "Содержимое таблицы (индекс: ключ:значение):" << endl;
    for (int i = 0; i < ht->capacity; i++) {
        string val = getElement(ht->table, i);
        if (val != "") cout << "  [" << i << "]: " << val << endl;
    }
}

void printAnalysis() {
    cout << "=== Эмпирический анализ ===" << endl;
    cout << "1. Линейное апробирование: при коллизии идем на index+1." << endl;
    cout << "   Плюсы: простота. Минусы: кластеризация." << endl;
    cout << "2. Двойное хеширование: шаг по второй функции." << endl;
    cout << "   Плюсы: нет кластеризации. Минусы: дольше считать." << endl;
}

/* ====== БЛОК ЗАМЕРОВ (добавлен, вашу логику не меняет) ====== */

long long g_collisions = 0;

void insertLinearCount(HashTable* ht, int key) {
    int index = foldingHash(key) % ht->capacity;
    if (getElement(ht->table, index) != "") g_collisions++;
    int startIndex = index;
    while (getElement(ht->table, index) != "") {
        index = (index + 1) % ht->capacity;
        if (index == startIndex) return;
    }
    replaceElement(ht->table, index, to_string(key));
    ht->size++;
}

void insertDoubleCount(HashTable* ht, int key) {
    int index = foldingHash(key) % ht->capacity;
    if (getElement(ht->table, index) != "") g_collisions++;
    int step = secondHash(key, ht->capacity);
    int startIndex = index;
    while (getElement(ht->table, index) != "") {
        index = (index + step) % ht->capacity;
        if (index == startIndex) return;
    }
    replaceElement(ht->table, index, to_string(key));
    ht->size++;
}

vector<int> genKeys(int n, long long seed = 12345) {
    vector<int> v; v.reserve(n);
    long long x = seed;
    for (int i = 0; i < n; i++) {
        x = (1103515245LL * x + 12345) % 2147483648LL;
        v.push_back((int)(x % 1000000));
    }
    return v;
}

void benchOne(int N, int cap, bool linear, double& outTime, long long& outColl) {
    vector<int> keys = genKeys(N);
    HashTable* ht = createTable(cap);
    g_collisions = 0;
    auto t0 = chrono::high_resolution_clock::now();
    for (int k : keys) {
        if (linear) insertLinearCount(ht, k);
        else        insertDoubleCount(ht, k);
    }
    auto t1 = chrono::high_resolution_clock::now();
    outTime = chrono::duration<double, milli>(t1 - t0).count();
    outColl = g_collisions;
}

void runBenchmark() {
    cout << "\n=== ЗАМЕРЫ ===" << endl;
    int cap = 10007;
    for (int N : {1000, 5000, 9000}) {
        double tLin = 0, tDbl = 0;
        long long cLin = 0, cDbl = 0;
        const int REPS = 5;
        for (int r = 0; r < REPS; r++) {
            double t; long long c;
            benchOne(N, cap, true, t, c);  tLin += t; cLin += c;
            benchOne(N, cap, false, t, c); tDbl += t; cDbl += c;
        }
        printf("N=%5d alpha=%.2f | linear: %.4f ms, coll=%lld | double: %.4f ms, coll=%lld\n",
               N, (double)N / cap,
               tLin / REPS, cLin / REPS,
               tDbl / REPS, cDbl / REPS);
    }
    cout << "=== КОНЕЦ ЗАМЕРОВ ===" << endl;
}

/* ====== КОНЕЦ БЛОКА ЗАМЕРОВ ====== */

int main() {
    printAnalysis();

    int userKey;
    cout << "\nВведите число для проверки метода свертки: ";
    cin >> userKey;

    cout << "\n--- Работа метода свертки для числа " << userKey << " ---" << endl;
    int hashVal = foldingHash(userKey);
    cout << "Хеш-значение (сумма): " << hashVal << endl;
    cout << "Индекс в таблице (по модулю 10): " << (hashVal % 10) << endl;

    int capacity = 10;
    HashTable* ht = createTable(capacity);

    cout << "\n--- Тест 1: Вставляем ключ 10 со значением 'v1' ---" << endl;
    insert(ht, 10, "v1"); printTable(ht);

    cout << "\n--- Тест 2: Вставляем ключ 10 со значением 'v2'  ---" << endl;
    insert(ht, 10, "v2"); printTable(ht);

    cout << "\n--- Тест 3: Вставляем новый ключ 20 ---" << endl;
    insert(ht, 20, "v3"); printTable(ht);

    runBenchmark();   // <-- единственная новая строка в main

    return 0;
}