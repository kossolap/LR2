#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Node {
    string data;
    Node* next;
};

struct MyList {
    Node* head;
    int size;
};

MyList* createList();
void pushFront(MyList* list, string value);
void pushBack(MyList* list, string value);
void pushBefore(MyList* list, string target, string value);
void pushAfter(MyList* list, string target, string value);
void popFront(MyList* list);
void popBack(MyList* list);
void popBefore(MyList* list, string target);
void popAfter(MyList* list, string target);
Node* findNode(MyList* list, string value);
void deleteByValue(MyList* list, string value);
void printList(MyList* list);