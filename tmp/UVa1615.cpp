#include <bits/stdc++.h>

using namespace std;

int right(int d, int x, int y) { return sqrt(d * d - y * y) + x; }

int left(int d, int x, int y) { return x - sqrt(d * d - y * y); }

int main() {
    ios::sync_with_stdio(false);
    int len, d, n;
    vector<pair<int, int>> point;
    while (cin >> len >> d >> n) {
        point.resize(n);
        for (int i = 0; i < n; i++) { cin >> point[i].first >> point[i].second; }
        sort(point.begin(), point.end(), [](const pair<int, int> &lhs, const pair<int, int> &rhs) {
            if (lhs.first == rhs.first) { return lhs.second > rhs.second; }
            return lhs.first < rhs.first;
        });
        int nowRight;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (i == 0) {
                nowRight = right(d, point[i].first, point[i].second);
                ans++;
            } else {
                int l = left(d, point[i].first, point[i].second);
                int r = right(d, point[i].first, point[i].second);
                if (l > nowRight) {
                    ans++;
                    nowRight = r;
                }
            }
            nowRight = min(nowRight, len);
            nowRight = max(0, nowRight);
        }
        cout << ans << endl;
    }
    return 0;
}
