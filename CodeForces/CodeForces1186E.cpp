// problem statement: https://codeforces.com/contest/1186/problem/E

#include <bits/stdc++.h>

using namespace std;

int n, m, q;
string s;
vector<vector<int>> sum;

long long cal(long long x, long long y) {
    if (x <= 0 || y <= 0) return 0;
    long long a = x % n, b = y % m;
    long long ans = (x * y - a * b) >> 1;
    if (((__builtin_popcountll(x / n)) ^ (__builtin_popcountll(y / m))) & 1) {
        ans += a * b - sum[a][b];
    } else {
        ans += sum[a][b];
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> q;
    sum.resize(n * 2 + 1, vector<int>(m * 2 + 1));
    for (int i = 1; i <= n; i++) {
        cin >> s;
        for (int j = 1; j <= m; j++) {
            if (s[j - 1] == '0') {
                sum[i][j] = 0;
            } else {
                sum[i][j] = 1;
            }
            sum[i + n][j] = sum[i][j + m] = sum[i][j] ^ 1;
            sum[i + n][j + m] = sum[i][j];
        }
    }
    n <<= 1, m <<= 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }
    while (q--) {
        long long x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << cal(x2, y2) - cal(x2, y1 - 1) - cal(x1 - 1, y2) + cal(x1 - 1, y1 - 1) << '\n';
    }
    return 0;
}
