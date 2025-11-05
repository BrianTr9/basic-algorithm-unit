#include <iostream>
#include <vector>

// Hàm hoán đổi hai phần tử
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Hàm phân chia mảng và trả về chỉ số của chốt
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Chọn phần tử cuối cùng làm chốt
    int i = low - 1; // Chỉ số của phần tử nhỏ hơn chốt

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Hàm quick sort
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // Chỉ số của chốt

        // Đệ quy sắp xếp các phần tử trước và sau chốt
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};

    std::cout << "Array before sorting: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    quickSort(arr, 0, arr.size() - 1);

    std::cout << "Array after sorting: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}