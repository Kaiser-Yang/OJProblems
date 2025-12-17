#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int a, b, m, n;
    vector<vector<int>> d;
    vector<int> minD, l, r;
    stack<int> s;
    while (cin >> a >> b >> m >> n) {
        if (a > b) { swap(a, b); }
        d.resize(m + 1);
        l.resize(n + 1);
        r.resize(n + 1);
        for (int i = 1; i <= m; i++) {
            d[i].resize(n + 1);
            for (int j = 1; j <= n; j++) {
                cin >> d[i][j];
            }
        }
        long long ans = 0;
        for (int i = 1; i <= m; i++) {
            for (int y = 1; y <= b && i + y - 1 <= m; y++) {
                if (y == 1) {
                    minD.clear();
                    minD.push_back(0);
                    for (int j = 1; j <= n; j++) { minD.push_back(d[i + y - 1][j]); }
                } else {
                    for (int j = 1; j <= n; j++) { minD[j] = min(minD[j], d[i + y - 1][j]); }
                }
                for (int j = 1; j <= n; j++) {
                    while (!s.empty() && minD[s.top()] >= minD[j]) {
                        s.pop();
                    }
                    if (!s.empty()) {
                        l[j] = s.top();
                    } else {
                        l[j] = 0;
                    }
                    s.push(j);
                }
                while (!s.empty()) { s.pop(); }
                for (int j = n; j >= 1; j--) {
                    while (!s.empty() && minD[s.top()] >= minD[j]) {
                        s.pop();
                    }
                    if (!s.empty()) {
                        r[j] = s.top();
                    } else {
                        r[j] = n + 1;
                    }
                    s.push(j);
                }
                while (!s.empty()) { s.pop(); }
                for (int j = 1; j <= n; j++) {
                    int x = min((y <= a ? b : a), r[j] - l[j] - 1);
                    ans = max(ans, 1LL * x * y * ((1LL * m * n * minD[j] - 1) / (1LL * m * n - x * y)));
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
