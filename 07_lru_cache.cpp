#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "dlist.h"  
using namespace std;

struct LRUCache {
    DoublyList* order;
    int capacity;
    int size;
};

LRUCache* createLRUCache(int capacity) {
    LRUCache* cache = new LRUCache;
    cache->order = createDList();
    cache->capacity = capacity;
    cache->size = 0;
    return cache;
}

DNode* findNodeByKey(DoublyList* dl, const string& key) {
    DNode* curr = dl->head;
    while (curr != nullptr) {
        size_t pos = curr->data.find(':');
        if (pos != string::npos && curr->data.substr(0, pos) == key) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

void moveToTail(DoublyList* dl, DNode* node) {
    if (node == dl->tail) return;
    
    if (node->prev != nullptr) node->prev->next = node->next;
    else dl->head = node->next;
    if (node->next != nullptr) node->next->prev = node->prev;
    
  
    node->next = nullptr;
    node->prev = dl->tail;
    if (dl->tail != nullptr) dl->tail->next = node;
    else dl->head = node;
    dl->tail = node;
}


string lruGet(LRUCache* cache, const string& key) {
    DNode* node = findNodeByKey(cache->order, key);
    if (node == nullptr) return "-1";
    
    size_t pos = node->data.find(':');
    string value = node->data.substr(pos + 1);
    
    moveToTail(cache->order, node);
    return value;
}

void lruSet(LRUCache* cache, const string& key, const string& value) {
    DNode* node = findNodeByKey(cache->order, key);
    string newData = key + ":" + value;
    
    if (node != nullptr) {
        node->data = newData;
        moveToTail(cache->order, node);
    } else {
        if (cache->size == cache->capacity) {
            DNode* oldest = cache->order->head;
            cache->order->head = oldest->next;
            if (cache->order->head != nullptr) cache->order->head->prev = nullptr;
            else cache->order->tail = nullptr;
            delete oldest;
            cache->size--;
        }
        pushBackD(cache->order, newData);
        cache->size++;
    }
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
    
    istringstream iss(inputLine);
    string token;
    vector<string> results;
    
    while (iss >> token) {
        if (token == "SET") {
            string key, value;
            iss >> key >> value;
            lruSet(cache, key, value);
        } else if (token == "GET") {
            string key;
            iss >> key;
            results.push_back(lruGet(cache, key));
        }
    }
    
    for (int i = 0; i < (int)results.size(); i++) {
        cout << results[i];
        if (i < (int)results.size() - 1) cout << " ";
    }
    cout << endl;
    
    return 0;
}