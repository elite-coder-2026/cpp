#include <iostream>
#include <vector>

int search(std::vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++)
        if (arr[i] == target)
            return i;
    return -1;
}

int main() {
    std::vector<int> arr = { 2, 3, 5, 10, 40 };
    int x = 14;
    int res = search(arr, x);

    if (res == -1) {
        std::cout << "Element not present in the array";
    } else {
        std::cout << "Element is present at index " << res;
    }

    return 0;
}
