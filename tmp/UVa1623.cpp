#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int T, n, m;
    vector<int> rain;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        rain.resize(m);
        for (int i = 0; i < m; i++) { cin >> rain[i]; }
        bool ok = true;
        set<int> s;
        vector<int> las(n + 1), ans(m + 1);
        for (int i = 0; i < m; i++) {
            if (rain[i] != 0) {
                auto it = s.lower_bound(las[rain[i]]);
                if (it == s.end()) {
                    ok = false;
                    break;
                }
                s.erase(it);
                ans[*it] = rain[i];
                las[rain[i]] = i;
            } else {
                s.insert(i);
            }
        }
        if (ok) {
            cout << "YES" << endl;
            for (int i = 0; i < m; i++) {
                if (rain[i] == 0) { cout << ans[i] << " "; }
            }
            cout << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
