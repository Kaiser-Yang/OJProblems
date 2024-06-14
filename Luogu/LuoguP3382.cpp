// problem statement: https://www.luogu.com.cn/problem/P3382

#include <bits/stdc++.h>

const double eps = 1e-7;
constexpr int MAXN = 15;

using namespace std;

double l, r, mid, lmid, rmid;
int n;
array<double, MAXN> a;

double f(double x) {
    double res = 0;
    for (int i = 0; i <= n; i++) { res += a[i] * pow(x, i); }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> l >> r;
    for (int i = n; i >= 0; i--) { cin >> a[i]; }
    while (r - l > eps) {
        mid = (l + r) / 2;
        lmid = mid - eps;
        rmid = mid + eps;
        if (f(lmid) > f(rmid)) {
            r = mid;
        } else {
            l = mid;
        }
        
    }
    cout << l << endl;
    return 0;
}
