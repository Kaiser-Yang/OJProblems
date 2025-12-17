/*
    You are given a n * m matrix. Every grid is either empty or blocked.
For every empty grid, you need figure out the matirx which has the maxium
perimeter and whose right-bottom is the empty grid. Then, count the times
of each perimeter.
*/
#include <bits/stdc++.h>

using namespace std;

int main()
{
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    ios::sync_with_stdio(false);
    int T, n, m;
    string str;
    vector<vector<int>> g;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        g.resize(n + 1);
        g[0].resize(m + 1);
        for (int i = 1; i <= n; i++) {
            cin >> str;
            g[i].resize(m + 1);
            for (int j = 1; j <= m; j++) {
                g[i][j] = str[j - 1] == '.' ? 1 : 0;
                if (g[i][j] == 1) {
                    g[i][j] += g[i - 1][j];
                }
            }
        }
        stack<pair<int, int>> s;
        map<int, int> cnt;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int p = j;
                while (!s.empty() && s.top().second >= g[i][j]) {
                    p = s.top().first;
                    s.pop();
                }
                if (g[i][j] == 0) { continue; }
                if (s.empty() || s.top().second - s.top().first < g[i][j] - p) {
                    s.push(make_pair(p, g[i][j]));
                    cnt[2 * (g[i][j] + j - p + 1)]++;
                } else {
                    cnt[(s.top().second + j - s.top().first + 1) * 2]++;
                }
            }
            while (!s.empty()) { s.pop(); }
        }
        vector<pair<int, int>> ans;
        for (auto item : cnt) { ans.push_back(item); }
        sort(ans.begin(), ans.end());
        for (auto it = ans.begin(); it != ans.end(); it++) {
            cout << it->second << " x " << it->first << endl;
        }
    }
    return 0;
}
