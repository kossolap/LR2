#include "tree.h"

AVLTree* createTree() {
    AVLTree* tree = new AVLTree;
    tree->root = nullptr;
    return tree;
}

int getHeight(TreeNode* node) { return node ? node->height : 0; }
int getBalance(TreeNode* node) { return node ? getHeight(node->left) - getHeight(node->right) : 0; }
void updateHeight(TreeNode* node) { if (node) node->height = 1 + max(getHeight(node->left), getHeight(node->right)); }

TreeNode* rotateRight(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

TreeNode* rotateLeft(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

TreeNode* balance(TreeNode* node) {
    if (!node) return node;
    updateHeight(node);
    int bf = getBalance(node);
    if (bf > 1 && getBalance(node->left) >= 0) return rotateRight(node);
    if (bf < -1 && getBalance(node->right) <= 0) return rotateLeft(node);
    if (bf > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (bf < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

TreeNode* insert(TreeNode* node, string key) {
    if (!node) return new TreeNode(key);
    if (key < node->key) node->left = insert(node->left, key);
    else if (key > node->key) node->right = insert(node->right, key);
    else return node;
    return balance(node);
}

TreeNode* minValueNode(TreeNode* node) {
    TreeNode* current = node;
    while (current && current->left != nullptr) current = current->left;
    return current;
}

TreeNode* deleteNode(TreeNode* root, string key) {
    if (root == nullptr) return root;
    if (key < root->key) root->left = deleteNode(root->left, key);
    else if (key > root->key) root->right = deleteNode(root->right, key);
    else {
        if (root->left == nullptr || root->right == nullptr) {
            TreeNode* temp = root->left ? root->left : root->right;
            if (temp == nullptr) { temp = root; root = nullptr; }
            else *root = *temp;
            delete temp;
        } else {
            TreeNode* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    if (root == nullptr) return root;
    return balance(root);
}

TreeNode* search(TreeNode* node, string key) {
    if (!node || node->key == key) return node;
    if (key < node->key) return search(node->left, key);
    return search(node->right, key);
}

void printInorder(TreeNode* node) {
    if (!node) return;
    printInorder(node->left);
    cout << node->key << " ";
    printInorder(node->right);
}

void printPreorder(TreeNode* node) {
    if (!node) return;
    cout << node->key << " ";
    printPreorder(node->left);
    printPreorder(node->right);
}

void printPostorder(TreeNode* node) {
    if (!node) return;
    printPostorder(node->left);
    printPostorder(node->right);
    cout << node->key << " ";
}

void printTree(TreeNode* node, string order) {
    if (order == "preorder") printPreorder(node);
    else if (order == "postorder") printPostorder(node);
    else printInorder(node);
}