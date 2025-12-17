#include <bits/stdc++.h>

using namespace std;

int n;
int d[10001][10001][2];
vector<pair<int, int>> x;
constexpr int INF = numeric_limits<int>::max() / 10;

int dis(int i, int j)
{
    return abs(x[i].first - x[j].first);
}

int main()
{
    ios::sync_with_stdio(false);
    while (cin >> n) {
        x.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> x[i].first >> x[i].second;
        }
        for (int i = 1; i <= n; i++) {
            d[i][i][0] = d[i][i][1] = 0;
        }
        for (int l = n - 1; l >= 1; l--) {
            for (int r = l + 1; r <= n; r++) {
                d[l][r][0] = min(d[l + 1][r][0] + dis(l + 1, l), d[l + 1][r][1] + dis(r, l));
                if (d[l][r][0] >= x[l].second) { d[l][r][0] = INF; }
                d[l][r][1] = min(d[l][r - 1][0] + dis(l, r), d[l][r - 1][1] + dis(r - 1, r));
                if (d[l][r][1] >= x[r].second) { d[l][r][1] = INF; }
            }
        }
        int ans = min(d[1][n][0], d[1][n][1]);
        if (ans >= INF) { cout << "No solution\n"; }
        else { cout << ans << endl; }

    }
    return 0;
}