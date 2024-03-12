// problem statement: https://www.luogu.com.cn/problem/P2766

constexpr int MAXN = 500 + 10;
constexpr int  INF = 0x3f3f3f3f;

#include <bits/stdc++.h>

using namespace std;

int n, ans;
int num[MAXN], dp[MAXN];
int s, t, ecnt;
int head[2 * MAXN], cur[2 * MAXN], depth[2 * MAXN];

struct Graph
{
    int to, nex, capacity;
} es[MAXN * MAXN * 2];

void addEdge(int u, int v, int capacity)
{
    es[ecnt] = {v, head[u], capacity};
    head[u] = ecnt++;
}

bool bfs()
{
    memset(depth, 0xff, sizeof(depth));
    queue<int> q;
    depth[s] = 0;
    q.push(s);
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = es[i].nex) {
            int v = es[i].to;
            if (es[i].capacity == 0 || depth[v] != -1) { continue; }
            depth[v] = depth[u] + 1;
            q.push(v);
        }
    }
    return depth[t] != -1;
}

int dfs(int u, int inFlow)
{
    if (u == t || inFlow == 0) { return inFlow; }
    int outFlow = 0;
    for (int &i = cur[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (es[i].capacity == 0 || depth[v] != depth[u] + 1) { continue; }
        int delta = dfs(v, min(es[i].capacity, inFlow - outFlow));
        if (delta > 0) {
            es[i].capacity -= delta;
            es[i ^ 1].capacity += delta;
            outFlow += delta;
            if (inFlow == outFlow) { break; }
        }
    }
    return outFlow;
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

int main()
{
	ios::sync_with_stdio(false);
    memset(head, 0xff, sizeof(head));
    cin >> n;
    for (int i = 1; i <= n; i++) { cin >> num[i]; }
    if (n == 1) {
        cout << "1\n1\n1\n";
        return 0;
    }
    dp[n] = 1;
    for (int i = n - 1; i >= 1; i--) {
        dp[i] = 1;
        for (int j = n; j > i; j--) {
            if (num[i] <= num[j]) { dp[i] = max(dp[i], dp[j] + 1); }
        }
    }
    for (int i = 1; i <= n; i++) { ans = max(ans, dp[i]); }
    cout << ans << "\n";
    s = 0, t = 2 * n + 1;
    for (int i = 1; i <= n; i++) {
        addEdge(i, i + n, 1);
        addEdge(i + n, i, 0);
        if (dp[i] == ans) {
            addEdge(s, i, 1);
            addEdge(i, s, 0);
        }
        if (dp[i] == 1) {
            addEdge(i + n, t, 1);
            addEdge(t, i + n, 0);
        }
        for (int j = i + 1; j <= n; j++) {
            if (num[i] <= num[j] && dp[i] == dp[j] + 1) {
                addEdge(i + n, j, 1);
                addEdge(j, i + n, 0);
            }
        }
    }
    cout << dinic() << "\n";
    for (int i = 0; i < ecnt; i += 2) {
        es[i].capacity += es[i ^ 1].capacity;
        es[i ^ 1].capacity = 0;
    }
    addEdge(1, 1 + n, INF);
    addEdge(1 + n, 1, 0);
    addEdge(n, n + n, INF);
    addEdge(n + n, n, 0);
    if (dp[1] == ans) {
        addEdge(s, 1, INF);
        addEdge(1, s, 0);
    }
    if (dp[n] == 1) {
        addEdge(n + n, t, INF);
        addEdge(t, n + n, 0);
    }
    cout << dinic() << "\n";
	return 0;
}
