#include <bits/stdc++.h>

using namespace std;

struct Bulb {
    int v, k, c, l;
    bool operator<(const Bulb &other) { return v < other.v; }
};

int main() {
    ios::sync_with_stdio(false);
    int n;
    vector<Bulb> bulb;
    vector<int> s, dp;
    while (cin >> n && n != 0) {
        bulb.resize(n);
        s.resize(n);
        dp.resize(n);
        for (int i = 0; i < n; i++) {
            int &v = bulb[i].v;
            int &k = bulb[i].k;
            int &c = bulb[i].c;
            int &l = bulb[i].l;
            cin >> v >> k >> c >> l;
        }
        sort(bulb.begin(), bulb.end());
        s[0] = bulb[0].l;
        for (int i = 1; i < n; i++) { s[i] = s[i - 1] + bulb[i].l; }
        for (int i = 0; i < n; i++) {
            dp[i] = bulb[i].k + bulb[i].c * s[i];
            for (int j = 0; j < i; j++) {
                dp[i] = min(dp[i], dp[j] + (s[i] - s[j]) * bulb[i].c + bulb[i].k);
            }
        }
        cout << dp[n - 1] << endl;
    }
    return 0;
}
