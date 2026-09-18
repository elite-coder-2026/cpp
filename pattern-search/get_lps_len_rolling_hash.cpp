#include <iostream>
#include <vector>
#include <string>

int get_lps_len(std::string& s) {
    int a = 31, b = 37;

    int c = 1e9 + 7;
    int d = 1e9 + 9;

    int e = 1, f = 1;

    int n = s.size();

    std::vector<int> h(2, 0), _h(2, 0);
    int ans = 0;

    for (int i = 0; i < n - 1; i++) {
        h[0] = (h[0] + 1LL * (s[i] - 'a' + 1) * e % c) % c;
        h[1] = (h[1] + 1LL * (s[i] - 'a' + 1) * f % d) % d;

        _h[0] = (1LL * _h[0] * a % c + (s[n - i - 1] - 'a' + 1)) % c;
        _h[1] = (1LL * _h[1] * b % d + (s[n - i - 1] - 'a' + 1)) % d;

        if (h == _h) {
            ans = i + 1;
        }

        e = 1LL * e * a % c;
        f = 1LL * f * b % d;
    }

    return ans;
}

int main() {
    std::string s = "ababab";
    std::cout << get_lps_len(s) << std::endl;

    return 0;
}
