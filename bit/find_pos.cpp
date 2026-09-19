#include <iostream>

int findPos(int n) {
    if (n == 0 || (n & (n - 1)) != 0) {
        return -1;
    }

    int pos = 1;
    int val = 1;

    while ((val & n) == 0) {
        val = val << 1;
        pos++;
    }

    return pos;
}

int main() {
    int n = 4096;
    std::cout << findPos(n);

    return 0;
}
