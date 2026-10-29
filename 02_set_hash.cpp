#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include "list.h"
using namespace std;

struct HashSet {
    MyList** buckets;
    int capacity;
};

HashSet* createHashSet(int capacity) {
    HashSet* hs = new HashSet;
    hs->capacity = capacity;
    hs->buckets = new MyList*[capacity];
    for (int i = 0; i < capacity; i++) {
        hs->buckets[i] = createList();
    }
    return hs;
}

int hashFunc(const string& key, int capacity) {
    int hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c) % capacity;
        if (hash < 0) hash += capacity;
    }
    return hash;
}

void setAdd(HashSet* hs, const string& val) {
    int idx = hashFunc(val, hs->capacity);
    if (findNode(hs->buckets[idx], val) == nullptr) {
        pushBack(hs->buckets[idx], val);
        cout << "Добавлено: " << val << endl; 
    } else {
        cout << "Элемент '" << val << "' уже есть (дубликат не добавлен)" << endl;
    }
}

void setDel(HashSet* hs, const string& val) {
    int idx = hashFunc(val, hs->capacity);
    deleteByValue(hs->buckets[idx], val);
    cout << "Удалено: " << val << endl;
}

bool setAt(HashSet* hs, const string& val) {
    int idx = hashFunc(val, hs->capacity);
    return findNode(hs->buckets[idx], val) != nullptr;
}

void setPrint(HashSet* hs) {
    cout << "Содержимое множества: [ ";
    for (int i = 0; i < hs->capacity; i++) {
        Node* curr = hs->buckets[i]->head;
        while (curr != nullptr) {
            cout << curr->data << " ";
            curr = curr->next;
        }
    }
    cout << "]" << endl;
}

map<string, HashSet*> sets;

vector<string> parseQuery(const string& query) {
    vector<string> tokens;
    istringstream iss(query);
    string token;
    while (iss >> token) tokens.push_back(token);
    return tokens;
}

bool executeCmd(const string& query) {
    vector<string> tokens = parseQuery(query);
    if (tokens.size() < 3) return false;

    string cmd = tokens[0];
    string name = tokens[1];
    string val = tokens[2];
    
    if (cmd == "SETADD" && sets.find(name) == sets.end()) {
        sets[name] = createHashSet(1000);
    }
    if (sets.find(name) == sets.end()) {
        cout << "error: set not found" << endl;
        return false;
    }

    HashSet* hs = sets[name];

    if (cmd == "SETADD") {
        setAdd(hs, val);
    } 
    else if (cmd == "SETDEL") {
        setDel(hs, val);
    } 
    else if (cmd == "SET_AT") {
        if (setAt(hs, val)) cout << "TRUE" << endl;
        else cout << "FALSE" << endl;
    } 
    else if (cmd == "SETPRINT") {
        setPrint(hs);
    }
    else {
        return false;
    }
    return true;
}

bool loadFromFile(const string& filename) {
    ifstream fs(filename);
    if (!fs.is_open()) return false;
    string line;
    while (getline(fs, line)) {
        if (!line.empty()) executeCmd(line);
    }
    fs.close();
    return true;
}

void saveToFile(const string& filename, const string& query) {
    if (filename.empty()) return;
    if (query.find("SETADD") != string::npos || query.find("SETDEL") != string::npos) {
        ofstream out(filename, ios::app);
        out << query << endl;
        out.close();
    }
}

int main(int argc, char* argv[]) {
    string filename = "";
    string query = "";

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) filename = argv[++i];
        else if (arg == "--query" && i + 1 < argc) query = argv[++i];
    }

    if (!filename.empty()) loadFromFile(filename);
    if (!query.empty()) {
        if (executeCmd(query)) {
            saveToFile(filename, query);
        }
    }

    return 0;
}