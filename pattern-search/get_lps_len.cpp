#include <iostream>
#include <vector>
#include <string>

int get_lps_length(std::string& s) {
    int n = s.size();
    std::vector<int> lps(n, 0);
    int len = 0;
    int i = 1;

    while (i < n) {
        if (s[i] == s[len]) {
            lps[i] = ++len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps[n - 1];
}

int main() {
    std::string s = "ababab";
    std::cout << get_lps_length(s);

    return 0;
}
