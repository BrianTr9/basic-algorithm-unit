#include <iostream>
#include <stdexcept>

/**
 * Singly Linked List
 * 
 * Concept: Nodes pointing to the next node.
 * - Add/Remove front: O(1)
 * - Add/Remove back: O(N) (without tracking a tail pointer)
 * - Access: O(N)
 */
template <typename T>
class SinglyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };

    Node* head;
    int count;

public:
    SinglyLinkedList() : head(nullptr), count(0) {}

    ~SinglyLinkedList() {
        Node* curr = head;
        while (curr != nullptr) {
            Node* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
    }

    // O(1)
    void addFront(T val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
        count++;
    }

    // O(N) Must traverse to end
    void addBack(T val) {
        if (head == nullptr) {
            addFront(val);
            return;
        }
        Node* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = new Node(val);
        count++;
    }

    // O(N)
    void addAt(int index, T val) {
        if (index < 0 || index > count) throw std::out_of_range("Index out of bounds");
        if (index == 0) {
            addFront(val);
            return;
        }
        
        Node* curr = head;
        for (int i = 0; i < index - 1; i++) {
            curr = curr->next;
        }
        Node* newNode = new Node(val);
        newNode->next = curr->next;
        curr->next = newNode;
        count++;
    }

    // O(1)
    T removeFront() {
        if (head == nullptr) throw std::out_of_range("List is empty");
        Node* temp = head;
        T val = temp->data;
        head = head->next;
        delete temp;
        count--;
        return val;
    }

    // O(N) Must traverse to find second to last
    T removeBack() {
        if (head == nullptr) throw std::out_of_range("List is empty");
        if (head->next == nullptr) return removeFront();

        Node* prev = nullptr;
        Node* curr = head;
        while (curr->next != nullptr) {
            prev = curr;
            curr = curr->next;
        }
        T val = curr->data;
        prev->next = nullptr;
        delete curr;
        count--;
        return val;
    }

    // O(N)
    T removeAt(int index) {
        if (index < 0 || index >= count) throw std::out_of_range("Index out of bounds");
        if (index == 0) return removeFront();

        Node* prev = nullptr;
        Node* curr = head;
        for (int i = 0; i < index; i++) {
            prev = curr;
            curr = curr->next;
        }
        T val = curr->data;
        prev->next = curr->next;
        delete curr;
        count--;
        return val;
    }

    int size() const { return count; }
    bool empty() const { return count == 0; }

    void print() const {
        Node* curr = head;
        std::cout << "SLL: ";
        while (curr != nullptr) {
            std::cout << curr->data << " -> ";
            curr = curr->next;
        }
        std::cout << "nullptr\n";
    }
};

int main() {
    SinglyLinkedList<int> sll;
    sll.addFront(10);
    sll.addBack(30);
    sll.addAt(1, 20);
    
    sll.print(); // Expected: 10 -> 20 -> 30 -> nullptr
    sll.removeBack();
    sll.print(); // Expected: 10 -> 20 -> nullptr
    return 0;
}
