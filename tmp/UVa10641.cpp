#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<pair<int, int>> p;

struct Light {
    int x, y;
    long long cost;
};
vector<Light> l;
vector<vector<long long>> d;
constexpr long long INF = numeric_limits<long long>::max() / 10;

// dot2Vec
template <typename T>
pair<double, double> dot2Vec(const pair<T, T> &vec1, const pair<T, T> &vec2) {
    return make_pair(vec2.first - vec1.first, vec2.second - vec1.second);
}

// cross product
template <typename T>
double crossProduct(const pair<T, T> &vec1, const pair<T, T> &vec2) {
    return 1.0 * vec1.first * vec2.second - 1.0 * vec1.second * vec2.first;
}

// check if current light can cover [left~right]
bool check(int cur, int left, int right) {
    vector<bool> cover(n, false);
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        cover[i] = crossProduct(dot2Vec(p[i], p[j]), dot2Vec(p[i], {l[cur].x, l[cur].y})) < 0;
    }
    for (int i = left; i <= right; i++) {
        if (!cover[i % n]) { return false; }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n && n != 0) {
        p.resize(n);
        for (int i = 0; i < n; i++) { cin >> p[i].first >> p[i].second; }
        cin >> m;
        l.resize(m);
        for (int i = 0; i < m; i++) { cin >> l[i].x >> l[i].y >> l[i].cost; }
        d.clear();
        d.resize(2 * n);
        for (int i = 0; i < 2 * n; i++) { d[i].resize(2 * n, INF); }
        for (int len = 1; len <= n; len++) {
            for (int left = 0; left < n; left++) {
                int right = left + len - 1;
                for (int i = 0; i < m; i++) {
                    if (check(i, left, right)) { d[left][right] = min(d[left][right], l[i].cost); }
                }
                for (int k = left; k < right; k++) {
                    if (d[left][k] >= INF || d[k + 1][right] >= INF) { continue; }
                    d[left][right] = min(d[left][right], d[left][k] + d[k + 1][right]);
                }
            }
        }
        long long ans = INF;
        for (int i = 0; i < n; i++) { ans = min(ans, d[i][i + n - 1]); }
        if (ans >= INF) {
            cout << "Impossible.\n";
        } else {
            cout << ans << endl;
        }
    }
    return 0;
}