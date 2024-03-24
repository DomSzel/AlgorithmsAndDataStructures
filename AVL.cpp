#include <iostream>
using namespace std;

class AVLTree {
private:
    struct Node {
        int value;
        int height;
        Node* left;
        Node* right;
    };

    Node* root;

    //insert a node into the AVL tree
    Node* insertNode(int x, Node* currentNode) {
        if (currentNode == nullptr) {
            currentNode = new Node;
            currentNode->value = x;
            currentNode->height = 0;
            currentNode->left = currentNode->right = nullptr;
        } else if (x < currentNode->value) {
            currentNode->left = insertNode(x, currentNode->left);
            if (height(currentNode->left) - height(currentNode->right) == 2) {
                if (x < currentNode->left->value)
                    currentNode = singleRightRotation(currentNode);
                else
                    currentNode = doubleRightRotation(currentNode);
            }
        } else if (x > currentNode->value) {
            currentNode->right = insertNode(x, currentNode->right);
            if (height(currentNode->right) - height(currentNode->left) == 2) {
                if (x > currentNode->right->value)
                    currentNode = singleLeftRotation(currentNode);
                else
                    currentNode = doubleLeftRotation(currentNode);
            }
        }

        currentNode->height = max(height(currentNode->left), height(currentNode->right)) + 1;
        return currentNode;
    }

    //single right rotation
    Node* singleRightRotation(Node*& currentNode) {
        Node* newRoot = currentNode->left;
        currentNode->left = newRoot->right;
        newRoot->right = currentNode;
        currentNode->height = max(height(currentNode->left), height(currentNode->right)) + 1;
        newRoot->height = max(height(newRoot->left), currentNode->height) + 1;
        return newRoot;
    }

    //single left rotation
    Node* singleLeftRotation(Node*& currentNode) {
        Node* newRoot = currentNode->right;
        currentNode->right = newRoot->left;
        newRoot->left = currentNode;
        currentNode->height = max(height(currentNode->left), height(currentNode->right)) + 1;
        newRoot->height = max(height(currentNode->right), currentNode->height) + 1;
        return newRoot;
    }

    //double left rotation
    Node* doubleLeftRotation(Node*& currentNode) {
        currentNode->right = singleRightRotation(currentNode->right);
        return singleLeftRotation(currentNode);
    }

    //double right rotation
    Node* doubleRightRotation(Node*& currentNode) {
        currentNode->left = singleLeftRotation(currentNode->left);
        return singleRightRotation(currentNode);
    }

    //find the node with the minimum value in a subtree
    Node* findMin(Node* currentNode) {
        if (currentNode == nullptr)
            return nullptr;
        else if (currentNode->left == nullptr)
            return currentNode;
        else
            return findMin(currentNode->left);
    }

    //find the node with the maximum value in a subtree
    Node* findMax(Node* currentNode) {
        if (currentNode == nullptr)
            return nullptr;
        else if (currentNode->right == nullptr)
            return currentNode;
        else
            return findMax(currentNode->right);
    }

    // remove a node from the AVL tree
    Node* removeNode(int x, Node* currentNode) {
        Node* temp;

        if (currentNode == nullptr)
            return nullptr;

        else if (x < currentNode->value)
            currentNode->left = removeNode(x, currentNode->left);
        else if (x > currentNode->value)
            currentNode->right = removeNode(x, currentNode->right);
        else if (currentNode->left && currentNode->right) {
            temp = findMin(currentNode->right);
            currentNode->value = temp->value;
            currentNode->right = removeNode(currentNode->value, currentNode->right);
        } else {
            temp = currentNode;
            if (currentNode->left == nullptr)
                currentNode = currentNode->right;
            else if (currentNode->right == nullptr)
                currentNode = currentNode->left;
            delete temp;
        }

        if (currentNode == nullptr)
            return currentNode;

        currentNode->height = max(height(currentNode->left), height(currentNode->right)) + 1;

        if (height(currentNode->left) - height(currentNode->right) == 2) {
            if (height(currentNode->left->left) - height(currentNode->left->right) == 1)
                return singleLeftRotation(currentNode);
            else
                return doubleLeftRotation(currentNode);
        } else if (height(currentNode->right) - height(currentNode->left) == 2) {
            if (height(currentNode->right->right) - height(currentNode->right->left) == 1)
                return singleRightRotation(currentNode);
            else
                return doubleRightRotation(currentNode);
        }
        return currentNode;
    }

    // get the height of a node
    int height(Node* currentNode) {
        return (currentNode == nullptr ? -1 : currentNode->height);
    }

public:
    // constructor to initialize AVL root
    AVLTree() {
        root = nullptr;
    }

    //insert a value into the AVL tree
    void insert(int x) {
        root = insertNode(x, root);
    }

    // remove a value from the AVL tree
    void remove(int x) {
        root = removeNode(x, root);
    }

    // display the AVL tree in inorder traversal
    void display() {
        inorder(root);
        cout << endl;
    }

    // inorder traversal of the AVL tree
    void inorder(Node* currentNode) {
        if (currentNode == nullptr)
            return;
        inorder(currentNode->left);
        cout << currentNode->value << " ";
        inorder(currentNode->right);
    }
};

int main() {
    AVLTree avl;
    avl.insert(20);
    avl.insert(25);
    avl.insert(15);
    avl.insert(10);
    avl.insert(30);
    avl.insert(5);
    avl.insert(35);
    avl.insert(67);
    avl.insert(43);
    avl.insert(21);
    avl.insert(10);
    avl.insert(89);
    avl.insert(38);
    avl.insert(69);
    avl.display(); // before
    avl.remove(5);
    avl.remove(35);
    avl.remove(65);
    avl.remove(89);
    avl.remove(43);
    avl.remove(88);
    avl.remove(20);
    avl.remove(38);
    avl.display(); //after
    return 0;
}
