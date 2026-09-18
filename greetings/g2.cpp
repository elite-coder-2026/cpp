#include <iostream>
#include <string>

int main() {
    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;

    if (name == "Darrell") {
        std::cout << "Hello, Darrell you are a great programmer" << std::endl;

    } else {
        std::cout << "Hello, " << name << "!" << std::endl;
    }


    return 0;
}
