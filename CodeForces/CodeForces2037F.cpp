// problem statement: https://codeforces.com/problemset/problem/2037/F

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 5;

int T, n, m, k;
int h[MAXN], x[MAXN];
;

bool check(int res) {
    if (res == 0) { return false; }
    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++) {
        int power = (h[i] + res - 1) / res;
        if (power <= m) {
            int from = x[i] - (m - power);
            int to = x[i] + (m - power);
            v.emplace_back(from, 1);
            v.emplace_back(to + 1, -1);
        }
    }
    sort(v.begin(), v.end());
    int cnt = 0;
    for (auto [_, val] : v) {
        cnt += val;
        if (cnt >= k) { return true; }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin >> T;
    while (T--) {
        cin >> n >> m >> k;
        for (int i = 0; i < n; i++) { cin >> h[i]; }
        for (int i = 0; i < n; i++) { cin >> x[i]; }
        int l = 0, r = 1e9, ans = -1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (check(mid)) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
