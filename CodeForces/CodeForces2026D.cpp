// problem statement: https://codeforces.com/contest/2026/problem/D

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 3e5 + 5;

int n, q;
long long a[MAXN], b[MAXN];

pair<int, int> get_block_idx(long long x) {
    int reverse_idx = ceil((-1 + sqrt(1 + 8LL * ((1LL + n) * n / 2 - x + 1))) / 2);
    return {n - reverse_idx + 1,
            (1LL + reverse_idx) * reverse_idx / 2 - ((1LL + n) * n / 2 - x + 1) + 1};
}

long long query(long long l, long long r) {
    auto idx_l = get_block_idx(l), idx_r = get_block_idx(r);
    long long sum = b[idx_r.first] - b[idx_l.first - 1];
    idx_l.second--;
    sum -= a[idx_l.first + idx_l.second - 1] - a[idx_l.first - 1] -
           (idx_l.first - 2 >= 0 ? (a[idx_l.first - 1] - a[idx_l.first - 2]) * idx_l.second : 0);
    sum -= b[idx_r.first] - b[idx_r.first - 1] -
           (a[idx_r.first + idx_r.second - 1] - a[idx_r.first - 1] -
            (idx_r.first - 2 >= 0 ? (a[idx_r.first - 1] - a[idx_r.first - 2]) * idx_r.second : 0));
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) { cin >> a[i]; }
    for (int i = n; i >= 1; i--) { b[i] = b[i + 1] + (n - i + 1) * a[i]; }
    for (int i = 1; i <= n; i++) { b[i] += b[i - 1]; }
    for (int i = 1; i <= n; i++) { a[i] += a[i - 1]; }
    for (int i = 1; i <= n; i++) { a[i] += a[i - 1]; }
    cin >> q;
    long long l = 0, r = 0;
    while (q--) {
        cin >> l >> r;
        cout << query(l, r) << '\n';
    }
    return 0;
}
