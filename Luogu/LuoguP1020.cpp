// problem statement:

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;

int a[MAXN], dp[MAXN];

int main() {
    ios::sync_with_stdio(false);
    int n = 0, temp = 0;
    while (cin >> temp) { a[n++] = temp; }
    if (n == 0) {
        cout << "0\n0\n";
        return 0;
    }
    int len   = 0;
    dp[++len] = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] <= dp[len]) {
            dp[++len] = a[i];
        } else {
            dp[upper_bound(dp + 1, dp + len + 1, a[i], greater<int>()) - dp] = a[i];
        }
    }
    cout << len << endl;
    len       = 0;
    dp[++len] = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > dp[len]) {
            dp[++len] = a[i];
        } else {
            dp[lower_bound(dp + 1, dp + len + 1, a[i]) - dp] = a[i];
        }
    }
    cout << len << endl;
    return 0;
}