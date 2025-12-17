#include <bits/stdc++.h>

using namespace std;

int dp(int i, int j, int k, int l, vector<vector<vector<vector<int>>>> &d, set<int> &occur, vector<vector<int>> &color)
{
    int n = d.size() - 1;
    int &ans = d[i][j][k][l];
    if (ans != -1) { return ans; }
    if (occur.size() == 5) {
        return ans = 0;
    }
    ans = 0;
    if (i < n) {
        if (occur.count(color[0][i])) {
            occur.erase(color[0][i]);
            ans = dp(i + 1, j, k, l, d, occur, color) + 1;
            occur.insert(color[0][i]);
        } else {
            occur.insert(color[0][i]);
            ans = dp(i + 1, j, k, l, d, occur, color);
            occur.erase(color[0][i]);
        }
    }
    if (j < n) {
        if (occur.count(color[1][j])) {
            occur.erase(color[1][j]);
            ans = max(ans, dp(i, j + 1, k, l, d, occur, color) + 1);
            occur.insert(color[1][j]);
        } else {
            occur.insert(color[1][j]);
            ans = max(ans, dp(i, j + 1, k, l, d, occur, color));
            occur.erase(color[1][j]);
        }
    }
    if (k < n) {
        if (occur.count(color[2][k])) {
            occur.erase(color[2][k]);
            ans = max(ans, dp(i, j, k + 1, l, d, occur, color) + 1);
            occur.insert(color[2][k]);
        } else {
            occur.insert(color[2][k]);
            ans = max(ans, dp(i, j, k + 1, l, d, occur, color));
            occur.erase(color[2][k]);
        }
    }
    if (l < n) {
        if (occur.count(color[3][l])) {
            occur.erase(color[3][l]);
            ans = max(ans, dp(i, j, k, l + 1, d, occur, color) + 1);
            occur.insert(color[3][l]);
        } else {
            occur.insert(color[3][l]);
            ans = max(ans, dp(i, j, k, l + 1, d, occur, color));
            occur.erase(color[3][l]);
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int n;
    vector<vector<int>> color;
    vector<vector<vector<vector<int>>>> d;
    set<int> occur;
    while (cin >> n && n != 0) {
        color.clear();
        color.resize(4);
        for (int i = 0; i < 4; i++) {
            color[i].resize(n);
        }
        for (int i = 0; i < n; i++) {
            cin >> color[0][i] >> color[1][i] >> color[2][i] >> color[3][i];
        }
        occur.clear();
        d.clear();
        d.resize(n + 1);
        for (int i = 0; i < n + 1; i++) {
            d[i].resize(n + 1);
            for (int j = 0; j < n + 1; j++) {
                d[i][j].resize(n + 1);
                for (int k = 0; k < n + 1; k++) {
                    d[i][j][k].resize(n + 1, -1);
                }
            }
        }
        cout << dp(0, 0, 0, 0, d, occur, color) << endl;
    }
    return 0;
}