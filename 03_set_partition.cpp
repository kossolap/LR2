#include <iostream>
#include <string>
#include <vector>
#include <sstream>
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
    }
}
vector<string> getElements(HashSet* hs) {
    vector<string> elements;
    for (int i = 0; i < hs->capacity; i++) {
        Node* curr = hs->buckets[i]->head;
        while (curr != nullptr) {
            elements.push_back(curr->data);
            curr = curr->next;
        }
    }
    return elements;
}

bool solve(vector<string>& nums, vector<int>& subsetSums, vector<vector<string>>& subsets, int target, int index, int k) {
    if (index == (int)nums.size()) {
        for (int s : subsetSums) {
            if (s != target) return false;
        }
        return true;
    }

    int val = stoi(nums[index]);
    
    for (int i = 0; i < k; i++) {
        if (subsetSums[i] + val <= target) {
            subsetSums[i] += val;
            subsets[i].push_back(nums[index]);

            if (solve(nums, subsetSums, subsets, target, index + 1, k)) return true;

            subsetSums[i] -= val;
            subsets[i].pop_back();
        }
        if (subsetSums[i] == 0) break;
    }
    return false;
}

void printResult(vector<vector<string>>& subsets, int k) {
    cout << "Разбиение найдено (" << k << " подмножеств):" << endl;
    for (int i = 0; i < k; i++) {
        cout << "{";
        for (int j = 0; j < (int)subsets[i].size(); j++) {
            cout << subsets[i][j];
            if (j < (int)subsets[i].size() - 1) cout << ", ";
        }
        cout << "}" << endl;
    }
}

int main() {
    string inputLine;
    int targetSum;

    cout << "Введите элементы множества через пробел: ";
    getline(cin, inputLine);
    cout << "Введите требуемую сумму каждого подмножества: ";
    cin >> targetSum;

    HashSet* mySet = createHashSet(100);
    istringstream iss(inputLine);
    string token;
    int totalSum = 0;

    while (iss >> token) {
        setAdd(mySet, token);
        totalSum += stoi(token);
    }

    if (totalSum % targetSum != 0) {
        cout << "Ошибка: общая сумма (" << totalSum << ") не делится на " << targetSum << endl;
        return 0;
    }

    // 4. Подготовка данных для рекурсии
    vector<string> nums = getElements(mySet); 
    int k = totalSum / targetSum;            
    vector<int> subsetSums(k, 0);
    vector<vector<string>> subsets(k);

    if (solve(nums, subsetSums, subsets, targetSum, 0, k)) {
        printResult(subsets, k);
    } else {
        cout << "Ошибка: невозможно разбить множество на подмножества с суммой " << targetSum << endl;
    }

    return 0;
}