#include <bits/stdc++.h>

using namespace std;

int dp(int i, int j, int k, vector<vector<vector<int>>> &d, vector<int> &left, vector<int> &col)
{
    int &ans = d[i][j][k];
    if (ans != -1) { return ans; }
    if (left[j] <= i || i == j) {
        ans = (j - i + 1 + k) * (j - i + 1 + k);
        return ans;
    }
    ans = dp(i, left[j] - 1, 0, d, left, col) + (j - left[j] + 1 + k) * (j - left[j] + 1 + k);
    for (int q = i; q < left[j] - 1; q++) {
        if (col[q] == col[j] && col[q + 1] != col[j]) {
            ans = max(ans, dp(q + 1, left[j] - 1, 0, d, left, col) + dp(i, q, j - left[j] + 1 + k, d, left, col));
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int T, n, kase = 0;
    vector<int> col, left;
    vector<vector<vector<int>>> d;
    cin >> T;
    while (T--) {
        cin >> n;
        col.resize(n);
        left.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> col[i];
        }
        for (int i = 0; i < n; i++) {
            if (i != 0 && col[i] == col[i - 1]) {
                left[i] = left[i - 1];
            } else {
                left[i] = i;
            }
        }
        d.clear();
        d.resize(n);
        for (int i = 0; i < n; i++) {
            d[i].resize(n);
            for (int j = 0; j < n; j++) {
                d[i][j].resize(n, -1);
            }
        }
        cout << "Case " << ++kase << ": " << dp(0, n - 1, 0, d, left, col) << endl;
    }
    return 0;
}