// problem statement: https://www.luogu.com.cn/problem/P2123

#include <bits/stdc++.h>

constexpr int MAXN = 2e4 + 10;

using namespace std;

int n, T;
pair<long long, long long> minister[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) { cin >> minister[i].first >> minister[i].second; }
        sort(minister, minister + n, [](const auto &a, const auto &b) {
            return min(a.first, b.second) == min(b.first, a.second) ?
                       a.first < b.first :
                       min(a.first, b.second) < min(b.first, a.second);
        });
        long long ans = 0, sum = 0;
        for (int i = 0; i < n; i++) {
            sum += minister[i].first;
            ans = max(ans, sum) + minister[i].second;
        }
        cout << ans << "\n";
    }
    return 0;
}
