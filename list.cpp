#include "list.h"

MyList* createList() {
    MyList* list = new MyList;
    list->head = nullptr;
    list->size = 0;
    return list;
}

void pushFront(MyList* list, string value) {
    Node* new_node = new Node{value, list->head};
    list->head = new_node;
    list->size++;
}

void pushBack(MyList* list, string value) {
    Node* new_node = new Node{value, nullptr};
    if (list->head == nullptr) { list->head = new_node; list->size++; return; }
    Node* current = list->head;
    while (current->next != nullptr) current = current->next;
    current->next = new_node;
    list->size++;
}

void pushBefore(MyList* list, string target, string value) {
    if (list->head == nullptr) return;
    if (list->head->data == target) { pushFront(list, value); return; }
    Node* current = list->head;
    while (current->next != nullptr && current->next->data != target) current = current->next;
    if (current->next != nullptr) {
        Node* new_node = new Node{value, current->next};
        current->next = new_node;
        list->size++;
    }
}

void pushAfter(MyList* list, string target, string value) {
    Node* current = findNode(list, target);
    if (current != nullptr) {
        Node* new_node = new Node{value, current->next};
        current->next = new_node;
        list->size++;
    }
}

void popFront(MyList* list) {
    if (list->head == nullptr) return;
    Node* temp = list->head;
    list->head = list->head->next;
    delete temp;
    list->size--;
}

void popBack(MyList* list) {
    if (list->head == nullptr) return;
    if (list->head->next == nullptr) { delete list->head; list->head = nullptr; list->size--; return; }
    Node* current = list->head;
    while (current->next->next != nullptr) current = current->next;
    delete current->next;
    current->next = nullptr;
    list->size--;
}

void popBefore(MyList* list, string target) {
    if (list->head == nullptr || list->head->data == target) return;
    Node* current = list->head;
    while (current->next != nullptr && current->next->next != nullptr && current->next->next->data != target) current = current->next;
    if (current->next != nullptr && current->next->next != nullptr) {
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
        list->size--;
    }
}

void popAfter(MyList* list, string target) {
    Node* current = findNode(list, target);
    if (current != nullptr && current->next != nullptr) {
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
        list->size--;
    }
}

Node* findNode(MyList* list, string value) {
    Node* current = list->head;
    while (current != nullptr) {
        if (current->data == value) return current;
        current = current->next;
    }
    return nullptr;
}

void deleteByValue(MyList* list, string value) {
    if (list->head == nullptr) return;
    if (list->head->data == value) { popFront(list); return; }
    Node* current = list->head;
    while (current->next != nullptr && current->next->data != value) current = current->next;
    if (current->next != nullptr) {
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
        list->size--;
    }
}

void printList(MyList* list) {
    Node* current = list->head;
    cout << "[ ";
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << "]" << endl;
}