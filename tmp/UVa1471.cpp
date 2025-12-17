/*
    You are given a sequence, and you need to find the maximum-length increasing substring after
eliminating one substring. (You can eliminating no one.)
*/
#include <bits/stdc++.h>

using namespace std;

struct NodeInfo {
    int first, second;
    constexpr bool operator<(const NodeInfo &rhs) const {
        return this->first < rhs.first;
    }
};

int  main()
{
    ios::sync_with_stdio(false);
    int T, n, ans;
    vector<int> a, f, g;
    set<NodeInfo> s;
    cin >> T;
    while (T--) {
        cin >> n;
        a.resize(n);
        f.resize(n);
        g.resize(n);
        for (int i = 0; i < n; i++) { cin >> a[i]; }
        f[0] = 1;
        for (int i = 1; i < n; i++) {
            if (a[i] > a[i - 1]) { f[i] = f[i - 1] + 1; }
            else { f[i] = 1; }
        }
        g[n - 1] = 1;
        for (int i = n - 2; i >= 0; i--) {
            if (a[i] < a[i + 1]) { g[i] = g[i + 1] + 1; }
            else { g[i] = 1; }
        }
        s.clear();
        ans = 1;
        for (int i = n - 1; i >= 0; i--) {
            auto pos = s.upper_bound({a[i], 0});
            if (pos == s.end()) {
                ans = max(ans, f[i]);
            } else {
                ans = max(ans, f[i] + pos->second);
            }
            if (pos == s.end() || pos->second < g[i]) {
                if (pos == s.begin()) {
                    s.insert({a[i], g[i]});
                    continue;
                }
                auto left = pos;
                left--;
                if (left->first == a[i] && left->second >= g[i]) { continue; }
                while (left->second <= g[i]) {
                    if (left == s.begin()) {
                        break;
                    }
                    left--;
                    if (left->second > g[i]) { left++; break; }
                }
                s.erase(left, pos);
                s.insert({a[i], g[i]});
            }
        }
        cout << ans << endl;
    }
    return 0;
}
