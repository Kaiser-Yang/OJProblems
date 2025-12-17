#include <bits/stdc++.h>

using namespace std;

int dp(int i, int j, int k, int pos, vector<vector<vector<vector<int>>>> &d, vector<int> &p, vector<int> &e)
{
    int &ans = d[i][j][k][pos];
    if (ans != -1) { return ans; }
    if (k == 0) {
        ans = 0;
        return ans;
    }
    ans = 0;
    for (int ii = 0; ii < i; ii++) {
        int temp = 0;
        if (pos == 0) {
            temp = abs(p[ii] - p[i]);
        } else {
            temp = abs(p[ii] - p[j]);
        }
        ans = max(ans, e[ii] - k * temp + dp(ii, j, k - 1, 0, d, p, e));
    }
    for (int ii = j + 1; ii < p.size(); ii++) {
        int temp = 0;
        if (pos == 0) {
            temp = abs(p[ii] - p[i]);
        } else {
            temp = abs(p[ii] - p[j]);
        }
        ans = max(ans, e[ii] - k * temp + dp(i, ii, k - 1, 1, d, p, e));

    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int T, n;
    vector<int> p, e;
    cin >> T;
    while (T--) {
        cin >> n;
        p.resize(n);
        e.resize(n);
        for (int i = 0; i < n; i++)  {
            cin >> p[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> e[i];
        }
        vector<vector<vector<vector<int>>>> d;
        d.resize(n);
        for (int i = 0; i < n; i++) {
            d[i].resize(n);
            for (int j = 0; j < n; j++) {
                d[i][j].resize(n);
                for (int k = 0; k < n; k++) {
                    d[i][j][k].resize(2, -1);
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int k = 1; k <= n; k++) {
                ans = max(ans, dp(i, i, k - 1, 0, d, p, e) + e[i] - abs(p[i]) * k);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
