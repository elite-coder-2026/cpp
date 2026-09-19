#include <iostream>

bool isPrime(int n) {
    if (n <= 1)
        return false;

    for (int i = 2; i < n; i++) {
        if (n % i == 0)
            return false;
    }

    return true;
}

int main() {
    int n = 13;

    if (isPrime(n)) {
        std::cout << "true";
    } else {
        std::cout << "false";
    }

    return 0;
}
