// problem statement: https://www.luogu.com.cn/problem/P1387

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 110;
constexpr int MAXM = 110;

int N, M, ans;
int grid[MAXN][MAXM];
int l[MAXN][MAXM], r[MAXN][MAXM], u[MAXN][MAXM];

int main()
{
    ios::sync_with_stdio(false);
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> grid[i][j];
        }
    }
    for (int j = 1; j <= M; j++) {
        u[0][j] = 1;
    }
    for (int i = 1; i <= N; i++) {
        l[i][0] = 1;
        r[i][M + 1] = M;
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (grid[i][j] == 0) {
                l[i][j] = j + 1;
            } else {
                l[i][j] = l[i][j - 1];
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = M; j >= 1; j--) {
            if (grid[i][j] == 0) {
                r[i][j] = j - 1;
            } else {
                r[i][j] = r[i][j + 1];
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (grid[i][j] == 1) {
                u[i][j] = u[i - 1][j];
            } else {
                u[i][j] = i + 1;
            }
            if (u[i][j] < i) {
                l[i][j] = max(l[i][j], l[i - 1][j]);
                r[i][j] = min(r[i][j], r[i - 1][j]);
            }
            int len1 = i - u[i][j] + 1;
            int len2 = r[i][j] - l[i][j] + 1;
            int len = min(len1, len2);
            ans = max(ans, len);
        }
    }
    cout << ans << endl;
    return 0;
}
