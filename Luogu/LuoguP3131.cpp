// problem statement: https://www.luogu.com.cn/problem/P3131

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 5e4 + 10;

int n, ans, l, r;
vector<int> a;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += a[i - 1];
        a[i] %= 7;
    }
    for (int rest = 0; rest < 7; rest++) {
        l = find_if(a.begin(), a.end(), [rest](int x) { return x == rest; }) - a.begin();
        if (l == n + 1) { continue; }
        r = find_if(a.rbegin(), a.rend(), [rest](int x) { return x == rest; }) - a.rbegin();
        r = n - r;
        ans = max(ans, r - l);
    }
    cout << ans << "\n";
    return 0;
}
