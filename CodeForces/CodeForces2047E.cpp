// problem statement: https://codeforces.com/contest/2047/problem/E

#include <bits/stdc++.h>

using namespace std;

constexpr int MAX_N = 2e5;

int T, n;
vector<int> x, y;
vector<pair<int, int>> coordinate;
vector<int> discrete;
pair<int, int> res;

struct {
    vector<int> val = vector<int>(MAX_N + 1, 0);

    int lowbit(int x) { return x & -x; }

    void update(int x, int delta) {
        for (int i = x; i < MAX_N; i += lowbit(i)) { val[i] += delta; }
    }

    int sum(int x) {
        int res = 0;
        for (int i = x; i; i -= lowbit(i)) { res += val[i]; }
        return res;
    }

    int sum_lower_bound(int x) {
        int l = 1, r = MAX_N - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (sum(mid) >= x) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return l;
    }
} l, r;

bool check(int now) {
    if (now == 0) { return true; }
    for (int i = 0; i < n; i++) { l.val[i] = r.val[i] = 0; }
    for (int i = 0; i < n; i++) { r.update(discrete[i], 1); }
    for (int i = 0; i < n; i++) {
        l.update(discrete[i], 1);
        r.update(discrete[i], -1);
        if (i + 1 < n && coordinate[i + 1].first == coordinate[i].first) { continue; }
        if (i + 1 >= 2 * now && n - (i + 1) >= 2 * now) {
            int l1 = l.sum_lower_bound(now), r1 = l.sum_lower_bound(i + 1 - now + 1) - 1;
            int l2 = r.sum_lower_bound(now), r2 = r.sum_lower_bound(n - (i + 1) - now + 1) - 1;
            int left_bound = max(l1, l2), right_bound = min(r1, r2);
            if (left_bound <= right_bound) {
                res = {coordinate[i].first + 1, y[left_bound - 1] + 1};
                return true;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        res = {0, 0};
        x.resize(n);
        y.resize(n);
        coordinate.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> x[i] >> y[i];
            coordinate[i] = {x[i], y[i]};
        }
        sort(x.begin(), x.end());
        sort(y.begin(), y.end());
        x.erase(unique(x.begin(), x.end()), x.end());
        y.erase(unique(y.begin(), y.end()), y.end());
        map<int, int> id_x, id_y;
        for (int i = 0; i < x.size(); i++) { id_x[x[i]] = i + 1; }
        for (int i = 0; i < y.size(); i++) { id_y[y[i]] = i + 1; }
        sort(coordinate.begin(), coordinate.end());
        discrete.resize(n);
        for (int i = 0; i < n; i++) {
            discrete[i] = id_y[coordinate[i].second];
        }
        int l = 0, r = n / 4;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (check(mid)) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        cout << l - 1 << "\n";
        cout << res.first << " " << res.second << "\n";
    }
    return 0;
}
