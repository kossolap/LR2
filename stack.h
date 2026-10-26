#pragma once
#include <iostream>
#include <string>
#include "list.h"
using namespace std;

struct Stack {
    Node* head;
};

Stack* createStack();
void push(Stack* stack, string value);
void pop(Stack* stack);
void printStack(Stack* stack);