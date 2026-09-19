#include <iostream>

bool check_kth_bit(int n, int k) {
    int val = (1 << k);

    if ((n & val) != 0) {
        return true;
    }

    return false;
}

int main() {
    int n = 7, k = 2;

    if (check_kth_bit(n, k))
        std::cout << "true" << std::endl;

    else
        std::cout << "false" << std::endl;

    return 0;
}
