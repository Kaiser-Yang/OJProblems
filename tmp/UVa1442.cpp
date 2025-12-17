/*
    You are given a cave. The cave can be seen as a plane, and the position i has
p[i] and s[i] meaning the bottom and the ceiling of the position. You need to fill
water into the cave as much as possible, and the water at any position can not exceed
the ceiling.
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int T, n;
    vector<int> p, s, l, r;
    cin >> T;
    while (T--) {
        cin >> n;
        p.resize(n), s.resize(n), l.resize(n), r.resize(n);
        for (int i = 0; i < n; i++) { cin >> p[i]; }
        for (int i = 0; i < n; i++) { cin >> s[i]; }
        l[0] = s[0];
        int height = s[0];
        for (int i = 1; i < n; i++) {
            if (p[i] > height) {
                height = p[i];
            } else if (s[i] < height) {
                height = s[i];
            }
            l[i] = height;
        }
        r[n - 1] = s[n - 1];
        height = s[n - 1];
        for (int i = n - 1; i >= 0; i--) {
            if (p[i] > height) {
                height = p[i];
            } else if (s[i] < height) {
                height = s[i];
            }
            r[i] = height;
        }
        int ans = 0;
        for (int i = 0; i < n; i++) { ans += min(l[i], r[i]) - p[i]; }
        cout << ans << endl;
    }
    return 0;
}
