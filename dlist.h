#pragma once
#include <iostream>
#include <string>
using namespace std;

struct DNode {
    string data;
    DNode* next;
    DNode* prev;
};

struct DoublyList {
    DNode* head;
    DNode* tail;
    int size;
};

DoublyList* createDList();
void pushFrontD(DoublyList* dl, string value);
void pushBackD(DoublyList* dl, string value);
void pushBeforeD(DoublyList* dl, string target, string value);
void pushAfterD(DoublyList* dl, string target, string value);
void popFrontD(DoublyList* dl);
void popBackD(DoublyList* dl);
void popBeforeD(DoublyList* dl, string target);
void popAfterD(DoublyList* dl, string target);
void deleteByValueD(DoublyList* dl, string value);
bool findD(DoublyList* dl, string value);
void printDList(DoublyList* dl);