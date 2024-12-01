// problem statement: https://codeforces.com/contest/2034/problem/D

#include <bits/stdc++.h>

using namespace std;

int T, n;
vector<int> a;
set<int> pos[3];

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        a.resize(n);
        pos[0].clear();
        pos[1].clear();
        pos[2].clear();
        for (int i = 0; i < n; i++) { cin >> a[i]; }
        for (int i = 0; i < n; i++) { pos[a[i]].insert(i); }
        int len0 = pos[0].size(), len1 = pos[1].size();
        vector<pair<int, int>> ans;
        while (!pos[0].empty() || !pos[1].empty() || !pos[2].empty()) {
            while (!pos[0].empty() && *pos[0].rbegin() + 1 <= len0) {
                pos[0].erase(*pos[0].rbegin());
            }
            while (pos[1].size() > 1 && len0 < *pos[1].rbegin() + 1 && *pos[1].rbegin() + 1 <= len0 + len1) {
                pos[1].erase(*pos[1].rbegin());
            }
            while (!pos[2].empty() && len0 + len1 < *pos[2].rbegin() + 1) {
                pos[2].erase(*pos[2].rbegin());
            }
            if (pos[0].empty() && pos[2].empty()) { break; }
            if (*pos[1].rbegin() + 1 <= len0) {
                int tmp0 = *pos[0].rbegin(), tmp1 = *pos[1].rbegin();
                pos[0].erase(tmp0);
                pos[1].erase(tmp1);
                pos[0].insert(tmp1);
                pos[1].insert(tmp0);
                ans.emplace_back(tmp0, tmp1);

            } else if (*pos[1].rbegin() + 1 > len0 + len1) {
                int tmp1 = *pos[1].rbegin(), tmp2 = *pos[2].rbegin();
                pos[1].erase(tmp1);
                pos[2].erase(tmp2);
                pos[1].insert(tmp2);
                pos[2].insert(tmp1);
                ans.emplace_back(tmp1, tmp2);
            } else {
                int tmp0 = *pos[0].rbegin(), tmp1 = *pos[1].rbegin(), tmp2 = *pos[2].rbegin();
                pos[0].erase(tmp0);
                pos[1].erase(tmp1);
                pos[2].erase(tmp2);
                pos[0].insert(tmp1);
                pos[1].insert(tmp2);
                pos[2].insert(tmp0);
                ans.emplace_back(tmp0, tmp1);
                ans.emplace_back(tmp0, tmp2);
            }
        }
        cout << ans.size() << '\n';
        for (auto [x, y] : ans) { cout << x + 1 << ' ' << y + 1 << '\n'; }
    }
    return 0;
}
