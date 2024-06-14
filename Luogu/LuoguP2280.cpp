// problem statement: https://www.luogu.com.cn/problem/P2280

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXX = 5e3 + 10;
constexpr int MAXY = 5e3 + 10;

int n, m, x, y, v, ans;
array<array<int, MAXY>, MAXX> a;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> x >> y >> v;
        x++;
        y++;
        a[x][y] += v;
    }
    for (int i = 1; i < MAXX; i++) {
        for (int j = 1; j < MAXY; j++) { a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1]; }
    }
    for (int i = m; i < MAXX; i++) {
        for (int j = m; j < MAXY; j++) {
            ans = max(ans, a[i][j] - a[i - m][j] - a[i][j - m] + a[i - m][j - m]);
        }
    }
    cout << ans << "\n";
    return 0;
}
