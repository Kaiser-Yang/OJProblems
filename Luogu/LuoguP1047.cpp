// probleb statement: https://www.luogu.com.cn/problem/P1047

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e4 + 10;

int n, m, l, r, ans;
int sum[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> l >> r;
        sum[l]--;
        sum[r + 1]++;
    }
    for (int i = 0; i <= n; i++) {
        sum[i] += sum[i - 1];
        if (sum[i] >= 0) { ans++; }
    }
    cout << ans << endl;
    return 0;
}
