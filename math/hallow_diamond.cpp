#include <iostream>

int main() {
    int n = 7;

    for (int i = 0; i < 2 * n - 1; i++) {
        int comp;

        if (i < n)
            comp = 2 * (n - i) - 1;

        else
            comp = 2 * (i - n + 1) + 1;

        for (int k = 1; k < comp; k++)
            std::cout << " ";

        for (int k = 0; k < 2 * n - comp; k++) {
            if (k == 0 || k < 2 * n - comp - 1)
                std::cout << "* ";
            else
                std::cout << " ";
        }

        std::cout << std::endl;
    }

    return 0;
}
