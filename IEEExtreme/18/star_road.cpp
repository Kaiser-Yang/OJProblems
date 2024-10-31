#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;

int n, ans = 1;
int star[MAXN], tmp[MAXN], len;
vector<int> g[MAXN];

struct {
    enum QUERY_TYPE { LIS, LDS, MAX_LEN };
    int cnt;
    int lc[MAXN * 20], rc[MAXN * 20], val[MAXN * 20][MAX_LEN], rt[MAXN * 20];

    int get_new_node() {
        if (cnt + 1 == MAXN * 20) { exit(-1); }
        return ++cnt;
    }

    void push_up(int id) {
        val[id][LIS] = max(val[lc[id]][LIS], val[rc[id]][LIS]);
        val[id][LDS] = max(val[lc[id]][LDS], val[rc[id]][LDS]);
    }

    int query(int ql, int qr, QUERY_TYPE type, int id, int l = 1, int r = len) {
        if (id == 0 || ql < 1 || qr > len || qr < ql) return 0;
        if (ql <= l && r <= qr) return val[id][type];
        int mid = (l + r) >> 1, res = 0;
        if (ql <= mid) { res = max(res, query(ql, qr, type, lc[id], l, mid)); }
        if (qr > mid) { res = max(res, query(ql, qr, type, rc[id], mid + 1, r)); }
        return res;
    }

    void update(int pos, int v, QUERY_TYPE type, int &id, int l = 1, int r = len) {
        if (id == 0) { id = get_new_node(); }
        if (l == r) {
            val[id][type] = max(val[id][type], v);
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) {
            update(pos, v, type, lc[id], l, mid);
        } else {
            update(pos, v, type, rc[id], mid + 1, r);
        }
        push_up(id);
    }

    int merge(int a, int b, int l = 1, int r = len) {
        // this part is for considering we do not choose u
        // if we do not choose u, the result must be the sum the maximum value of LIS and LDS
        // we can get one LIS ended between [l, mid], ans one LDS ended between [mid + 1, r]
        // then we can get the maximum value of LIS and LDS by merging the two parts
        ans = max({ans, val[lc[a]][LIS] + val[rc[b]][LDS], val[rc[a]][LDS] + val[lc[b]][LIS]});
        if (a == 0 || b == 0) return a + b;
        if (l == r) {
            val[a][LIS] = max(val[a][LIS], val[b][LIS]);
            val[a][LDS] = max(val[a][LDS], val[b][LDS]);
            return a;
        }
        int mid = (l + r) >> 1;
        lc[a] = merge(lc[a], lc[b], l, mid);
        rc[a] = merge(rc[a], rc[b], mid + 1, r);
        push_up(a);
        return a;
    }

} seg;

void dfs(int u, int par) {
    seg.rt[u] = seg.get_new_node();
    for (int v : g[u]) {
        if (v == par) continue;
        dfs(v, u);
    }
    // son.first = LIS, son.second = LDS
    vector<pair<int, int>> son;
    int max_LIS = 1, max_LDS = 1;
    for (int v : g[u]) {
        if (v == par) continue;
        son.push_back({seg.query(1, star[u] - 1, seg.LIS, seg.rt[v]) + 1,
                       seg.query(star[u] + 1, len, seg.LDS, seg.rt[v]) + 1});
        max_LIS = max(max_LIS, son.back().first);
        max_LDS = max(max_LDS, son.back().second);
        seg.rt[u] = seg.merge(seg.rt[u], seg.rt[v]);
    }
    if (son.size() == 1) {
        ans = max({ans, max_LIS, max_LDS});
    } else if (son.size() > 1) {
        sort(son.begin(), son.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
            if (a.first == b.first) { return a.second < b.second; }
            return a.first > b.first;
        });
        ans = max(ans, son[0].first + son[1].second - 1);
        sort(son.begin(), son.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
            if (a.second == b.second) { return a.first < b.first; }
            return a.second > b.second;
        });
        ans = max(ans, son[0].second + son[1].first - 1);
    }
    seg.update(star[u], max_LIS, seg.LIS, seg.rt[u]);
    seg.update(star[u], max_LDS, seg.LDS, seg.rt[u]);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> star[i];
        tmp[i] = star[i];
    }
    sort(tmp + 1, tmp + n + 1);
    len = unique(tmp + 1, tmp + n + 1) - tmp - 1;
    for (int i = 1; i <= n; i++) { star[i] = lower_bound(tmp + 1, tmp + len + 1, star[i]) - tmp; }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    cout << ans << endl;
    return 0;
}
