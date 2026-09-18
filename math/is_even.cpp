#include <iostream>

bool isEven(int n) {
    int rem = n % 2;

    if (rem == 0)
        return true;
    else
        return false;
}

int main() {
    int n;

    std::cout << "enter a number: " << std::endl;
    std::cin >> n;

    if (isEven(n))
        std::cout << "true";

    else
        std::cout << "false";

    return 0;
}
