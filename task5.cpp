#include <iostream>
#include <vector>
#include <algorithm>
#include "tree.h" 
using namespace std;


TreeNode* insertBST(TreeNode* root, int key) {
    if (root == nullptr) {
        return new TreeNode(to_string(key));
    }
    
    int rootVal = stoi(root->key);
    if (key < rootVal) {
        root->left = insertBST(root->left, key);
    } else if (key > rootVal) {
        root->right = insertBST(root->right, key);
    }
    return root;
}

void findForks(TreeNode* root, vector<int>& forks) {
    if (root == nullptr) return;

    findForks(root->left, forks);

    if (root->left != nullptr && root->right != nullptr) {
        forks.push_back(stoi(root->key));
    }

    findForks(root->right, forks);
}

int main() {
    TreeNode* root = nullptr;
    int val;
    
    cout << "Введите последовательность чисел (0 для завершения): ";

    while (cin >> val && val != 0) {
        root = insertBST(root, val);
    }

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