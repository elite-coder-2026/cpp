#include <iostream>




int gcd(int a, int b) {
    if (a == 0)
        return b;

    if (b == 0)
        return a;

    if (a > b) {
        if (a % b == 0) {
            return b;
        }

        return gcd(a - b, b);
    }

    if (b % a == 0)
        return a;

    return gcd(a, b - a);
}

int main() {
    int a = 28, b = 30;
    std::cout << gcd(a, b);

    return 0;
}
