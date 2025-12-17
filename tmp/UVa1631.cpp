#include <bits/stdc++.h>

using namespace std;

vector<vector<vector<vector<int>>>> d;
string s, t;
int n;

int dp(int i, int a, int b, int c) {
    if (i == n) { return 0; }
    int &ans = d[i][a][b][c];
    if (ans != -1) { return ans; }
    static const int INF = numeric_limits<int>::max() / 10;
    int nc = (i + 3 < n ? (s[i + 3] - '0') : 0);
    ans = INF;
    for (int p = 0, d = (a - (t[i] - '0') + 10) % 10, flag = -1; p < 2;
         p++, d = 10 - d, flag = -flag) {
        for (int numB = 0; numB <= d; numB++) {
            for (int numC = 0; numC <= numB; numC++) {
                ans = min(
                    ans,
                    dp(i + 1, (b + numB * flag + 10) % 10, (c + numC * flag + 10) % 10, nc) + d);
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    static constexpr int INF = numeric_limits<int>::max();
    while (cin >> s >> t) {
        n = s.length();
        d.clear();
        d.resize(n);
        for (int i = 0; i < n; i++) {
            d[i].resize(10);
            for (int a = 0; a < 10; a++) {
                d[i][a].resize(10);
                for (int b = 0; b < 10; b++) { d[i][a][b].resize(10, -1); }
            }
        }
        s += "000";
        cout << dp(0, s[0] - '0', s[1] - '0', s[2] - '0') << endl;
    }
    return 0;
}