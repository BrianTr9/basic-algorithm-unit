#include <iostream>

// Node structure for linked list
struct Node {
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};

// Stack implementation using linked list
class Stack {
private:
    Node* top;
public:
    Stack() : top(nullptr) {}

    void push(int data) {
        Node* newNode = new Node(data);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (top == nullptr) {
            std::cout << "Stack is empty\n";
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    int peek() {
        if (top == nullptr) {
            std::cout << "Stack is empty\n";
            return -1;
        }
        return top->data;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    ~Stack() {
        while (top != nullptr) {
            pop();
        }
    }
};

// Queue implementation using linked list
class Queue {
private:
    Node* front;
    Node* rear;
public:
    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(int data) {
        Node* newNode = new Node(data);
        if (rear == nullptr) {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    void dequeue() {
        if (front == nullptr) {
            std::cout << "Queue is empty\n";
            return;
        }
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
    }

    int peek() {
        if (front == nullptr) {
            std::cout << "Queue is empty\n";
            return -1;
        }
        return front->data;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    ~Queue() {
        while (front != nullptr) {
            dequeue();
        }
    }
};

int main() {
    // Stack usage example
    Stack stack;
    stack.push(10);
    stack.push(20);
    std::cout << "Stack top: " << stack.peek() << std::endl;
    stack.pop();
    std::cout << "Stack top after pop: " << stack.peek() << std::endl;

    // Queue usage example
    Queue queue;
    queue.enqueue(30);
    queue.enqueue(40);
    std::cout << "Queue front: " << queue.peek() << std::endl;
    queue.dequeue();
    std::cout << "Queue front after dequeue: " << queue.peek() << std::endl;

    return 0;
}