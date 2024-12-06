// problem statement: https://codeforces.com/contest/2050/problem/D

#include <bits/stdc++.h>

using namespace std;

int T;
string s;

struct {
    vector<int> max_val, lazy, pos;

    void push_up(int id) {
        if (max_val[id * 2] >= max_val[id * 2 + 1]) {
            max_val[id] = max_val[id * 2];
            pos[id] = pos[id * 2];
        } else {
            max_val[id] = max_val[id * 2 + 1];
            pos[id] = pos[id * 2 + 1];
        }
        lazy[id] = 0;
    }

    void push_down(int id) {
        if (lazy[id] != 0) {
            max_val[id * 2] += lazy[id];
            lazy[id * 2] += lazy[id];
            max_val[id * 2 + 1] += lazy[id];
            lazy[id * 2 + 1] += lazy[id];
            lazy[id] = 0;
        }
    }

    void build(int id = 1, int l = 0, int r = s.size() - 1) {
        if (l == r) {
            if (max_val.size() != s.size() * 4) {
                pos.resize(s.size() * 4);
                max_val.resize(s.size() * 4);
                lazy.resize(s.size() * 4);
            }
            max_val[id] = s[l] - l;
            pos[id] = l;
            lazy[id] = 0;
            return;
        }
        int mid = (l + r) / 2;
        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);
        push_up(id);
    }

    pair<int, int> query(int x, int y, int id = 1, int l = 0, int r = s.size() - 1) {
        if (x <= l && r <= y) { return {max_val[id], pos[id]}; }
        push_down(id);
        int mid = (l + r) / 2;
        pair<int, int> res = {numeric_limits<int>::min(), numeric_limits<int>::max()};
        if (x <= mid) { res = query(x, y, id * 2, l, mid); }
        if (y > mid) {
            auto tmp = query(x, y, id * 2 + 1, mid + 1, r);
            if (res.first < tmp.first) {
                res = tmp;
            } else if (res.first == tmp.first) {
                res.second = min(res.second, tmp.second);
            }
        }
        return res;
    }

    void set(int x, int val, int id = 1, int l = 0, int r = s.size() - 1) {
        if (l > x || r < x) { return; }
        if (l == r) {
            max_val[id] = val;
            return;
        }
        push_down(id);
        int mid = (l + r) / 2;
        if (x <= mid) { set(x, val, id * 2, l, mid); }
        if (x > mid) { set(x, val, id * 2 + 1, mid + 1, r); }
        push_up(id);
    }

    void update(int x, int y, int delta, int id = 1, int l = 0, int r = s.size() - 1) {
        if (x > y) { return; }
        if (x <= l && r <= y) {
            max_val[id] += delta;
            lazy[id] += delta;
            return;
        }
        push_down(id);
        int mid = (l + r) / 2;
        if (x <= mid) { update(x, y, delta, id * 2, l, mid); }
        if (y > mid) { update(x, y, delta, id * 2 + 1, mid + 1, r); }
        push_up(id);
    }
} seg;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> s;
        seg.build();
        for (int i = 0; i < s.size(); i++) {
            auto tmp = seg.query(0, s.size() - 1);
            cout << (char)tmp.first;
            seg.update(tmp.second + 1, s.size() - 1, 1);
            seg.set(tmp.second, numeric_limits<int>::min());
        }
        cout << '\n';
    }
    return 0;
}
