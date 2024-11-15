// problem statement: https://www.luogu.com.cn/problem/P3392

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 51;

int n, m, ans = numeric_limits<int>::max();
string grid[MAXN];

int getAns(int a, int b, int c) {
    assert(a >= 1);
    assert(b >= 1);
    assert(c >= 1);
    assert(a + b + c == n);
    int res = 0;
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != 'W') { res++; }
        }
    }
    for (int i = a; i < a + b; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != 'B') { res++; }
        }
    }
    for (int i = a + b; i < a + b + c; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != 'R') { res++; }
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < n; i++) { cin >> grid[i]; }
    for (int i = 1; i <= n - 2; i++) {
        for (int j = 1; i + j + 1 <= n; j++) {
            int k = n - i - j;
            ans = min(ans, getAns(i, j, k));
        }
    }
    cout << ans << endl;
    return 0;
}
