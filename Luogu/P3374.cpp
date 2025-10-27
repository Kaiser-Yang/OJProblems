// problem statement: https://www.luogu.com.cn/problem/P3374

#include <array>
#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;

// API zero-indexed
// internal one-indexed
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

constexpr int MAXN = 5e5;
struct node {
    node(int n) {}
    int get_zero() { return 0; }

    void update(int i, int delta, int x) { tr[i] += delta; }

    void query(int i, int x, int &res) { res += tr[i]; }

    std::array<int, MAXN + 1> tr;
};
fenwick_tree<node> ft(MAXN);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int a;
        std::cin >> a;
        ft.update(i, a);
    }
    for (int i = 0; i < m; i++) {
        int op, x, y;
        std::cin >> op >> x >> y;
        x--;
        if (op == 1) {
            ft.update(x, y);
        } else {
            std::cout << ft.query(y) - ft.query(x) << "\n";
        }
    }
    return 0;
}
