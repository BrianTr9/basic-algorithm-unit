#include <iostream>
#include <vector>

void shellSort(std::vector<int>& arr) {
    int n = arr.size();

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

int main() {
    std::vector<int> arr = {23, 12, 1, 8, 34, 54, 2, 3};

    std::cout << "Array before sorting: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    shellSort(arr);

    std::cout << "Array after sorting: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}