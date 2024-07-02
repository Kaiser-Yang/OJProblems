// problem statement: https://www.luogu.com.cn/problem/P1251

#include <bits/stdc++.h>

constexpr int MAXN      = 2e3 + 10;
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;

using namespace std;

int n, P, M, F, N, S;
int needTowel[MAXN];
int head[2 * MAXN], cur[2 * MAXN];
long long dis[2 * MAXN];
bool vis[2 * MAXN];
int s, t, ecnt;

struct Graph {
    int to, nex, capacity;
    long long cost;
} es[12 * MAXN];

void addFlow(int u, int v, int capacity, long long cost) {
    es[ecnt] = {v, head[u], capacity, cost};
    head[u]  = ecnt++;
    es[ecnt] = {u, head[v], 0, -cost};
    head[v]  = ecnt++;
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
            if (es[i].capacity > 0 && dis[v] > dis[u] + es[i].cost) {
                dis[v] = dis[u] + es[i].cost;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
        }
    }
    return dis[t] != INF;
}

int dfs(int u, int inFlow, pair<int, long long> &ans) {
    if (u == t || inFlow == 0) { return inFlow; }
    vis[u]      = true;
    int outFlow = 0;
    for (int &i = cur[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (vis[v] || es[i].capacity == 0 || dis[v] != dis[u] + es[i].cost) { continue; }
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

pair<int, long long> MCMFDinic() {
    pair<int, long long> ans{0, 0};
    int flow = 0;
    while (spfa()) {
        memcpy(cur, head, sizeof(head));
        while ((flow = dfs(s, 0x3f3f3f3f, ans)) != 0) { ans.first += flow; }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    memset(head, 0xff, sizeof(head));
    cin >> n;
    for (int i = 1; i <= n; i++) { cin >> needTowel[i]; }
    cin >> P >> M >> F >> N >> S;
    s = 0, t = 2 * n + 1;
    for (int i = 1; i <= n; i++) {
        addFlow(s, i + n, needTowel[i], 0);  // get dirty towels.
        addFlow(s, i, needTowel[i], P);      // buy new towels
        addFlow(i, t, needTowel[i], 0);
        if (i + 1 <= n) { addFlow(i + n, i + 1 + n, 0x3f3f3f3f, 0); }
        if (i + M <= n) { addFlow(i + n, i + M, 0x3f3f3f3f, F); }
        if (i + N <= n) { addFlow(i + n, i + N, 0x3f3f3f3f, S); }
    }
    cout << MCMFDinic().second << "\n";
    return 0;
}
