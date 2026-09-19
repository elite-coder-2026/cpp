#include <iostream>
using namespace std;

bool checkKthBit(int n, int k) {

    // Right shift n by k
    n = n >> k;

    // If 0th bit is set
    if ((n & 1) != 0) {
        return true;
    }

    return false;
}

int main() {
    int n = 7, k = 2;

    if (checkKthBit(n, k)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
    return 0;
}
