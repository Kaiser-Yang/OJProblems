// problem statement: https://www.luogu.com.cn/problem/P1993
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 5e3 + 10;

int n, m, op, a, b, c;
int dis[MAXN];

struct Edge {
    int u, v, w;
};

vector<Edge> edge;

void addEdge(int u, int v, int w) { edge.push_back({u, v, w}); }

bool bellmanFord() {
    memset(dis, 0x3f, sizeof(dis));
    dis[0]    = 0;
    bool flag = false;
    for (int i = 0; i <= n; i++) {
        flag = false;
        for (auto e : edge) {
            int u = e.u, v = e.v, w = e.w;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                flag   = true;
            }
        }
        if (!flag) { break; }
    }
    return flag;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> op;
        if (op == 1) {
            cin >> a >> b >> c;
            addEdge(a, b, -c);
        } else if (op == 2) {
            cin >> a >> b >> c;
            addEdge(b, a, c);
        } else {
            cin >> a >> b;
            addEdge(a, b, 0);
            addEdge(b, a, 0);
        }
    }
    for (int i = 1; i <= n; i++) { addEdge(0, i, 0); }
    cout << (bellmanFord() ? "No" : "Yes") << endl;
    return 0;
}
