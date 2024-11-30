// problem statement: https://codeforces.com/contest/1185/problem/A

#include <bits/stdc++.h>

using namespace std;

int a, b, c, d;

int main() {
    ios::sync_with_stdio(false);
    cin >> a >> b >> c >> d;
    if (a > b) { swap(a, b); }
    if (a > c) { swap(a, c); }
    if (b > c) { swap(b, c); }
    int ans = 0;
    if (b - a < d) { ans += d - (b - a); }
    if (c - b < d) { ans += d - (c - b); }
    cout << ans << endl;
    return 0;
}
