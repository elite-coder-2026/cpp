#include <iostream>
#include <vector>

std::vector<int> twoSum(std::vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;

    while (left < right) {
        int curr = arr[left] + arr[right];

        if (curr == target) {
            return { left + 1, right + 1 };
        } else if (curr < target) {
            left++;
        } else {
            right--;
        }
    }

    /// no pair sum with given target
    return { -1, -1 };
}

int main() {
    std::vector<int> arr = { 2, 7, 11, 15 };

    int target = 18;

    std::vector<int> result = twoSum(arr, target);

    for (int num : result) {
        std::cout << num << " ";
    }

    std::cout << std::endl;
    return 0;
}
