#pragma once
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct TreeNode {
    string key;
    TreeNode* left;
    TreeNode* right;
    int height;
    TreeNode(string k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

struct AVLTree {
    TreeNode* root;
};

AVLTree* createTree();
TreeNode* insert(TreeNode* node, string key);
TreeNode* search(TreeNode* node, string key);
TreeNode* deleteNode(TreeNode* root, string key);
void printTree(TreeNode* node, string order);