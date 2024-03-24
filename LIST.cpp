#include <iostream>
using namespace std;

struct Node {
    Node* next;
    int value;
};

void addToFront(Node*& head, int value) {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = head;
    head = newNode;
}

void addNodeToFront(Node*& head, Node* newNode) {
    newNode->next = head;
    head = newNode;
}

void addToBack(Node*& head, int value) {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;

    if (!head) {
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->next) {
        current = current->next;
    }

    current->next = newNode;
}

void addNodeToBack(Node*& head, Node*& newNode) {
    newNode->next = nullptr;

    if (!head) {
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->next) {
        current = current->next;
    }

    current->next = newNode;
}

void displayList(Node* head) {
    if (!head) {
        cout << "The list is empty" << endl;
    } else {
        Node* current = head;
        while (current) {
            cout << current->value << endl;
            current = current->next;
        }
    }
}

// 1. Delete every other node
void deleteEveryOtherNode(Node*& head) {
    if (!head) {
        cout << "The list is empty" << endl;
        return;
    }

    Node* current = head;
    while (current && current->next) {
        Node* nextNode = current->next;
        current->next = nextNode->next;
        delete nextNode;
        current = current->next;
    }
    displayList(head);
}

// 2. Duplicate each node
void duplicateNodes(Node*& head) {
    Node* duplicatedList = nullptr;
    Node* current = head;
    while (current) {
        addToBack(duplicatedList, current->value);
        addToBack(duplicatedList, current->value);
        current = current->next;
    }
    head = duplicatedList;
    displayList(head);
}

// 3. Copy the list
void copyList(Node*& head) {
    Node* tail = head;
    while (tail->next) {
        tail = tail->next;
    }

    Node* current = head;
    while (current != tail) {
        addToBack(current, current->value);
        current = current->next;
    }
    addToBack(tail, tail->value);
    displayList(head);
}

// 4. Calculate the average value of nodes
void calculateAverage(Node* head) {
    Node* current = head;
    float sum = 0.0;
    float count = 0.0;
    while (current) {
        sum += current->value;
        count++;
        current = current->next;
    }
    cout << "Average: " << sum / count << endl;
}

// 5. Swap nodes with the next one after a given value
void swapWithNext(Node*& head, int value) {
    Node* newNode = new Node;
    newNode->next = head;
    head = newNode;
    Node* current = head;

    while (current->next && current->next->value != value) {
        current = current->next;
    }

    if (!current->next) {
        cout << "Element not found: " << value << endl;
    } else {
        Node* second = current->next->next;
        Node* first = current->next;

        current->next = second;
        first->next = second->next;
        second->next = first;

        head = head->next;
        delete newNode;
    }
    displayList(head);
}

// 6. Delete every even node
void deleteEveryEvenNode(Node*& head) {
    Node* newNode = new Node;
    newNode->next = head;
    head = newNode;
    Node* current = head;

    while (current->next) {
        if (current->next->value % 2 == 0) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        } else {
            current = current->next;
        }
    }
    head = head->next;
    delete newNode;
    displayList(head);
}

// 7. Swap every other pair of nodes
void swapEveryOtherPair(Node*& head) {
    Node* newNode = new Node;
    newNode->next = head;
    head = newNode;
    Node* current = head;

    while (current->next && current->next->next) {
        Node* first = current->next;
        Node* second = current->next->next;
        Node* third = current->next->next->next;
        current->next = second;
        second->next = first;
        first->next = third;
        current = first;
    }
    head = head->next;
    delete newNode;
    displayList(head);
}

// Function to create a copy of the list in reverse order
void copyBackwards(Node* head) {
    if (head) {
        Node* reversedList = nullptr;
        Node* current = head;
        while (current->next) {
            addToFront(reversedList, current->value);
            current = current->next;
        }
        addToFront(reversedList, current->value);
        current->next = reversedList;
    }
}

//Divide the list into two separate lists
void divideList(Node*& head, Node*& secondList) {
    if (!head) {
        cout << "The list is empty" << endl;
    }
    Node* current = head;

    while (current && current->next) {
        Node* temp = current->next;
        current->next = temp->next;
        addNodeToFront(secondList, temp);
        current = current->next;
    }

    cout << "First List after division:" << endl;
    displayList(head);
    cout << "Second List after division:" << endl;
    displayList(secondList);
}

//Merge two sorted lists
void mergeLists(Node*& mergedList, Node*& list1, Node*& list2) {
    while (list1 && list2) {
        if (list1->value < list2->value) {
            Node* temp = list1;
            list1 = list1->next;
            addNodeToBack(mergedList, temp);
        } else {
            Node* temp = list2;
            list2 = list2->next;
            addNodeToBack(mergedList, temp);
        }
    }
    if (!list1) {
        while (list2) {
            Node* temp = list2;
            list2 = list2->next;
            addNodeToBack(mergedList, temp);
        }
    } else {
        while (list1) {
            Node* temp = list1;
            list1 = list1->next;
            addNodeToBack(mergedList, temp);
        }
    }
    cout << "Merged List:" << endl;
    displayList(mergedList);
}

void addElements(Node*& head) {
    addToBack(head, 1);
    addToBack(head, 2);
    addToBack(head, 4);
    addToBack(head, 5);
    addToBack(head, 7);
}

int main() {
    cout << "Initial List" << endl;
    Node* head = nullptr;
    addElements(head);
    displayList(head);

    cout << endl;
    cout << "Copy of the list" << endl;
    copyList(head);
    cout << endl;
    cout << "Duplicates in the list" << endl;
    duplicateNodes(head);
    cout << endl;
    cout << "Deleting every other node" << endl;
    deleteEveryOtherNode(head);
    cout << endl;
    cout << "Average of the list" << endl;
    calculateAverage(head);
    cout << endl;
    cout << "Swapping nodes based on value" << endl;
    swapWithNext(head, 4);
    cout << endl;
    cout << "Deleting even nodes" << endl;
    deleteEveryEvenNode(head);
    cout << endl;
    cout << "Swapping every other pair of nodes" << endl;
    swapEveryOtherPair(head);
    cout << endl;
    cout << "Copying the list backwards" << endl;
    copyBackwards(head);
    displayList(head);
    cout << endl;
    cout << "Dividing the list into two" << endl;
    Node* secondList = nullptr;
    divideList(head, secondList);
    cout << endl;
    cout << "Merging two lists" << endl;
    Node* mergedList = nullptr;
    Node* list1 = nullptr;
    addElements(list1);
    Node* list2 = nullptr;
    addElements(list2);
    mergeLists(mergedList, list1, list2);

    return 0;
}
