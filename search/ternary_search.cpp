#include <iostream>
#include <vector>

int find_min_idx(std::vector<int>& arr) {
    int low = 0;
    int high = arr.size() - 1;
    int min_idx = -1;

    while (low <= high) {
        int left = low + (high - low) / 2;
        int right = high - (high - low) / 2;

        if (arr[left] == arr[right]) {
            low = left + 1;
            high = right - 1;

            min_idx = left;
        } else if (arr[left] < arr[right]) {
            high = right - 1;
            min_idx = left;
        } else {
            low = left + 1;
            min_idx = right;
        }
    }

    return min_idx;
}

int main() {
    std::vector<int> arr = { 9, 7, 1, 2, 3, 6, 10 };
    int idx = find_min_idx(arr);

    std::cout << idx << std::endl;

    return 0;
}
