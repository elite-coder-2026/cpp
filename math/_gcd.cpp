#include <iostream>

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int a = 20, b = 28;

    std::cout << gcd(a, b);

    return 0;
}
