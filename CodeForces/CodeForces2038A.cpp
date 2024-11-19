// problem statement: https://codeforces.com/problemset/problem/2038/A

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 5;

int n, k;
int a[MAXN], b[MAXN], sum[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin >> n >> k;
    for (int i = 0; i < n; i++) { cin >> a[i]; }
    for (int i = 0; i < n; i++) { cin >> b[i]; }
    for (int i = n - 1; i >= 0; i--) { sum[i] = sum[i + 1] + a[i] / b[i]; }
    if (sum[0] < k) {
        for (int i = 0; i < n; i++) { cout << 0 << (i == n - 1 ? '\n' : ' '); }
        return 0;
    }
    for (int i = 0; i < n; i++) {
        cout << max(0, k - sum[i + 1]) << (i == n - 1 ? '\n' : ' ');
        if (k > sum[i + 1]) { k -= k - sum[i + 1]; }
    }
    return 0;
}
