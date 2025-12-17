#include <bits/stdc++.h>

using namespace std;

bool check(double res, vector<pair<int, int>> &p) {
    double pos = 0;
    for (int i = 0; i < p.size(); i++) {
        if (p[i].first < pos) {
            pos += res;
        } else {
            pos = p[i].first + res;
        }
        if (pos > p[i].second) { return false; }
    }
    return true;
}

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
    ios::sync_with_stdio(false);
    int n;
    vector<pair<int, int>> p;
    while (cin >> n) {
        p.resize(n);
        double l = 0, r = 1e6, ans = -1;
        for (int i = 0; i < n; i++) {
            cin >> p[i].first >> p[i].second;
            r = min((int)r, p[i].second - p[i].first);
        }
        sort(p.begin(), p.end(), [](const pair<int, int> &lhs, pair<int, int> &rhs) {
            if (lhs.first == rhs.first) { return lhs.second < rhs.second; }
            return lhs.first < rhs.first;
        });
        while (r - l >= 1e-9) {
            double mid = (l + r) / 2;
            if (check(mid, p)) {
                ans = mid;
                l = mid;
                ;
            } else {
                r = mid;
            }
        }
        double ans1 = 1, ans2 = 1;
        for (int denominator = 1; denominator <= n; denominator++) {
            int numerator = round(denominator * ans);
            if (fabs((double)numerator / denominator - ans) < fabs((double)ans1 / ans2 - ans)) {
                ans1 = numerator;
                ans2 = denominator;
            }
        }
        int g = gcd(ans1, ans2);
        cout << ans1 / g << "/" << ans2 / g << endl;
    }
    return 0;
}
