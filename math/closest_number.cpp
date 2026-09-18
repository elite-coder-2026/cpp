#include <iostream>
#include <climits>

int closestNumber(int n, int m) {
    int closest = 0;
    int min_diff = INT_MAX;

    for (int i = n - abs(m); i <= n + abs(m); ++i) {
        if (i % m == 0) {
            int diff = abs(n - i);

            if (diff < min_diff || (diff == min_diff && abs(i) > abs(closest))) {
                closest = i;
                min_diff = diff;
            }
        }
    }

    return closest;
}

int main() {
    int n = 30, m = 4;
    std::cout << closestNumber(n, m) << std::endl;
    return 0;
}
