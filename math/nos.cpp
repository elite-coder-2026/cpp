#include <iostream>

void printNos(int n) {
    if (n == 0) {
        return;
    }

    printNos(n - 1);

    std::cout << n << "\n";
}

int main() {
    int n = 100;
    printNos(n);

    return 0;
}
