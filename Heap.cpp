#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

template<class T>
class Heap {
protected:
    T* elements;
    int capacity;
    int count;
public:
    Heap()
    {
        this->capacity = 10;
        this->count = 0;
        this->elements = new T[capacity];
    }
    ~Heap()
    {
        delete[]elements;
    }
    void push(T item);
    
    bool isEmpty();
    bool contains(T item);
    T peek();
    bool pop();
    int size();
    
    void printHeap()
    {
        cout << "Max Heap [ ";
        for (int i = 0; i < count; i++)
            cout << elements[i] << " ";
        cout << "]\n";
    }
private:
    void ensureCapacity(int minCapacity);
    void reheapUp(int position);
    void reheapDown(int position);
};

template<class T>
void Heap<T>::ensureCapacity(int minCapacity) {
    if (minCapacity > capacity) {
        int newCapacity = max(capacity * 2, minCapacity);
        T* newElements = new T[newCapacity];
        for (int i = 0; i < count; i++) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
        capacity = newCapacity;
    }
}

template<class T>
void Heap<T>::reheapUp(int position) {
    if (position > 0) {
        int parent = (position - 1) / 2;
        if (elements[position] > elements[parent]) {
            swap(elements[position], elements[parent]);
            reheapUp(parent);
        }
    }
}

template<class T>
void Heap<T>::reheapDown(int position) {
    int leftChild = 2 * position + 1;
    int rightChild = 2 * position + 2;
    int largest = position;

    if (leftChild < count && elements[leftChild] > elements[largest]) {
        largest = leftChild;
    }
    if (rightChild < count && elements[rightChild] > elements[largest]) {
        largest = rightChild;
    }
    if (largest != position) {
        swap(elements[position], elements[largest]);
        reheapDown(largest);
    }
}

template<class T>
void Heap<T>::push(T item) {
    ensureCapacity(count + 1);
    elements[count] = item;
    reheapUp(count);
    count++;
}

template<class T>
bool Heap<T>::isEmpty() {
    return count == 0;
}

template<class T>
bool Heap<T>::contains(T item) {
    for (int i = 0; i < count; i++) {
        if (elements[i] == item) {
            return true;
        }
    }
    return false;
}

template<class T>
T Heap<T>::peek() {
    if (isEmpty()) {
        return -1;
    }
    return elements[0];
}

template<class T>
bool Heap<T>::pop() {
    if (isEmpty()) {
        return false;
    }
    elements[0] = elements[count - 1];
    count--;
    reheapDown(0);
    return true;
}

template<class T>
int Heap<T>::size() {
    return count;
}