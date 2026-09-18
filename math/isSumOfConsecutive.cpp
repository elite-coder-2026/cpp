#include <iostream>

bool isSubOfConsecutive(int n) {
    if (n == 1)
        return false;

    if ((n & (n - 1)) == 0) {
        return false;
    }

    return true;
}

int main() {
    int n = 3;
    if (isSubOfConsecutive(n)) {
        std::cout << "true";
    } else {
        std::cout << "false";
    }

    return 0;
}
