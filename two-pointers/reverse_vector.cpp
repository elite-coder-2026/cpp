#include <iostream>
#include <vector>

void reverseVector(std::vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;

    while (left < right) {
        std::swap(nums[left], nums[right]);
        ++left;
        --right;
    }
}

int main() {
    std::vector<int> nums = {10, 20, 30, 40, 50};
    reverseVector(nums);

    for (int n : nums)
        std::cout << n << " ";

    std::cout << std::endl;
    return 0;
}
