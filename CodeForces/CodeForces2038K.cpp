// problem statement: https://codeforces.com/problemset/problem/2038/K

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 10;

int n;
long long a, b, ans;
long long sum_a[MAXN], sum_b[MAXN];
vector<int> seq_a[MAXN], seq_b[MAXN], na, nb;

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    ios::sync_with_stdio(0);
    cin >> n >> a >> b;
    for (int i = 1; i <= n; i++) {
        sum_a[i] = sum_a[i - 1] + gcd(i, a);
        sum_b[i] = sum_b[i - 1] + gcd(i, b);
        seq_a[gcd(i, a)].push_back(i);
        seq_b[gcd(i, b)].push_back(i);
    }
    for (int i = 1; i <= a; i++) {
        if (seq_a[i].empty()) { continue; }
        na.push_back(seq_a[i][0]);
        na.push_back(seq_a[i].back());
    }
    for (int i = 1; i <= b; i++) {
        if (seq_b[i].empty()) { continue; }
        nb.push_back(seq_b[i][0]);
        nb.push_back(seq_b[i].back());
    }
    sort(na.begin(), na.end());
    sort(nb.begin(), nb.end());
    na.erase(unique(na.begin(), na.end()), na.end());
    nb.erase(unique(nb.begin(), nb.end()), nb.end());
    vector<vector<long long>> dp(na.size(), vector<long long>(nb.size(), numeric_limits<long long>::max()));
    dp[0][0] = 2;
    for (int i = 0; i < na.size(); i++) {
        for (int j = 0; j < nb.size(); j++) {
            if (i > 0) {
                dp[i][j] = dp[i - 1][j] + sum_a[na[i]] - sum_a[na[i - 1]] + gcd(nb[j], b) * (na[i] - na[i - 1]);
            }
            if (j > 0) {
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + sum_b[nb[j]] - sum_b[nb[j - 1]] + gcd(na[i], a) * (nb[j] - nb[j - 1]));
            }
        }
    }
    cout << dp[na.size() - 1][nb.size() - 1] << '\n';
    return 0;
}
