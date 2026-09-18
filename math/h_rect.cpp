#include <iostream>

void printHollowRect(int n, int m) {
    int i, k;

    for (i = 1; i <= n; i++) {
        for (k = 1; k <= m; k++) {
            if (i == 1 || i == n || k == 1 || k == m) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
        }

        std::cout << std::endl;
    }
}

int main() {
    int n = 6, m = 20;
    printHollowRect(n, m);

    return 0;
}
