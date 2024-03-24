#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

class Stack {
private:
    Node* top;

public:
    Stack() {
        top = nullptr;
    }

    void push(int value) {
        Node* temp = new Node;
        temp->data = value;
        if (top == nullptr) {
            temp->next = nullptr;
        } else {
            temp->next = top;
        }
        top = temp;
    }

    void pop() {
        if (top == nullptr)
            cout << "The stack is empty!";
        else
            top = top->next;
    }

    void showTop() {
        if (top == nullptr)
            cout << "The stack is empty!" << endl;
        else
            cout << top->data << endl;
    }
};

int main() {
    Stack stack;
    stack.push(5);
    stack.push(6);
    stack.showTop();
    stack.pop();
    stack.showTop();
    system("pause");
    return 0;
}
