#include <iostream>
#include <stdexcept>

/**
 * ArrayList (Dynamic Array)
 * 
 * Concept: Array that resizes itself by doubling capacity when full.
 * - Random Access: O(1)
 * - Add/Remove at back: O(1) amortized
 * - Add/Remove at front or middle: O(N) due to shifting
 */
template <typename T>
class ArrayList {
private:
    T* data;
    int capacity;
    int count;

    void resize() {
        capacity *= 2;
        T* newData = new T[capacity];
        for (int i = 0; i < count; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    ArrayList(int initCapacity = 10) : capacity(initCapacity), count(0) {
        data = new T[capacity];
    }

    ~ArrayList() {
        delete[] data;
    }

    // O(N)
    void addFront(T val) {
        addAt(0, val);
    }

    // O(1) Amortized
    void addBack(T val) {
        if (count == capacity) resize();
        data[count++] = val;
    }

    // O(N) Shifting right
    void addAt(int index, T val) {
        if (index < 0 || index > count) throw std::out_of_range("Index out of bounds");
        if (count == capacity) resize();
        for (int i = count; i > index; i--) {
            data[i] = data[i - 1];
        }
        data[index] = val;
        count++;
    }

    // O(N)
    T removeFront() {
        return removeAt(0);
    }

    // O(1)
    T removeBack() {
        if (count == 0) throw std::out_of_range("List is empty");
        count--;
        return data[count];
    }

    // O(N) Shifting left
    T removeAt(int index) {
        if (index < 0 || index >= count) throw std::out_of_range("Index out of bounds");
        T val = data[index];
        for (int i = index; i < count - 1; i++) {
            data[i] = data[i + 1];
        }
        count--;
        return val;
    }

    // O(1)
    T& get(int index) const {
        if (index < 0 || index >= count) throw std::out_of_range("Index out of bounds");
        return data[index];
    }

    int size() const { return count; }
    bool empty() const { return count == 0; }

    void print() const {
        std::cout << "ArrayList: [";
        for(int i = 0; i < count; i++) {
            std::cout << data[i] << (i < count - 1 ? ", " : "");
        }
        std::cout << "]\n";
    }
};

int main() {
    ArrayList<int> list;
    list.addBack(10);
    list.addBack(30);
    list.addAt(1, 20);
    
    list.print(); // Expected: [10, 20, 30]
    list.removeBack();
    list.print(); // Expected: [10, 20]
    return 0;
}
