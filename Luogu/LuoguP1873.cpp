// problem statement: https://www.luogu.com.cn/problem/P1873

#include <bits/stdc++.h>

constexpr int MAXN = 1e6 + 10;

using namespace std;

int n, m, l, r, ans;
array<int, MAXN> a;

bool check(int ans) {
    long long tot = 0;
    for (int i = 0; i < n; i++) { tot += a[i] > ans ? a[i] - ans : 0; }
    return tot >= m;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        r = max(r, a[i]);
    }
    while (l <= r) {
        int mid = l + ((r - l) >> 1);
        if (check(mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans << endl;
    return 0;
}
