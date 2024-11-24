// problem statement: https://codeforces.com/contest/2039/problem/D

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;

int T, n, m;
int cnt[MAXN];

int main() {
    ios::sync_with_stdio(0);
    for (int i = 2; i < MAXN; i++) {
        if (cnt[i]) { continue; }
        for (int j = i; j < MAXN; j += i) {
            int tmp = j;
            while (tmp % i == 0) {
                tmp /= i;
                cnt[j]++;
            }
        }
    }
    cin >> T;
    while (T--) {
        cin >> n >> m;
        vector<int> a(m + 1);
        for (int i = 1; i <= m; i++) { cin >> a[i]; }
        bool fail = false;
        for (int i = 1; i <= n; i++) {
            if (m <= cnt[i]) { fail = true; }
        }
        if (fail) {
            cout << "-1\n";
        } else {
            for (int i = 1; i <= n; i++) { cout << a[m - cnt[i]] << " \n"[i == n]; }
        }
    }
    return 0;
}
