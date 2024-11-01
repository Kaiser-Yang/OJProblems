// problem statement:

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e6 + 10;
constexpr int MAXM = 5e6 + 10;

int n, m, ecnt, ans;
int price[MAXN], head[MAXN * 3], dis[MAXN * 3];
bool inq[MAXN * 3];

struct Edge {
    int to, w, nex;
} es[MAXM * 10];

void addEdge(int u, int v, int w) {
    es[ecnt].to = v;
    es[ecnt].w = w;
    es[ecnt].nex = head[u];
    head[u] = ecnt++;
}

// TODO update wrong codes
void SPFA() {
    struct Compare {
        bool operator()(const int a, const int b) { return dis[a] > dis[b]; }
    };
    priority_queue<int, vector<int>, Compare> q;
    fill(dis, dis + 3 * n + 1, std::numeric_limits<int>::min() / 2);
    memset(inq, 0, sizeof(inq));
    dis[1] = 0;
    q.push(1);
    inq[1] = true;
    while (!q.empty()) {
        int u = q.top();
        q.pop();
        inq[u] = false;
        for (int i = head[u]; i != -1; i = es[i].nex) {
            int v = es[i].to;
            if (dis[v] < dis[u] + es[i].w) {
                dis[v] = dis[u] + es[i].w;
                if (inq[v]) { continue; }
                q.push(v);
                inq[v] = true;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    memset(head, -1, sizeof(head));
    cin >> n >> m;
    for (int i = 1; i <= n; i++) { cin >> price[i]; }
    for (int i = 0; i < m; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        addEdge(u, v, 0);
        addEdge(u + n, v + n, 0);
        addEdge(u + 2 * n, v + 2 * n, 0);
        addEdge(u, u + n, -price[u]);
        addEdge(u + n, u + 2 * n, price[u]);
        addEdge(v, v + n, -price[v]);
        addEdge(v + n, v + 2 * n, price[v]);
        if (t == 2) {
            addEdge(v, u, 0);
            addEdge(v + n, u + n, 0);
            addEdge(v + 2 * n, u + 2 * n, 0);
        }
    }
    SPFA();
    cout << dis[3 * n] << endl;
    return 0;
}