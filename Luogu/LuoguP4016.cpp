// problem statement: https://www.luogu.com.cn/problem/P4016

#include <bits/stdc++.h>

constexpr int MAXN = 100 + 10;
constexpr int INF  = 0x3f3f3f3f;

using namespace std;

int n, s, t, ecnt;
array<int, MAXN> cargo, head, cur, dis;
array<bool, MAXN> vis;

struct Graph {
    int to, nex, capacity, cost;
} es[8 * MAXN];

void addEdge(int u, int v, int capacity, int cost) {
    es[ecnt] = {v, head[u], capacity, cost};
    head[u]  = ecnt++;
}

bool spfa() {
    fill(dis.begin(), dis.end(), INF);
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
            if (es[i].capacity > 0 && dis[v] > dis[u] + es[i].cost) {
                dis[v] = dis[u] + es[i].cost;
                if (!inq[v]) {
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return dis[t] != INF;
}

int dfs(int u, int inFlow, pair<int, int> &ans) {
    if (u == t || inFlow == 0) { return inFlow; }
    int outFLow = 0;
    vis[u]      = true;
    for (int &i = cur[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (vis[v] || es[i].capacity == 0 || dis[v] != dis[u] + es[i].cost) { continue; }
        int delta = dfs(v, min(es[i].capacity, inFlow - outFLow), ans);
        if (delta > 0) {
            es[i].capacity -= delta;
            es[i ^ 1].capacity += delta;
            ans.second += delta * es[i].cost;
            outFLow += delta;
            if (inFlow == outFLow) { break; }
        }
    }
    vis[u] = false;
    return outFLow;
}

pair<int, int> MCMFDinic() {
    pair<int, int> ans{0, 0};
    int flow = 0;
    while (spfa()) {
        cur = head;
        while ((flow = dfs(s, INF, ans)) != 0) { ans.first += flow; }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    fill(head.begin(), head.end(), -1);
    cin >> n;
    for (int i = 1; i <= n; i++) { cin >> cargo[i]; }
    int avg = accumulate(cargo.begin(), cargo.end(), 0) / n;
    s = 0, t = n + 1;
    for (int i = 1; i <= n; i++) {
        addEdge(s, i, cargo[i], 0);
        addEdge(i, s, 0, 0);
        addEdge(i, t, avg, 0);
        addEdge(t, i, 0, 0);
    }
    for (int i = 1; i <= n; i++) {
        int pre = i - 1, nex = i + 1;
        if (pre == 0) { pre = n; }
        if (nex == n + 1) { nex = 1; }
        addEdge(i, pre, INF, 1);
        addEdge(pre, i, 0, -1);
        addEdge(i, nex, INF, 1);
        addEdge(nex, i, 0, -1);
    }
    cout << MCMFDinic().second << "\n";
    return 0;
}
