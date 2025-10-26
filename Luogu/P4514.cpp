// problem statement: https://www.luogu.com.cn/problem/P4514

#include <array>
#include <cassert>
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

    template <typename T>
    void update(int x, int y, T delta) {
        for (int i = x + 1; i <= n; i += lowbit(i)) {
            for (int j = y + 1; j <= m; j += lowbit(j)) { node.update(i, j, delta, x + 1, y + 1); }
        }
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

constexpr int MAXN = 2048, MAXM = 2048;
struct sum_node {
    sum_node(int n, int m) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                t1[i][j] = 0;
                t2[i][j] = 0;
                t3[i][j] = 0;
                t4[i][j] = 0;
            }
        }
    }

    int get_zero() { return 0; }

    template <typename T>
    void update(int i, int j, T delta, int x, int y) {
        t1[i][j] += delta;
        t2[i][j] += delta * (x - 1);
        t3[i][j] += delta * (y - 1);
        t4[i][j] += delta * (x - 1) * (y - 1);
    }

    void query(int i, int j, int x, int y, int &res) {
        res += t1[i][j] * x * y - t2[i][j] * y - t3[i][j] * x + t4[i][j];
    }

    std::array<std::array<int, MAXM + 1>, MAXN + 1> t1, t2, t3, t4;
    int n, m;
};
fenwick_tree<sum_node> ft(MAXN, MAXM);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string op;
    int n, m;
    std::cin >> op >> n >> m;
    while (std::cin >> op) {
        if (op == "L") {
            int a, b, c, d, delta;
            std::cin >> a >> b >> c >> d >> delta;
            a--;
            b--;
            ft.update(a, b, delta);
            ft.update(a, d, -delta);
            ft.update(c, b, -delta);
            ft.update(c, d, delta);
        } else if (op == "k") {
            int a, b, c, d;
            std::cin >> a >> b >> c >> d;
            a--;
            b--;
            std::cout << ft.query(c, d) - ft.query(a, d) - ft.query(c, b) + ft.query(a, b) << "\n";
        } else {
            assert(false);
        }
    }
    return 0;
}
