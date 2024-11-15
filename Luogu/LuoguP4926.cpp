// problem statement: https://www.luogu.com.cn/problem/P4926
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1010;
constexpr int MAXS = 1010;
constexpr double EPS = 1e-6;

int n, s, t, c, x;
int o[MAXN], a[MAXN], b[MAXN], k[MAXN];
double ans = numeric_limits<double>::min();
double dis[MAXN];
double l, r = numeric_limits<double>::max();

struct Edge {
    int u, v;
    double w;
};

vector<Edge> edge;

void addEdge(int u, int v, double w) { edge.push_back({u, v, w}); }

bool bellmanFord(double res) {
    for (int i = 0; i < s; i++) {
        if (o[i] == 1) {
            edge[i].w = -log(k[i] - res);
        } else {
            edge[i].w = log(k[i] + res) - EPS;
        }
    }
    fill(dis, dis + 1 + n, numeric_limits<double>::max() / 2);
    dis[0] = 0;
    bool flag = false;
    for (int i = 0; i <= n; i++) {
        flag = false;
        for (auto e : edge) {
            int u = e.u, v = e.v;
            double w = e.w;
            if (dis[v] > dis[u] + w + EPS) {
                dis[v] = dis[u] + w;
                flag = true;
            }
        }
        if (!flag) { break; }
    }
    return flag;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> s >> t;
    for (int i = 0; i < s; i++) {
        cin >> o[i] >> a[i] >> b[i] >> k[i];
        if (o[i] == 1) {
            addEdge(a[i], b[i], -log(k[i]));
        } else {
            addEdge(a[i], b[i], log(k[i]) - EPS);
        }
        if (o[i] == 1) { r = min(r, (double)k[i]); }
    }
    for (int i = 0; i < t; i++) {
        cin >> c >> x;
        addEdge(0, c, log(x));
        addEdge(c, 0, -log(x));
    }
    for (int i = 1; i <= n; i++) { addEdge(0, i, numeric_limits<double>::max() / 2); }
    if (!bellmanFord(EPS)) {
        cout << "-1\n";
        return 0;
    }
    while (l <= r - EPS) {
        double mid = (l + r) / 2;
        if (!bellmanFord(mid)) {
            r = mid - EPS;
        } else {
            l = mid + EPS;
            ans = mid;
        }
    }
    cout << fixed << setprecision(10) << ans << endl;
    return 0;
}
