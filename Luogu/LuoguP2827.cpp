// problem statement: https://www.luogu.com.cn/problem/P2827

#include <bits/stdc++.h>

constexpr size_t MAXN = 1e5 + 10;

using namespace std;

int n, m, q, u, v, t;
long long a[MAXN];
queue<long long> q1, q2, q3;

long long get_max() {
    long long a = std::numeric_limits<long long>::min(), b = std::numeric_limits<long long>::min(),
              c = std::numeric_limits<long long>::min();
    if (!q1.empty()) { a = q1.front(); }
    if (!q2.empty()) { b = q2.front(); }
    if (!q3.empty()) { c = q3.front(); }
    long long res = max({a, b, c});
    if (res == a) {
        q1.pop();
    } else if (res == b) {
        q2.pop();
    } else {
        q3.pop();
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> q >> u >> v >> t;
    for (int i = 0; i < n; i++) { cin >> a[i]; }
    sort(a, a + n, std::greater<long long>());
    for (int i = 0; i < n; i++) { q1.push(a[i]); }
    long long increment = 0;
    for (int i = 1; i <= m; i++) {
        long long x = get_max();
        x += increment;
        if (i % t == 0) { cout << x << (i + t > m ? "" : " "); }
        increment += q;
        long long y = x * u / v;
        long long z = x - y;
        if (y > z) { swap(y, z); }
        q2.push(y - increment);
        q3.push(z - increment);
    }
    cout << '\n';
    vector<long long> res;
    while (!q1.empty() || !q2.empty() || !q3.empty()) { res.push_back(get_max() + increment); }
    for (int i = 0; i < res.size(); i++) {
        if ((i + 1) % t == 0) { cout << res[i] << (i + 1 == res.size() ? '\n' : ' '); }
    }
    return 0;
}
