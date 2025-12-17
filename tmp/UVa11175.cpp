// int main()
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int T, m, k, x, y;
    vector<vector<int>> g;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> m >> k;
        g.resize(m);
        for (int i = 0; i < m; i++) {
            g[i].clear();
            g[i].resize(m);
        }
        for (int i = 0; i < k; i++) {
            cin >> x >> y;
            g[x][y] = true;
        }
        bool ok = true;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                bool ok1 = false, ok2 = false;
                for (int k = 0; k < m; k++) {
                    if (g[i][k] && g[j][k]) { ok1 = true; }
                    if (g[i][k] ^ g[j][k]) { ok2 = true; }
                }
                ok = !(ok1 && ok2);
                if (!ok) { break; }
            }
            if (!ok) { break; }
        }
        cout << "Case #" << t << ": " << (ok ? "Yes" : "No") << endl;
    }
    return 0;
}
