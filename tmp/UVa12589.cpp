#include <bits/stdc++.h>

using namespace std;

int T, n, m;
vector<pair<int, int>> p;
vector<vector<vector<int>>> d;
const double PI = acos(-1.0);

int main()
{
    ios::sync_with_stdio(false);
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> n >> m;
        p.resize(n);
        int totHeight = 0;
        for (int i = 0; i < n; i++) {
            cin >> p[i].first >> p[i].second;
            totHeight += p[i].second;
        }
        sort(p.begin(), p.end(), [] (const pair<int, int> &lhs, const pair<int, int> &rhs) {
            double thelta1 = atan2(lhs.second, lhs.first);
            double thelta2 = atan2(rhs.second, rhs.first);
            if (thelta1 != thelta2) {
                return thelta1 > thelta2;
            }
            return lhs.first < rhs.first;
        });
        d.clear();
        d.resize(n);
        for (int i = 0; i < n; i++) {
            d[i].resize(m + 1);
            for (int j = 0; j <= m; j++) {
                d[i][j].resize(totHeight + 1, numeric_limits<int>::min());
            }
            d[i][0][0] = 0;
        }
        d[0][1][p[0].second] = p[0].second * p[0].first;
        for (int i = 1; i < n; i++) {
            for (int j = 1; j <= min(m, i + 1); j++) {
                for (int h = 0; h <= totHeight; h++) {
                    d[i][j][h] = d[i - 1][j][h];
                    if (h >= p[i].second) {
                        d[i][j][h] = max(d[i][j][h], d[i - 1][j - 1][h - p[i].second] + 2 * h * p[i].first - p[i].first * p[i].second);
                    }
                }
            }
        }
        int ans = 0;
        for (int h = 0; h <= totHeight; h++) { ans = max(ans, d[n - 1][m][h]); }
        cout << "Case " << t << ": " << ans << endl;
    }
    return 0;
}
