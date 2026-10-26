#include "dlist.h"

DoublyList* createDList() {
    DoublyList* dl = new DoublyList;
    dl->head = nullptr;
    dl->tail = nullptr;
    dl->size = 0;
    return dl;
}

void pushFrontD(DoublyList* dl, string value) {
    DNode* new_node = new DNode{value, dl->head, nullptr};
    if (dl->head != nullptr) dl->head->prev = new_node;
    else dl->tail = new_node;
    dl->head = new_node;
    dl->size++;
}

void pushBackD(DoublyList* dl, string value) {
    DNode* new_node = new DNode{value, nullptr, dl->tail};
    if (dl->tail != nullptr) dl->tail->next = new_node;
    else dl->head = new_node;
    dl->tail = new_node;
    dl->size++;
}

void pushBeforeD(DoublyList* dl, string target, string value) {
    DNode* curr = dl->head;
    while (curr != nullptr && curr->data != target) curr = curr->next;
    if (curr == nullptr) return;
    if (curr->prev == nullptr) pushFrontD(dl, value);
    else {
        DNode* new_node = new DNode{value, curr, curr->prev};
        curr->prev->next = new_node;
        curr->prev = new_node;
        dl->size++;
    }
}

void pushAfterD(DoublyList* dl, string target, string value) {
    DNode* curr = dl->head;
    while (curr != nullptr && curr->data != target) curr = curr->next;
    if (curr == nullptr) return;
    if (curr->next == nullptr) pushBackD(dl, value);
    else {
        DNode* new_node = new DNode{value, curr->next, curr};
        curr->next->prev = new_node;
        curr->next = new_node;
        dl->size++;
    }
}

void popFrontD(DoublyList* dl) {
    if (dl->head == nullptr) return;
    DNode* temp = dl->head;
    dl->head = dl->head->next;
    if (dl->head != nullptr) dl->head->prev = nullptr;
    else dl->tail = nullptr;
    delete temp;
    dl->size--;
}

void popBackD(DoublyList* dl) {
    if (dl->tail == nullptr) return;
    DNode* temp = dl->tail;
    dl->tail = dl->tail->prev;
    if (dl->tail != nullptr) dl->tail->next = nullptr;
    else dl->head = nullptr;
    delete temp;
    dl->size--;
}

void popBeforeD(DoublyList* dl, string target) {
    DNode* curr = dl->head;
    while (curr != nullptr && curr->data != target) curr = curr->next;
    if (curr == nullptr || curr->prev == nullptr) return;
    DNode* temp = curr->prev;
    curr->prev = temp->prev;
    if (temp->prev != nullptr) temp->prev->next = curr;
    else dl->head = curr;
    delete temp;
    dl->size--;
}

void popAfterD(DoublyList* dl, string target) {
    DNode* curr = dl->head;
    while (curr != nullptr && curr->data != target) curr = curr->next;
    if (curr == nullptr || curr->next == nullptr) return;
    DNode* temp = curr->next;
    curr->next = temp->next;
    if (temp->next != nullptr) temp->next->prev = curr;
    else dl->tail = curr;
    delete temp;
    dl->size--;
}

void deleteByValueD(DoublyList* dl, string value) {
    DNode* curr = dl->head;
    while (curr != nullptr && curr->data != value) curr = curr->next;
    if (curr == nullptr) return;
    if (curr->prev != nullptr) curr->prev->next = curr->next; else dl->head = curr->next;
    if (curr->next != nullptr) curr->next->prev = curr->prev; else dl->tail = curr->prev;
    delete curr;
    dl->size--;
}

bool findD(DoublyList* dl, string value) {
    DNode* curr = dl->head;
    while (curr != nullptr) {
        if (curr->data == value) return true;
        curr = curr->next;
    }
    return false;
}

void printDList(DoublyList* dl) {
    DNode* curr = dl->head;
    cout << "[ ";
    while (curr != nullptr) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << "]" << endl;
}