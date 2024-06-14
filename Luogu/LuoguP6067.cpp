// problem statement: https://www.luogu.com.cn/problem/P6067

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;

int n;
long long ans;
vector<long long> a;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) { cin >> a[i]; }
    sort(a.begin(), a.end());
    for (int i = 1; i <= n; i++) { a[i] += a[i - 1]; }
    for (int i = 1; i <= n; i++) { ans += i * (a[i] - a[i - 1]) - a[i]; }
    ans *= 2;
    cout << ans << "\n";
    return 0;
}
