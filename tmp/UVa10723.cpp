#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int T;
    string a, b;
    vector<vector<int>> d;
    vector<vector<long long>> num;
    cin >> T;
    cin.ignore();
    for (int t = 1; t <= T; t++) {
        getline(cin, a);
        getline(cin, b);
        static const int INF = numeric_limits<int>::max();
        int n = a.length(), m = b.length();
        a = " " + a;
        b = " " + b;
        d.clear();
        num.clear();
        d.resize(n + 1);
        num.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            d[i].resize(m + 1, INF);
            num[i].resize(m + 1, 0);
        }
        for (int j = 0; j <= m; j++) {
            d[0][j] = j;
            num[0][j] = 1;
        }
        for (int i = 0; i <= n; i++) {
            d[i][0] = i;
            num[i][0] = 1;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (a[i] == b[j]) {
                    d[i][j] = d[i - 1][j - 1] + 1;
                    num[i][j] = num[i - 1][j - 1];
                } else {
                    if (d[i - 1][j] < d[i][j - 1]) {
                        d[i][j] = d[i - 1][j] + 1;
                        num[i][j] = num[i - 1][j];
                    } else if (d[i - 1][j] == d[i][j - 1]) {
                        d[i][j] = d[i - 1][j] + 1;
                        num[i][j] = num[i - 1][j] + num[i][j - 1];
                    } else {
                        d[i][j] = d[i][j - 1] + 1;
                        num[i][j] = num[i][j - 1];
                    }
                }
            }
        }
        cout << "Case #" << t << ": " << d[n][m] << " " << num[n][m] << endl;
    }
    return 0;
}
