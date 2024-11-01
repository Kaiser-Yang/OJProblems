// problem statement: https://www.luogu.com.cn/problem/P3358

#include <bits/stdc++.h>

constexpr int MAXN = 500 + 10;
constexpr int MAXK = 3 + 2;
constexpr int MAXR = 1e5 + 10;
constexpr int INF = 0x3f3f3f3f;

using namespace std;

int n, k;
int l[MAXN], r[MAXN];
int s, t, s1, ecnt;
int head[MAXR], cur[MAXR], dis[MAXR];
bool vis[MAXR];

struct Graph {
    int to, nex, capacity, cost;
} es[MAXN * MAXN * 2];

void addFlow(int u, int v, int capacity, int cost) {
    es[ecnt] = {v, head[u], capacity, cost};
    head[u] = ecnt++;
    es[ecnt] = {u, head[v], 0, -cost};
    head[v] = ecnt++;
}

bool spfa() {
    memset(dis, 0x3f, sizeof(dis));
    auto &inq = vis;
    queue<int> q;
    q.push(s);
    dis[s] = 0;
    inq[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int i = head[u]; i != -1; i = es[i].nex) {
            int v = es[i].to;
            if (es[i].capacity > 0 && dis[v] > dis[u] - es[i].cost) {
                dis[v] = dis[u] - es[i].cost;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
        }
    }
    return dis[t] != INF;
}

int dfs(int u, int inFlow, pair<int, int> &ans) {
    if (u == t || inFlow == 0) { return inFlow; }
    vis[u] = true;
    int outFlow = 0;
    for (int &i = cur[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (vis[v] || es[i].capacity == 0 || dis[v] != dis[u] - es[i].cost) { continue; }
        int delta = dfs(v, min(es[i].capacity, inFlow - outFlow), ans);
        if (delta > 0) {
            es[i].capacity -= delta;
            es[i ^ 1].capacity += delta;
            ans.second += delta * es[i].cost;
            outFlow += delta;
            if (inFlow == outFlow) { break; }
        }
    }
    vis[u] = false;
    return outFlow;
}

pair<int, int> MCMFDinic() {
    pair<int, int> ans{0, 0};
    int flow = 0;
    while (spfa()) {
        memcpy(cur, head, sizeof(head));
        while ((flow = dfs(s, INF, ans)) != 0) { ans.first += flow; }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    memset(head, 0xff, sizeof(head));
    cin >> n >> k;
    s = 0, s1 = 1e5 + 1, t = 1e5 + 2;
    addFlow(s, s1, k, 0);
    for (int i = 0; i < n; i++) { cin >> l[i] >> r[i]; }
    for (int i = 0; i < n; i++) {
        addFlow(s1, l[i], 1, 0);
        addFlow(l[i], r[i], 1, r[i] - l[i]);
        addFlow(r[i], t, 1, 0);
        for (int j = i + 1; j < n; j++) {
            if (l[j] >= r[i]) {
                addFlow(r[i], l[j], 1, 0);
            } else if (l[i] >= r[j]) {
                addFlow(r[j], l[i], 1, 0);
            }
        }
    }
    cout << MCMFDinic().second << "\n";
    return 0;
}
