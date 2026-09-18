#include <iostream>

void printFloydsTriangle(int n) {
    int i, k, val = 1;

    for (i = 1; i <= n; i++) {
        for (k = 1; k <= i; k++) {
            std::cout << val++ << " ";
        }


        std::cout << std::endl;
    }
}

int main() {
    printFloydsTriangle(6);
    return 0;
}
