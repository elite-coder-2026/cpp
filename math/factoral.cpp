#include <iostream>

int factoral(int n) {
    int ans = 1;

    for (int i = 2; i <= n; i++) {
        ans = ans * i;
    }

    return ans;
}

int main() {
    int num = 10;
    std::cout << factoral(num) << std::endl;

    return 0;
}
