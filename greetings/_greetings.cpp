#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

int main() {
    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;

    std::string lower_name = name;
    std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(),[](unsigned char c) { return std::tolower(c); });

    if (lower_name == "darrell") {
        std::cout << "hello, " << name << "! You are a great programmer," << std::endl;
    } else {
        std::cout << "hello, " << name << "!" << std::endl;
    }

    return 0;
}
