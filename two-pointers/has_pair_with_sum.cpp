#include <ios>
#include <iostream>
#include <vector>

bool hasPairWithSum(std::vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    while (left < right) {
        int sum = nums[left] + nums[right];

        if (sum == target) {
            return true;
        } else if (sum < target) {
            ++left;
        } else {
            --right;
        }
    }

    return false;
}

int main() {
    std::vector<int> nums = { 1, 3, 5, 7, 9, 11 };
    int target = 35;

    std::cout << std::boolalpha << hasPairWithSum(nums, target) << std::endl;
}
