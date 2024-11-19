// problem statement: https://codeforces.com/problemset/problem/2038/B

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;

int T, n;
int a[MAXN], b[MAXN];

bool check(int res) {
    for (int i = 0; i < n; i++) { b[i] = a[i] - res; }
    while (true) {
        bool finish = true;
        for (int i = 0; i < n; i++) {
            if (b[i] <= 0) { continue; }
            finish = false;
            int delta = (b[i] + 1) / 2;
            b[i] -= delta * 2;
            b[(i + 1) % n] += delta;
        }
        if (finish) { break; }
    }
    for (int i = 0; i < n; i++) {
        if (b[i] != 0) { return false; }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> a[i];
        int l = 0, r = 1e9, ans = -1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (check(mid)) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        if (ans == -1) {
            cout << -1 << '\n';
            continue;
        }
        cout << accumulate(a, a + n, 0LL) - 1LL * ans * n << '\n';
    }
    return 0;
}
