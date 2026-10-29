#include <string>
#include "stack.h"
#include "list.h"
using namespace std;

string peek(Stack* s) {
    if (s->head == nullptr) return "";
    return s->head->data;
}

int priority(const string& op) {
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

bool isOperator(const string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

string infixToPostfix(const string& expr) {
    Stack* s = createStack(); 
    string result = "";

    for (int i = 0; i < (int)expr.size(); i++) {
        char c = expr[i];
        if (c == ' ') continue;
        if (isalnum(c)) {
            result += c;
        }
    
        else if (c == '(') {
            push(s, string(1, c));
        }
    
        else if (c == ')') {
            while (s->head != nullptr && peek(s) != "(") {
                result += peek(s);
                pop(s);
            }
            if (s->head != nullptr) pop(s);
        }
   
        else if (isOperator(string(1, c))) {
            string op(1, c);
            while (s->head != nullptr && peek(s) != "(" &&
                   priority(peek(s)) >= priority(op)) {
                result += peek(s);
                pop(s);
            }
            push(s, op);
        }
    }

    while (s->head != nullptr) {
        result += peek(s);
        pop(s);
    }

    delete s;
    return result;
}

int main() {
    string expr;
    cout << "Введите инфиксное выражение: ";
    getline(cin, expr);

    cout << "Постфиксная запись: " << infixToPostfix(expr) << endl;
}