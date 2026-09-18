#include <iostream>
#include <vector>
#include <string>

std::vector<int> z_fnc(std::string& s) {
    int n = s.length();
    std::vector<int> z(n);
    int l = 0, r = 0;

    for (int i = 1; i < n; i++) {
        if (i <= r) {
            int k = i - l;

            z[i] = std::min(r - i + 1, z[k]);
        }

        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }

        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    return z;
}

std::vector<int> search(std::string& text, std::string& pat) {
    std::string s = pat + '$' + text;
    std::vector<int> z = z_fnc(s);
    std::vector<int> pos;

    int m = pat.size();

    for (int i = m + 1; i < z.size(); i++) {
        if (z[i] == m) {
            pos.push_back(i - m - 1);
        }
    }

    return pos;
}

int main() {
    std::string txt = "aabxaabxaa";
    std::string pat = "aab";

    std::vector<int> matches = search(txt, pat);

    for (int pos : matches) {
        std::cout << pos << " ";
    }

    return 0;
}
