// problem statement:

#include <bits/stdc++.h>

using namespace std;

int n;
double h, s1, v, l, k;

int main() {
    cin >> h >> s1 >> v >> l >> k >> n;
    double tMax = sqrt(h / 5);
    double tMin = sqrt((h - k) / 5);
    double r = s1 - tMin * v + l, l = s1 - tMax * v;
    if (fabs(int(r + 1) - r) <= 1e-4) { r++; }
    if (l > 0 && l - (int)l > 1e-4 && fabs(int(l) - l) <= 1e-4) { l--; }
    r = min(r, (double)n);
    l = max(l, 0.);
    cout << (int)r - (int)l << endl;
    return 0;
}