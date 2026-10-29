#include <iostream>
#include <vector>
#include <algorithm>
#include "tree.h" 
using namespace std;

TreeNode* addToTree(TreeNode* root, int key) {
    return insert(root, to_string(key));
}

void findForks(TreeNode* root, vector<int>& forks) {
    if (root == nullptr) return;
    findForks(root->left, forks);

    if (root->left != nullptr && root->right != nullptr) {
        forks.push_back(stoi(root->key));
    }

    findForks(root->right, forks);
}

TreeNode* buildTreeFromInput() {
    TreeNode* root = nullptr;
    int val;
    
    cout << "Введите последовательность чисел (0 для завершения): ";
    while (cin >> val && val != 0) {
        root = addToTree(root, val);
    }
    return root;
}

int main() {
    TreeNode* root = buildTreeFromInput();
    vector<int> forks;
    findForks(root, forks);
    sort(forks.begin(), forks.end());
    cout << "Развилки: ";
    for (int f : forks) {
        cout << f << " ";
    }
    cout << endl;

    return 0;
}