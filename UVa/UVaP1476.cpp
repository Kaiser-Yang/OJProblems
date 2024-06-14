// problem statement: https://vjudge.net/problem/UVA-1476

#include <bits/stdc++.h>

const double eps   = 1e-9;
constexpr int MAXN = 1e4 + 10;

using namespace std;

int T, n;
array<int, MAXN> a, b, c;
double l, r, mid, lmid, rmid;

double f(double x) {
    double res = a[0] * x * x + b[0] * x + c[0];
    for (int i = 1; i < n; i++) { res = max(res, a[i] * x * x + b[i] * x + c[i]); }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) { cin >> a[i] >> b[i] >> c[i]; }
        l = 0, r = 1000;
        while (r > l + eps) {
            mid  = (l + r) / 2;
            lmid = mid - eps;
            rmid = mid + eps;
            if (f(lmid) > f(rmid)) {
                l = mid;
            } else {
                r = mid;
            }
        }
        cout << fixed << setprecision(4) << f(l) << "\n";
    }
    return 0;
}
