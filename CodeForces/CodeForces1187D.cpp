// problem statement: https: https://codeforces.com/contest/1187/problem/D

#include <bits/stdc++.h>

using namespace std;

int T, n, b;
vector<int> a;
vector<list<int>> p;

struct {
    int cnt = 0, rt = 0;
    vector<int> ls, rs, val;

    void clear() {
        cnt = 0;
        rt = 0;
        ls.clear();
        rs.clear();
        val.clear();
    }

    int get_next_node() {
        ls.push_back(0);
        rs.push_back(0);
        val.push_back(0);
        return ++cnt;
    }

    void push_up(int id) { val[id] = min(val[ls[id]], val[rs[id]]); }

    int build(const vector<int> &a, int id = 1, int l = 1, int r = n) {
        if (rt == 0) {
            ls.resize(1);
            rs.resize(1);
            val.resize(1);
            ls[0] = rs[0] = val[0] = 0;
            rt = get_next_node();
        }
        if (id == 0) { id = get_next_node(); }
        if (l == r) {
            val[id] = a[l];
            return id;
        }
        int m = l + (r - l) / 2;
        ls[id] = build(a, ls[id], l, m);
        rs[id] = build(a, rs[id], m + 1, r);
        push_up(id);
        return id;
    }

    void update(int x, int new_val, int id = 1, int l = 1, int r = n) {
        if (l == r) {
            val[id] = new_val;
            return;
        }
        int m = l + (r - l) / 2;
        if (x <= m) {
            update(x, new_val, ls[id], l, m);
        } else {
            update(x, new_val, rs[id], m + 1, r);
        }
        push_up(id);
    }

    int query(int L, int R, int id = 1, int l = 1, int r = n) {
        if (r < L || l > R) { return numeric_limits<int>::max(); }
        if (L <= l && r <= R) { return val[id]; }
        int m = l + (r - l) / 2;
        return min(query(L, R, ls[id], l, m), query(L, R, rs[id], m + 1, r));
    }
} seg;

int main() {
    cin >> T;
    while (T--) {
        cin >> n;
        p.clear();
        p.resize(n + 1);
        a.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            p[a[i]].push_back(i);
        }
        seg.clear();
        seg.build(a);
        bool ok = true;
        for (int i = 1; i <= n; i++) {
            cin >> b;
            if (!ok) { continue; }
            if (p[b].size() == 0) {
                ok = false;
                continue;
            }
            int pos = p[b].front();
            p[b].pop_front();
            if (seg.query(1, pos) == b) {
                seg.update(pos, numeric_limits<int>::max());
                continue;
            }
            ok = false;
        }
        if (ok) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
