#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    string s;
    vector<vector<string>> d;
    while (cin >> s) {
        int n = s.length();
        d.resize(n);
        for (int i = 0; i < n; i++) {
            d[i].resize(n);
            d[i][i] = s[i];
        }
        for (int l = n - 1; l >= 0; l--) {
            for (int r = l + 1; r < n; r++) {
                d[l][r] = s.substr(l, r - l + 1);
                size_t len = 0;
                for (int i = 1; i < r - l + 1; i++) {
                    if ((r - l + 1) % i != 0) { continue; }
                    for (int j = i; j < r - l + 1; j++) {
                        if (d[l][r][j] != d[l][r][j % i]) { break; }
                        if (j == r - l) {
                            len = i;
                            break;
                        }
                    }
                    if (len != 0) { break; }
                }
                if (len != 0) {
                    string &&num = to_string((r - l + 1) / len);
                    if (2 + len + num.size() < r - l + 1) {
                        d[l][r] = num + "(" + d[l][l + len - 1] + ")";
                    }
                }
                len = d[l][r].size();
                int pos = -1;
                for (int k = l; k < r; k++) {
                    if (len > d[l][k].size() + d[k + 1][r].size()) {
                        len = d[l][k].size() + d[k + 1][r].size();
                        pos = k;
                    }
                }
                if (pos != -1) { d[l][r] = d[l][pos] + d[pos + 1][r]; }
            }
        }
        cout << d[0][n - 1] << endl;
    }
    return 0;
}