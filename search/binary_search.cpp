#include <iostream>
#include <vector>

int binary_search(std::vector<int>& arr, int low, int high, int target) {
    if (high >= low) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        }

        if (arr[mid] > target) {
            return binary_search(arr, low, mid - 1, target);
        }

        return binary_search(arr, mid + 1, high, target);
    }

    return -1;
}

int main() {
    std::vector<int> arr = {2, 3, 5, 10, 40};
    int query = 10;
    int n = arr.size();
    int result = binary_search(arr, 0, n - 1, query);

    if (result == -1) {
        std::cout << "Element not present in array";
    } else {
        std::cout << "Element is present at index" << result;
    }

    return 0;
}
