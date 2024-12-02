// problme statement: https://codeforces.com/contest/1194/problem/B

#include <bits/stdc++.h>

using namespace std;

int T, n, m;
vector<string> mp;
vector<int> cnt1, cnt2;

int main() {
    cin >> T;
    while (T--) {
        cin >> n >> m;
        mp.resize(n);
        for (int i = 0; i < n; i++) { cin >> mp[i]; }
        cnt1.clear();
        cnt2.clear();
        cnt1.resize(n);
        cnt2.resize(m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mp[i][j] == '*') cnt1[i]++;
            }
        }
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) {
                if (mp[i][j] == '*') cnt2[j]++;
            }
        }
        int ans = numeric_limits<int>::max();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mp[i][j] == '*') {
                    ans = min(ans, n - cnt1[i] + m - cnt2[j]);
                } else {
                    ans = min(ans, n - cnt1[i] + m - cnt2[j] - 1);
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
