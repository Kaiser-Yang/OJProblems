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
