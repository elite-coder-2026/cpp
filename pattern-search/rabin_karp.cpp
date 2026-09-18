#include <string>
#include <vector>
#include <iostream>
std::vector<int> search(const std::string& pat, const std::string& txt) {
    int d = 256;
    int q = 101;
    int m = pat.length();
    int n = txt.length();
    int p = 0;
    int t = 0;
    int h = 1;
    int i;

    std::vector<int> ans;

    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    for (int i = 0; i < m; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            bool match = true;
            for (int k = 0; k < m; k++) {
                if (txt[i + k] != pat[k]) {
                    match = false;
                    break;
                }
            }

            if (match)
                ans.push_back(i);
        }

        if (i < n - m) {
            t = (d * (t - txt[i] * h) + txt[i + m]) % q;

            if (t < 0)
                t += q;
        }
    }

    return ans;
}

int main() {
    std::string txt = "geeksforgeeks";
    std::string pat = "geeks";

    std::vector<int> res = search(pat, txt);

    for (auto it : res) {
        std::cout << it << " ";
    }

    std::cout << "\n";
    return 0;
}
