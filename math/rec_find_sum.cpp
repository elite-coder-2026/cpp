#include <iostream>

int rec_find_sum(int n) {
    if (n == 1) {
        return 1;
    }

    return n + rec_find_sum(n - 1);
}

int main() {
    int n = 5;
    std::cout << rec_find_sum(n);

    return 0;
}
