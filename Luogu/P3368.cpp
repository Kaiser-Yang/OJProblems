// problem statement: https://www.luogu.com.cn/problem/P3368

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

constexpr int MAXN = 5e5;

struct node {
    node(int n) {}

    int get_zero() { return 0; }

    void update(int i, int delta, int x) { tr[i] += delta; }

    void query(int i, int x, int &res) { res += tr[i]; }

    std::array<int, MAXN> tr;
};

fenwick_tree<node> ft(MAXN);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, M;
    std::cin >> N >> M;
    std::vector<int> a(N);
    for (int i = 0; i < N; i++) { std::cin >> a[i]; }
    for (int i = 0; i < N; i++) { ft.update(i, a[i] - (i - 1 >= 0 ? a[i - 1] : 0)); }
    for (int i = 0; i < M; i++) {
        int op;
        std::cin >> op;
        if (op == 1) {
            int x, y, k;
            std::cin >> x >> y >> k;
            x--;
            ft.update(x, k);
            ft.update(y, -k);
        } else {
            int x;
            std::cin >> x;
            std::cout << ft.query(x) << '\n';
        }
    }
    return 0;
}
