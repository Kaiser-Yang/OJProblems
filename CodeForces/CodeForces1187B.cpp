// problem statement: https://codeforces.com/contest/1187/problem/B

#include <bits/stdc++.h>

using namespace std;

int n, m;
string s, t;
vector<vector<int>> cnt1;
vector<int> cnt2;

bool check(int x) {
    for (int i = 0; i < 26; i++) {
        if (cnt2[i] > cnt1[x - 1][i]) { return false; }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> s;
    cnt1.resize(n, vector<int>(26));
    for (int i = 0; i < n; i++) {
        cnt1[i][s[i] - 'a']++;
        for (int j = 0; j < 26; j++) {
            if (i - 1 >= 0) { cnt1[i][j] += cnt1[i - 1][j]; }
        }
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> t;
        cnt2.clear();
        cnt2.resize(26);
        for (auto &&ch : t) { cnt2[ch - 'a']++; }
        int l = 1, r = n;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << l << '\n';
    }
    return 0;
}
