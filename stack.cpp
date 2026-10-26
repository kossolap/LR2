#include "stack.h"

Stack* createStack() {
    Stack* stack = new Stack;
    stack->head = nullptr;
    return stack;
}

void push(Stack* stack, string value) {
    Node* new_node = new Node{value, stack->head};
    stack->head = new_node;
}

void pop(Stack* stack) {
    if (stack->head == nullptr) return;
    Node* temp = stack->head;
    stack->head = stack->head->next;
    delete temp;
}

void printStack(Stack* stack) {
    Node* current = stack->head;
    cout << "[ ";
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << "]" << endl;
}