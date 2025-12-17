#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int T, n, w, h;
    vector<pair<int, int>> p;
    vector<int> y;
    cin >> T;
    while (T--) {
        cin >> n >> w >> h;
        p.resize(n);
        y.clear();
        y.push_back(0);
        for (int i = 0; i < n; i++) {
            cin >> p[i].first >> p[i].second;
            y.push_back(p[i].second);
        }
        y.push_back(h);
        sort(y.begin(), y.end());
        sort(p.begin(), p.end());
        int len = unique(y.begin(), y.end()) - y.begin();
        int ans = -1, ansx = 0, ansy = 0;
        int minY = 0, maxY = 0, height = 0, tmp = 0, width = 0;
        for (int i = 0; i < len; i++) {
            minY = y[i];
            for (int j = i + 1; j < len; j++) {
                maxY = y[j];
                height = maxY - minY;
                tmp = 0;
                for (int k = 0; k < n; k++) {
                    if (p[k].second <= minY || p[k].second >= maxY) { continue; }
                    width = p[k].first - tmp;
                    if (ans < min(width, height)) {
                        ans = min(width, height);
                        ansx = tmp;
                        ansy = minY;
                    }
                    tmp = p[k].first;
                }
                width = w - tmp;
                if (ans < min(width, height)) {
                    ans = min(width, height);
                    ansx = tmp;
                    ansy = minY;
                }
            }
        }
        cout << ansx << " " << ansy << " " << ans << endl;
        if (T != 0) { cout << endl; }
    }
    return 0;
}
