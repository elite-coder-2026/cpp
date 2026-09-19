#include <algorithm>

typedef long long int ll;
ll X[200005], Y[200005];


void calc_subarr(ll a[], ll x[], int n, int c) {
    for (int i = 0; i < (1 << n); i++) {
        ll s = 0;

        for (int k = 0; k < n; k++) {
            if (i & (1 << k)) {
                s += a[k + c];
            }
        }

        x[i] = s;
    }
}

ll solve_subset_sum(ll a[], int n, ll S) {
    calc_subarr(a, X, n / 2, 0);
    calc_subarr(a, Y, n - n / 2, n / 2);

    int size_x = 1 << (n / 2);
    int size_y = 1 << (n - n/2);

    std::sort(Y, Y + size_y);

    ll max = 0;

    for (int i = 0; i < size_x; i++) {
        if (X[i] <= S) {
            int p = std::lower_bound(Y, Y + size_y, S - X[i]) - Y;

            if (p == size_y || Y[p] != (S - X[i]))
                p--;

            if ((Y[p] + X[i]) > max)
                max = Y[p] + X[i];
        }
    }

    return max;
}

int main() {
    ll a[] = { 3, 34, 4, 12, 4, 2 };
    int n = sizeof(a) / sizeof(a[0]);
    ll S = 10;

    printf("Largest value smaller than or equal to given "
        "sum is %lld\n", solve_subset_sum(a, n, S));

    return 0;
}
