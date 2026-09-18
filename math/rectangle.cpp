#include <iostream>
int main() {
    int n = 4, m = 2;

    for (int i = 1; i <= n; i++) {
        for (int k = 1; k <= m; k++) {
            std::cout << "* ";
        }

        std::cout << "\n";
    }

    return 0;
}
