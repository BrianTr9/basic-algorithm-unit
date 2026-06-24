#include <iostream>
#include <stdexcept>

/**
 * Doubly Linked List
 * 
 * Concept: Nodes pointing both next and prev. Uses dummy head/tail nodes.
 * - Add/Remove front: O(1)
 * - Add/Remove back: O(1)
 * - Pointer bypass deletion: O(1) (Essential for LRU cache!)
 */
template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(T val) : data(val), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int count;

public:
    DoublyLinkedList() {
        head = new Node(T()); // Dummy Head
        tail = new Node(T()); // Dummy Tail
        head->next = tail;
        tail->prev = head;
        count = 0;
    }

    ~DoublyLinkedList() {
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
        Node* firstNode = head->next;

        head->next = newNode;
        newNode->prev = head;
        newNode->next = firstNode;
        firstNode->prev = newNode;

        count++;
    }

    // O(1)
    void addBack(T val) {
        Node* newNode = new Node(val);
        Node* lastNode = tail->prev;

        lastNode->next = newNode;
        newNode->prev = lastNode;
        newNode->next = tail;
        tail->prev = newNode;

        count++;
    }

    // O(N) Traversal to find index
    void addAt(int index, T val) {
        if (index < 0 || index > count) throw std::out_of_range("Index out of bounds");
        Node* curr = head->next;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        
        Node* newNode = new Node(val);
        Node* prevNode = curr->prev;

        prevNode->next = newNode;
        newNode->prev = prevNode;
        newNode->next = curr;
        curr->prev = newNode;
        
        count++;
    }

    // O(1)
    T removeFront() {
        if (empty()) throw std::out_of_range("List is empty");
        Node* target = head->next;
        T val = target->data;
        
        head->next = target->next;
        target->next->prev = head;
        delete target;
        count--;
        return val;
    }

    // O(1)
    T removeBack() {
        if (empty()) throw std::out_of_range("List is empty");
        Node* target = tail->prev;
        T val = target->data;

        target->prev->next = tail;
        tail->prev = target->prev;
        delete target;
        count--;
        return val;
    }

    // O(N) Traversal to find index, O(1) Deletion
    T removeAt(int index) {
        if (index < 0 || index >= count) throw std::out_of_range("Index out of bounds");
        
        Node* curr = head->next;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }

        // Pointer bypass
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;

        T val = curr->data;
        delete curr;
        count--;
        return val;
    }

    int size() const { return count; }
    bool empty() const { return count == 0; }

    void print() const {
        Node* curr = head->next;
        std::cout << "DLL: ";
        while (curr != tail) {
            std::cout << curr->data << " <-> ";
            curr = curr->next;
        }
        std::cout << "nullptr\n";
    }
};

int main() {
    DoublyLinkedList<int> dll;
    dll.addFront(10);
    dll.addBack(30);
    dll.addAt(1, 20);
    
    dll.print(); // Expected: 10 <-> 20 <-> 30 <-> nullptr
    dll.removeBack();
    dll.print(); // Expected: 10 <-> 20 <-> nullptr
    
    return 0;
}
