#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    Node* parent;
};

Node* root = nullptr;

// inserting an element
void insertElement(Node*& root, int x) {
    if (root == nullptr) {
        Node* newNode = new Node;
        newNode->value = x;
        newNode->right = nullptr;
        newNode->left = nullptr;
        root = newNode;
    } else {
        if (x >= root->value) {
            insertElement(root->right, x);
        } else {
            insertElement(root->left, x);
        }
    }
}

//print nodes in inorder
void inorderTraversal(Node* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        cout << root->value << endl;
        inorderTraversal(root->right);
    }
}

//find a node in the tree
Node* findNode(Node* root, int x) {
    if (!root) {
        return nullptr;
    } else if (root->value == x) {
        return root;
    } else if (root->value > x) {
        return findNode(root->left, x);
    } else {
        return findNode(root->right, x);
    }
}

// removing a node from the tree
void removeNode(Node*& root, Node* x) {
    Node* successor;
    if (x->left && x->right) {
        successor = nextNode(x);
    } else {
        successor = x;
    }
    Node* newNode;
    if (successor->left) {
        newNode = successor->left;
    } else {
        newNode = successor->right;
    }
    if (newNode) {
        newNode->parent = successor->parent;
    }
    if (successor->parent) {
        if (successor == successor->parent->left) {
            successor->parent->left = newNode;
        } else {
            successor->parent->right = newNode;
        }
    } else {
        root = newNode;
    }
    if (successor != x) {
        x->value = successor->value;
    }
    delete successor;
}

//the minimum value node in the tree
Node* findMin(Node* root) {
    while (root->left) {
        root = root->left;
    }
    return root;
}

void printMin(Node* root) {
    if (root->left != nullptr) {
        printMin(root->left);
    } else {
        cout << root->value << endl;
    }
}

//the maximum value node in the tree
Node* findMax(Node* root) {
    while (root->right) {
        root = root->right;
    }
    return root;
}

//the next node in the tree
Node* nextNode(Node* x) {
    if (x->right) {
        return findMin(x->right);
    }
    Node* y = x->parent;
    while (y && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

//the previous node in the tree
Node* prevNode(Node* x) {
    if (x->left) {
        return findMax(x->left);
    }
    Node* y = x->parent;
    while (y && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

int main() {
    insertElement(root, 20);
    insertElement(root, 30);
    insertElement(root, 10);
    insertElement(root, 15);
    inorderTraversal(root);
    printMin(root);
    return 0;
}
