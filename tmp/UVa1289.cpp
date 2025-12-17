#include <bits/stdc++.h>

using namespace std;

int n, h, kase = 0;
vector<vector<int>> plate, pos, d;
vector<int> maxD;
vector<vector<bool>> occur;

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n) {
        int ALL = 0;
        plate.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> h;
            plate[i].clear();
            int height, lastHeight = -1;
            for (int j = 0; j < h; j++) {
                cin >> height;
                if (height == lastHeight) { continue; }
                ALL++;
                plate[i].push_back(height);
                lastHeight = height;
            }
        }
        vector<int> np;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < plate[i].size(); j++) { np.push_back(plate[i][j]); }
        }
        sort(np.begin(), np.end());
        int len = unique(np.begin(), np.end()) - np.begin();
        pos.resize(len);
        for (int i = 0; i < len; i++) { pos[i].clear(); }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < plate[i].size(); j++) {
                int p = lower_bound(np.begin(), np.begin() + len, plate[i][j]) - np.begin();
                pos[p].push_back(i);
            }
        }
        occur.clear();
        occur.resize(len);
        for (int i = 0; i < len; i++) {
            occur[i].resize(n, false);
            for (int j : pos[i]) { occur[i][j] = true; }
        }
        d.clear();
        d.resize(len);
        for (int i = 0; i < len; i++) { d[i].resize(n); }
        maxD.resize(len);
        maxD[0] = 0;
        for (int j : pos[0]) { d[0][j] = 0; }
        for (int i = 1; i < len; i++) {
            maxD[i] = -1;
            for (int j : pos[i]) {
                if (!occur[i - 1][j]) {
                    d[i][j] = maxD[i - 1];
                } else {
                    if (pos[i - 1].size() == 1) {
                        d[i][j] = maxD[i - 1] + 2;
                    } else {
                        for (int k : pos[i - 1]) {
                            if (k == j) {
                                d[i][j] = max(d[i][j], d[i - 1][k]);
                            } else {
                                d[i][j] = max(d[i][j], d[i - 1][k] + 2);
                            }
                        }
                    }
                }
                maxD[i] = max(maxD[i], d[i][j]);
            }
        }
        cout << "Case " << ++kase << ": " << 2 * ALL - n - 1 - maxD[len - 1] << endl;
    }
    return 0;
}