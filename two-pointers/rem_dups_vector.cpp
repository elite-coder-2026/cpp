#include <iostream>
#include <vector>

int remove_dup_vec(std::vector<int>& nums) {
    if (nums.empty())
        return 0;

    int slow = 0;

    for (int fast = 1; fast < nums.size(); ++fast) {
        if (nums[fast] != nums[slow]) {
            ++slow;
            nums[slow] = nums[fast];
        }
    }

    return slow + 1;
}

int main() {
    std::vector<int> nums = { 1, 1, 2, 2, 2, 2, 3, 4, 4 };
    int newLength = remove_dup_vec(nums);

    for (int i = 0; i < newLength; ++i)
        std::cout << nums[i] << " ";


    std::cout << std::endl;
    return 0;
}
