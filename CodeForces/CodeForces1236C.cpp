// problem statement: https://codeforces.com/problemset/problem/1236/C

#include <bits/stdc++.h>

using namespace std;

int n;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    vector<vector<int>> ans(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j == 0) {
                ans[i][j] = i + 1;
            } else if (i == 0) {
                if (j % 2 == 0) {
                    ans[i][j] = ans[i][j - 1] + 1;
                } else {
                    ans[i][j] = ans[i][j - 1] + 2 * n - 1;
                }
            } else if (i == n - 1) {
                if (j % 2 == 1) {
                    ans[i][j] = ans[i][j - 1] + 1;
                } else {
                    ans[i][j] = ans[i][j - 1] + 2 * n - 1;
                }
            } else {
                if (j % 2 == 1) {
                    ans[i][j] = ans[i][j - 1] + 2 * n - 2 * i - 1;
                } else {
                    ans[i][j] = ans[i][j - 1] + 2 * i + 1;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) { cout << ans[i][j] << " \n"[j == n - 1]; }
    }
    return 0;
}
