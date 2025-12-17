/*
    You are given a 0-1 string and an integer L. Your task is to found one section
whose length is equal or more than L and has the maximum average number.
*/
#include <bits/stdc++.h>

using namespace std;

int crossProduct(int i, int j, int k, int l, vector<int> &s) {
    return (j - i) * (s[l] - s[k]) - (s[j] - s[i]) * (l - k);
}

int main() {
    ios::sync_with_stdio(false);
    int T, n, l;
    string str;
    vector<int> s, p;
    cin >> T;
    while (T--) {
        cin >> n >> l >> str;
        s.resize(n);
        p.resize(n);
        s[0] = 0;
        for (int i = 1; i <= n; i++) { s[i] = s[i - 1] + str[i - 1] - '0'; }
        int i = 0, j = 0, left = 1, right = l;
        for (int r = l; r <= n; r++) {
            while (j - i >= 2 &&
                   crossProduct(p[j - 2] - 1, p[j - 1] - 1, p[j - 1] - 1, r - l, s) <= 0) {
                j--;
            }
            p[j++] = r - l + 1;
            while (j - i >= 2 && crossProduct(p[i] - 1, p[i + 1] - 1, p[i + 1] - 1, r, s) >= 0) {
                i++;
            }
            int c = crossProduct(left - 1, right, p[i] - 1, r, s);
            if (c > 0 || (c == 0 && r - p[i] < right - left)) {
                left = p[i];
                right = r;
            }
        }
        cout << left << " " << right << endl;
    }
    return 0;
}