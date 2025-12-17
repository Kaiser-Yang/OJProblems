#include <bits/stdc++.h>

// https://www.cnblogs.com/jionkitten/p/12984866.html

using namespace std;

int T, n, m, g;

vector<vector<pair<int, int>>> p;
vector<int> opponent;
vector<vector<vector<vector<int>>>> dp[2];

template<class T0, class ...T>
bool same(T0 arg0, T ...args)
{
    T0 t[] = {arg0, args...};
    int len = sizeof(t) / sizeof(T0);
    for (int i = 0; i < len; i++) {
        if (t[i].first <= 0 || t[i].second == 0) { continue; }
        for (int j = i + 1; j < len; j++) {
            if (t[j].first <= 0 || t[j].second == 0) { continue; }
            if (p[opponent[t[i].first]][t[i].second].second == p[opponent[t[j].first]][t[j].second].second) { return true; }
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m >> g;
        p.resize(m + 1);
        for (int i = 0; i < m + 1; i++) { p[i].resize(n + 1); }
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> p[i][j].first;
                p[i][j].second = j;
            }
            sort(p[i].begin() + 1, p[i].end(), [] (const pair<int, int> &lhs, const pair<int, int> &rhs) {
                if (lhs.first != rhs.first) {
                    return lhs.first > rhs.first;
                }
                return lhs.second < rhs.second;
            });
        }
        g += 10;
        opponent.resize(g + 1);
        for (int i = 1; i <= g; i++) { cin >> opponent[i]; }
        int maxNum = min(10, n + 1);
        dp[0].clear();
        dp[1].clear();
        dp[0].resize(maxNum);
        dp[1].resize(maxNum);
        for (int a = 0; a < maxNum; a++) {
            dp[0][a].resize(maxNum);
            dp[1][a].resize(maxNum);
            for (int b = 0; b < maxNum; b++) {
                dp[0][a][b].resize(maxNum);
                dp[1][a][b].resize(maxNum);
                for (int c = 0; c < maxNum; c++) {
                    dp[0][a][b][c].resize(maxNum, 0);
                    dp[1][a][b][c].resize(maxNum, 0);
                }
            }
        }
        int now = 0, las = 1;
        for (int i = 1; i <= g; i++) {
            swap(now, las);
            for (int a = 0; a < maxNum; a++) {
                for (int b = 0; b < maxNum; b++) {
                    for (int c = 0; c < maxNum; c++) {
                        for (int d = 0; d < maxNum; d++) {
                            dp[now][a][b][c][d] = 0;
                        }
                    }
                }
            }
            for (int b = 0; b < maxNum; b++) {
                if (b == 0 && i - 1 >= 1 && opponent[i - 1] != 0) { continue; }
                if (b != 0 && (i - 1 <= 0 || opponent[i - 1] == 0)) { break; }
                for (int c = 0; c < maxNum; c++) {
                    if (c == 0 && i - 2 >= 1 && opponent[i - 2] != 0) { continue; }
                    if (c != 0 && (i - 2 <= 0 || opponent[i - 2] == 0)) { break; }
                    if (same(make_pair(i - 1, b), make_pair(i - 2, c))) { continue; }
                    for (int d = 0; d < maxNum; d++) {
                        if (d == 0 && i - 3 >= 1 && opponent[i - 3] != 0) { continue; }
                        if (d != 0 && (i - 3 <= 0 || opponent[i - 3] == 0)) { break; }
                        if (same(make_pair(i - 1, b), make_pair(i - 2, c), make_pair(i - 3, d))) { continue; }
                        for (int x = 0; x < maxNum; x++) {
                            if (x == 0 && i - 4 >= 1 && opponent[i - 4] != 0) { continue; }
                            if (x != 0 && (i - 4 <= 0 || opponent[i - 4] == 0)) { break; }
                            if (same(make_pair(i - 1, b), make_pair(i - 2, c), make_pair(i - 3, d), make_pair(i - 4, x))) { continue; }
                            if (opponent[i] != 0) {
                                for (int a = 1; a < maxNum; a++){
                                    if (same(make_pair(i - 1, b), make_pair(i - 2, c), make_pair(i - 3, d), make_pair(i - 4, x), make_pair(i, a))) { continue; }
                                    dp[now][a][b][c][d] = max(dp[now][a][b][c][d], dp[las][b][c][d][x] + p[opponent[i]][a].first);
                                }
                            } else {
                                dp[now][0][b][c][d] = max(dp[now][0][b][c][d], dp[las][b][c][d][x]);
                            }
                        }
                    }
                }
            }
        }
        int ans = 0;
        for (int a = 0; a < maxNum; a++) {
            for (int b = 0; b < maxNum; b++) {
                for (int c = 0; c < maxNum; c++) {
                    for (int d = 0; d < maxNum; d++) {
                        ans = max(ans, dp[now][a][b][c][d]);
                    }
                }
            }
        }
        cout << fixed << setprecision(2) << ans / 100.0 << endl;
    }
    return 0;
}
