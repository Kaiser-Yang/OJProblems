// problem statement:

#include <bits/stdc++.h>

using namespace std;

constexpr double eps = 1e-4;

double a, b, c, d;

bool less(const double a, const double b) {
    if (b - a > eps) { return true; }
    return false;
}
set<double, decltype(&::less), std::allocator<double>> ans(::less);

int cmp(const double a, const double b) {
    if (fabs(a - b) <= eps) { return 0; }
    if (a - b > eps) { return 1; }
    return -1;
}

double f(double x) { return a * x * x * x + b * x * x + c * x + d; }

int main() {
    ios::sync_with_stdio(false);
    cin >> a >> b >> c >> d;
    for (int i = -100; i <= 100; i++) {
        double l = i, r = i + 1;
        double fl = f(l), fr = f(r);
        if (fl * fr <= 0) {
            while (cmp(l, r) < 0) {
                double mid = (l + r) / 2;
                double fmid = f(mid);
                if (fl * fmid <= 0) {
                    r = mid;
                } else {
                    l = mid;
                }
            }
            ans.insert(l);
        }
    }
    for (double elem : ans) { cout << fixed << setprecision(2) << elem << " "; }
    cout << endl;
    return 0;
}
