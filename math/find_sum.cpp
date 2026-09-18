#include <iostream>

int findSum(int n) {
    int sum = 0;
    for (int i = 0; i <= n; i++) {
        sum = sum + i;
    }

    return sum;
}

int main() {
    int n = 5;
    std::cout << findSum(n);
    return 0;
}
