#include <iostream>

void pymarid(int n) {
    for (int i = 1; i <= n; i++) {
        for (int k = 1; k <= n - i; k++) {
            std::cout << " ";
        }

        for (int k = 1; k <= 2 * i - 1; k++) {
            std::cout << "*";
        }

        std::cout << std::endl;
    }
}

int main() {
    int n = 7;
    pymarid(n);

    return 0;
}
