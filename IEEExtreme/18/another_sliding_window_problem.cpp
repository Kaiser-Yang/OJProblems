// problem statement: https://csacademy.com/ieeextreme-practice/task/another-sliding-window-problem

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;

int n, q;
int a[MAXN];
long long x;
long long sum[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) { cin >> a[i]; }
    for (int i = 1; i <= n; i++) { sum[i] = sum[i - 1] + a[i]; }
    while (q--) {
        cin >> x;
        long long ans = 0;
        int r = n, l = n;
        while (r > 0 && a[r] > x) { r--; }
        l = r;
        while (l > 1) {
            l--;
            if ((r - l + 1 - 1) % 2 == 0) {
                if (r + 1 <= n && a[l] + a[r + 1] <= x) { r++; }
            } else {
                if (a[l] + a[r] > x) {
                    r--;
                } else {
                    if (r + 1 <= n && a[r + 1] <= x) { r++; }
                }
            }
            ans += (sum[r] - sum[l - 1]) - 1LL * (r - l + 1) * a[l];
        }
        cout << ans << endl;
    }
    return 0;
}
