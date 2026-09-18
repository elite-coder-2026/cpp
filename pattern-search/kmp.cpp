#include <iostream>
#include <string>
#include <vector>

void construct_lps(std::string& pat, std::vector<int>& lps) {
    int len = 0;
    lps[0] = 0;
    int i = 1;

    while (i < pat.length()) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
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
}

std::vector<int> search(std::string& pat, std::string& txt) {
    int n = txt.length();
    int m = pat.length();

    std::vector<int> lps(m);
    std::vector<int> res;

    construct_lps(pat, lps);

    int i = 0;
    int k = 0;

    while (i < n) {
        if (txt[i] == pat[k]) {
            i++;
            k++;

            if (k == m) {
                res.push_back(i - k);
                k = lps[k - 1];
            }
        } else {
            if (k != 0) {
                k = lps[k - 1];
            } else {
                i++;
            }
        }
    }

    return res;
}

int main() {
    std::string txt = "ABCDEABCDABABCEABCD";
    std::string pat = "ABCD";

    std::vector<int> res = search(pat, txt);

    for (int i = 0; i < res.size(); i++)
        std::cout << res[i] << " ";

    return 0;
}
