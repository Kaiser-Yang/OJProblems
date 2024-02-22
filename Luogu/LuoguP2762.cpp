// problem statement: https://www.luogu.com.cn/problem/P2762

#include <bits/stdc++.h>

constexpr int MAXN = 50 + 10;
constexpr int MAXM = 50 + 10;
constexpr int  INF = std::numeric_limits<int>::max();

using namespace std;

int n, m, c, node, s, t, ans, ecnt;
string line;
int head[MAXN + MAXM], cur[MAXN + MAXM], depth[MAXN + MAXM];
bool ins[MAXN + MAXM];
vector<int> experiment[MAXM];

struct Graph
{
    int to, nex, capacity;
} es[MAXM * 2 + MAXM * 2 + MAXM * MAXN * 2];

void addEdge(int u, int v, int w)
{
    es[ecnt] = {v, head[u], w};
    head[u] = ecnt++;
}

bool bfs()
{
    memset(depth, 0, sizeof(depth));
    queue<int> q;
    depth[s] = 1;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = es[i].nex) {
            int v = es[i].to;
            if (depth[v] != 0 || es[i].capacity == 0) { continue; }
            depth[v] = depth[u] + 1;
            q.push(v);
        }
    }
    return depth[t] != 0;
}

int dfs(int u, int flow)
{
    if (u == t || flow == 0) { return flow; }
    int res = 0;
    for (int &i = cur[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (depth[v] != depth[u] + 1 || es[i].capacity == 0) { continue; }
        int outFlowV = dfs(v, min(flow - res, es[i].capacity));
        if (outFlowV > 0) {
            res += outFlowV;
            es[i].capacity -= outFlowV;
            es[i ^ 1].capacity += outFlowV;
            if (res == flow) { return flow; }
        }
    }
    return res;
}

int dinic()
{
    int res = 0;
    while (bfs()) {
        memcpy(cur, head, sizeof(head));
        res += dfs(s, INF);
    }
    return res;
}

void dfs(int u) 
{
    ins[u] = true;
    for (int i = head[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (ins[v] || es[i].capacity == 0) { continue; }
        dfs(v);
    }
}

int main()
{
	ios::sync_with_stdio(false);
    memset(head, 0xff, sizeof(head));
    cin >> m >> n;
    getline(cin, line);
    s = 0, t = n + 1;
    for (int i = 1; i <= m; i++) {
        getline(cin, line);
        stringstream ss(line);
        ss >> c;
        ans += c;
        int u = n + 1 + i;
        addEdge(s, u, c);
        addEdge(u, s, 0);
        while (ss >> node) {
            addEdge(u, node, INF);
            addEdge(node, u, 0);
            experiment[i].push_back(node);
        }
    }
    for (int i = 1; i <= n; i++) {
        cin >> c;
        addEdge(i, t, c);
        addEdge(t, i, 0);
    }
    ans -= dinic();
    dfs(s);
    for (int i = 1; i <= m; i++) {
        bool done = true;
        for (const int &node : experiment[i]) {
            if (!ins[node]) {
                done = false;
                break;
            }
        }
        if (done) { cout << i << " "; }
    }
    cout << "\n";
    for (int i = 1; i <= n; i++) {
        if (!ins[i]) { continue; }
        cout << i << " ";
    }
    cout << "\n";
    cout << ans << "\n";
	return 0;
}
