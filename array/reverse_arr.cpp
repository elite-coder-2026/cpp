#include <iostream>

void reverseArray(int arr[], int size) {
    int left = 0;
    int right = size - 1;

    while (left < right) {
        std::swap(arr[left], arr[right]);
        ++left;
        --right;
    }
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);

    reverseArray(arr, size);

    for (int i = 0; i < size; ++i)
        std::cout << arr[i] << " ";

    std::cout << std::endl;
    return 0;
}
