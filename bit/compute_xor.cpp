#include <cstdio>

int computeXOR(int n) {
    if (n % 4 == 0)
        return n;

    if (n % 4 == 1)
        return 1;

    if (n % 4 == 2)
        return n + 1;

    else
        return 0;
}

// Brute-force reference, just to sanity-check computeXOR against
int bruteForceXOR(int n) {
    int result = 0;
    for (int i = 1; i <= n; i++) {
        result ^= i;
    }
    return result;
}

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    int fast = computeXOR(n);
    int slow = bruteForceXOR(n);

    printf("XOR of 1 to %d = %d\n", n, fast);

    if (fast != slow) {
        printf("MISMATCH: brute force gives %d\n", slow);
    }

    return 0;
}
