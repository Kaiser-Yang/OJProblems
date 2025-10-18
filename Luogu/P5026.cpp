// problem statement: https://www.luogu.com.cn/problem/P5026

#include <cassert>
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
    std::vector<i64> a(m);
    auto update = [&](int l, int r, int s, int e) {
        if (l > m || r < 0) { return; }
        auto d = e > s ? 1 : -1;
        if (l < 0) {
            s += d * (-l);
            l = 0;
        }
        if (r > m) {
            e -= d * (r - m);
            r = m;
        }
        if (l >= r) { return; }
        assert(std::abs(e - s) == r - l - 1);
        a[l] += s;
        if (l + 1 < m) {
            a[l + 1] -= s;
            a[l + 1] += d;
        }
        if (r < m) {
            a[r] -= d;
            a[r] -= e;
        }
        if (r + 1 < m) { a[r + 1] += e; }
    };
    for (int i = 0; i < n; i++) {
        int v, x;
        std::cin >> v >> x;
        x--;
        // 3, 1
        update(x - 3 * v, x - 2 * v, 0, v - 1);
        update(x - 2 * v, x - v, v, 1);
        update(x - v, x, 0, -v + 1);
        update(x, x + v, -v, -1);
        update(x + v, x + 2 * v, 0, v - 1);
        update(x + 2 * v, x + 3 * v, v, 1);
    }
    for (int i = 1; i < m; i++) { a[i] += a[i - 1]; }
    for (int i = 1; i < m; i++) { a[i] += a[i - 1]; }
    for (int i = 0; i < m; i++) { std::cout << a[i] << " \n"[i == m - 1]; }
    return 0;
}
