// problem statement: https://www.luogu.com.cn/problem/P4231

#include <cstdint>
#include <iostream>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<i64> a(n);
    auto update = [&](int l, int r, i64 s, i64 e) {
        i64 d = (e - s) / (r - l - 1);
        a[l] += s;
        if (l + 1 < n) {
            a[l + 1] -= s;
            a[l + 1] += d;
        }
        if (r < n) {
            a[r] -= d;
            a[r] -= e;
        }
        if (r + 1 < n) { a[r + 1] += e; }
    };
    for (int i = 0; i < m; i++) {
        int l, r;
        i64 s, e;
        std::cin >> l >> r >> s >> e;
        l--;
        update(l, r, s, e);
    }
    for (int i = 1; i < n; i++) { a[i] += a[i - 1]; }
    i64 ans1 = a[0], ans2 = a[0];
    for (int i = 1; i < n; i++) {
        a[i] += a[i - 1];
        ans1 ^= a[i];
        ans2 = std::max(ans2, a[i]);
    }
    std::cout << ans1 << ' ' << ans2 << '\n';
    return 0;
}
