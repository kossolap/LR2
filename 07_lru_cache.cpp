#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "dlist.h" // (хранит порядок)
#include "list.h"  // (для хеш-таблицы)

using namespace std;


struct HashEntry {
    int key;
    DNode* listNode; // Указатель на узел в двусвязном списке
    HashEntry* next; // Для разрешения коллизий методом цепочек
};

struct LRUHashTable {
    HashEntry** buckets;
    int capacity;
};

LRUHashTable* createHashTable(int capacity) {
    LRUHashTable* ht = new LRUHashTable;
    ht->capacity = capacity;
    ht->buckets = new HashEntry*[capacity];
    for (int i = 0; i < capacity; i++) {
        ht->buckets[i] = nullptr;
    }
    return ht;
}

int hashFunc(int key, int capacity) {
    return key % capacity; // Простая хеш-функция
}

// Поиск узла списка по ключу через хеш-таблицу (O(1))
DNode* hashFind(LRUHashTable* ht, int key) {
    int idx = hashFunc(key, ht->capacity);
    HashEntry* curr = ht->buckets[idx];
    while (curr != nullptr) {
        if (curr->key == key) return curr->listNode;
        curr = curr->next;
    }
    return nullptr;
}

// Добавление связи "ключ -> узел списка" в хеш-таблицу
void hashInsert(LRUHashTable* ht, int key, DNode* listNode) {
    int idx = hashFunc(key, ht->capacity);
    HashEntry* newEntry = new HashEntry{key, listNode, ht->buckets[idx]};
    ht->buckets[idx] = newEntry;
}

// Удаление связи из хеш-таблицы
void hashRemove(LRUHashTable* ht, int key) {
    int idx = hashFunc(key, ht->capacity);
    HashEntry* curr = ht->buckets[idx];
    HashEntry* prev = nullptr;
    while (curr != nullptr) {
        if (curr->key == key) {
            if (prev == nullptr) ht->buckets[idx] = curr->next;
            else prev->next = curr->next;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

struct LRUCache {
    DoublyList* order;   //  для порядка
    LRUHashTable* hash;  // для быстрого поиска
    int capacity;
    int size;
};

LRUCache* createLRUCache(int capacity) {
    LRUCache* cache = new LRUCache;
    cache->order = createDList();
    cache->hash = createHashTable(capacity * 2); 
    cache->capacity = capacity;
    cache->size = 0;
    return cache;
}

// Вспомогательная функция: переместить узел в конец списка (сделать "самым новым")
void moveToTail(LRUCache* cache, DNode* node) {
    if (node == cache->order->tail) return; 
    
    // Вырезаем узел из текущего места
    if (node->prev != nullptr) node->prev->next = node->next;
    else cache->order->head = node->next;
    if (node->next != nullptr) node->next->prev = node->prev;
    
    // Вставляем в конец
    node->next = nullptr;
    node->prev = cache->order->tail;
    if (cache->order->tail != nullptr) cache->order->tail->next = node;
    else cache->order->head = node; 
    cache->order->tail = node;
}

int lruGet(LRUCache* cache, int key) {
    DNode* node = hashFind(cache->hash, key);
    if (node == nullptr) return -1; 
    
    size_t pos = node->data.find(':');
    int value = stoi(node->data.substr(pos + 1));
    
    moveToTail(cache, node);
    return value;
}

void lruSet(LRUCache* cache, int key, int value) {
    DNode* node = hashFind(cache->hash, key);
    string newData = to_string(key) + ":" + to_string(value);
    
    if (node != nullptr) {
        node->data = newData;
        moveToTail(cache, node);
    } else {
        // Если кэш переполнен 
        if (cache->size == cache->capacity) {
            DNode* oldest = cache->order->head;
            size_t pos = oldest->data.find(':');
            int oldKey = stoi(oldest->data.substr(0, pos));
            
            hashRemove(cache->hash, oldKey); 
            
            cache->order->head = oldest->next;
            if (cache->order->head != nullptr) cache->order->head->prev = nullptr;
            else cache->order->tail = nullptr;
            delete oldest;
            cache->size--;
        }
        
        pushBackD(cache->order, newData);
        hashInsert(cache->hash, key, cache->order->tail);
        cache->size++;
    }
}


void processQuery(LRUCache* cache, const string& query, vector<int>& results) {
    istringstream iss(query);
    string token;
    while (iss >> token) {
        if (token == "SET") {
            int k, v;
            iss >> k >> v;
            lruSet(cache, k, v);
        } else if (token == "GET") {
            int k;
            iss >> k;
            results.push_back(lruGet(cache, k));
        }
    }
}

void printResults(const vector<int>& results) {
    for (size_t i = 0; i < results.size(); i++) {
        cout << results[i];
        if (i < results.size() - 1) cout << " ";
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    int capacity = 0;
    string inputLine = "";
    
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--cap" && i + 1 < argc) capacity = stoi(argv[++i]);
        else if (arg == "--query" && i + 1 < argc) inputLine = argv[++i];
    }
    
    if (capacity == 0) {
        cout << "Использование: ./task7 --cap <ёмкость> --query <запросы>" << endl;
        return 1;
    }
    
    LRUCache* cache = createLRUCache(capacity);
    vector<int> results;
    
    processQuery(cache, inputLine, results);
    printResults(results);
    
    return 0;
}