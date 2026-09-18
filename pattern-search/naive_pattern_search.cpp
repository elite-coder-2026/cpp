#include <iostream>
void search(std::string pat, std::string txt) {
    int m = pat.size();
    int n = txt.size();
    int i = 0;

    while (i <= n - m) {
        int k;

        for (k = 0; k < m; k++) {
            if (txt[i + k] != pat[k]) {
                break;
            }
        }

        if (k == m) {
            std::cout << "pattern found at index: "<< i << std::endl;
            i = i + m;
        } else if (k == 0) {
            i += 1;
        } else {
            i += k;
        }
    }
}

int main() {
    std::string txt = "ABCDEABCDABABCEABCD";
    std::string pat = "ABCD";

    search(pat, txt);

    return 0;
}
