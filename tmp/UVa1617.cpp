#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int T, n;
    vector<pair<int, int>> p;
    cin >> T;
    while (T--) {
        cin >> n;
        p.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i].first >> p[i].second;
        }
        sort(p.begin(), p.end(), [] (const pair<int, int> &lhs, pair<int, int> &rhs) {
            if (lhs.second == rhs.second) { return lhs.first < rhs.first; }
            return lhs.second < rhs.second;
        });
        int ans = 0, pos = p[0].second;
        for (int i = 1; i < n; i++) {
            if (p[i].first > pos) {
                ans++;
                pos = p[i].second;
            } else if (pos != p[i].second) {
                pos++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
