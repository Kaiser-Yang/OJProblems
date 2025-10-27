// problem statement: https://www.luogu.com.cn/problem/P3372

#include <array>
#include <cstdint>
#include <iostream>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

template <typename fenwick_tree_node>
class fenwick_tree {
public:
    fenwick_tree(int n, int m) : n(n), m(m), node(n, m) {}

    fenwick_tree(int n) : n(n), node(n) {}

    template <typename T>
    void update(int x, T delta) {
        for (int i = x + 1; i <= n; i += lowbit(i)) { node.update(i, delta, x + 1); }
    }

    template <typename T>
    void update(int x, int y, T delta) {
        for (int i = x + 1; i <= n; i += lowbit(i)) {
            for (int j = y + 1; j <= m; j += lowbit(j)) { node.update(i, j, delta, x + 1, y + 1); }
        }
    }

    // [0, x)
    auto query(int x) {
        auto res = node.get_zero();
        for (int i = x; i > 0; i -= lowbit(i)) { node.query(i, x, res); }
        return res;
    }

    // [0, x) * [0, y)
    auto query(int x, int y) {
        auto res = node.get_zero();
        for (int i = x; i > 0; i -= lowbit(i)) {
            for (int j = y; j > 0; j -= lowbit(j)) { node.query(i, j, x, y, res); }
        }
        return res;
    }

private:
    int lowbit(int x) { return x & -x; }

    int n, m;
    fenwick_tree_node node;
};

constexpr int MAXN = 1e5;

struct node {
    node(int n) {}

    i64 get_zero() { return 0; }

    void update(int i, i64 delta, int x) {
        t1[i] += delta;
        t2[i] += (x - 1) * delta;
    }

    void query(int i, int x, i64 &res) { res += x * t1[i] - t2[i]; }

    std::array<i64, MAXN + 1> t1, t2;
};

fenwick_tree<node> ft(MAXN);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<i64> a(n);
    for (int i = 0; i < n; i++) { std::cin >> a[i]; }
    for (int i = 0; i < n; i++) { ft.update(i, a[i] - (i - 1 >= 0 ? a[i - 1] : 0)); }
    for (int i = 0; i < m; i++) {
        int op, x, y;
        i64 delta;
        std::cin >> op >> x >> y;
        x--;
        if (op == 1) {
            std::cin >> delta;
            ft.update(x, delta);
            ft.update(y, -delta);
        } else {
            std::cout << ft.query(y) - ft.query(x) << '\n';
        }
    }
    return 0;
}
