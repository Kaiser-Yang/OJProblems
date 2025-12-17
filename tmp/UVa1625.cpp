#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int T;
    string s, t;
    vector<int> ss, st, es, et;
    vector<vector<int>> dp;
    cin >> T;
    while (T--) {
        ss.clear();
        st.clear();
        es.clear();
        et.clear();
        dp.clear();
        cin >> s >> t;
        int n = s.length(), m = t.length();
        ss.resize(26, n);
        st.resize(26, m);
        es.resize(26, -1);
        et.resize(26, -1);
        dp.resize(n + 1);
        for (int i = 0; i <= n; i++) { dp[i].resize(m + 1); }
        for (int i = 0; i < n; i++) {
            ss[s[i] - 'A'] = min(ss[s[i] - 'A'], i);
            es[s[i] - 'A'] = max(es[s[i] - 'A'], i);
        }
        for (int i = 0; i < m; i++) {
            st[t[i] - 'A'] = min(st[t[i] - 'A'], i);
            et[t[i] - 'A'] = max(et[t[i] - 'A'], i);
        }
        for (int i = n; i >= 0; i--) {
            for (int j = m; j >= 0; j--) {
                int cost = 0;
                for (int c = 0; c < 26; c++) {
                    if ((ss[c] < i || st[c] < j) && (es[c] >= i || et[c] >= j)) { cost++; }
                }
                if (i == n) {
                    if (j == m) {
                        dp[i][j] = 0;
                    } else {
                        dp[i][j] = dp[i][j + 1] + cost;
                    }
                } else if (j == m) {
                    dp[i][j] = dp[i + 1][j] + cost;
                } else {
                    dp[i][j] = min(dp[i + 1][j], dp[i][j + 1]) + cost;
                }
            }
        }
        cout << dp[0][0] << endl;
    }
    return 0;
}
