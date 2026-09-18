#include <iostream>
#include <vector>

int interpolation_search(const std::vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;

    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (arr[high] == arr[low]) {
            return (arr[low] == target) ? low : -1;
        }

        int pos = low + (long long)(target - arr[low]) * (high - low) / (arr[high] - arr[low]);

        if (arr[pos] == target) {
            return pos;
        }

        if (arr[pos] < target) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }

    return -1;
}

int main() {
    std::vector<int> arr = { 1, 3, 5, 7, 9, 11, 13, 15, 20, 25, 30 };
    std::cout << interpolation_search(arr, 20) << std::endl;

    return 0;
}
