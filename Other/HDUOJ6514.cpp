// problem statement: https://acm.hdu.edu.cn/showproblem.php?pid=6514

#include <bits/stdc++.h>

using namespace std;

int n, m, p, q, a1, b1, a2, b2;
vector<vector<int>> a;

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> m) {
        vector<vector<int>>().swap(a);
        a.resize(n + 2, vector<int>(m + 2));
        cin >> p;
        for (int i = 0; i < p; i++) {
            cin >> a1 >> b1 >> a2 >> b2;
            a[a1][b1]++;
            a[a1][b2 + 1]--;
            a[a2 + 1][b1]--;
            a[a2 + 1][b2 + 1]++;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) { a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1]; }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (a[i][j] > 1) { a[i][j] = 1; }
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) { a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1]; }
        }
        cin >> q;
        for (int i = 0; i < q; i++) {
            cin >> a1 >> b1 >> a2 >> b2;
            if (a[a2][b2] - a[a1 - 1][b2] - a[a2][b1 - 1] + a[a1 - 1][b1 - 1] ==
                (b2 - b1 + 1) * (a2 - a1 + 1)) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
    return 0;
}
