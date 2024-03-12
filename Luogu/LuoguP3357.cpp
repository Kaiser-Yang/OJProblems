// problem statement: https://www.luogu.com.cn/problem/P3357

#include <bits/stdc++.h>

constexpr int MAXN = 510;
constexpr long long INF  = 0x3f3f3f3f3f3f3f3f;

using namespace std;

int n, k;
int idCnt;
long long a, b, c, d;
map<long long, int> id, node;
int s, t, ecnt;
int head[2 * MAXN], cur[2 * MAXN];
long long dis[2 * MAXN];
bool vis[2 * MAXN];

struct Line { 
    int left, right;
    long long len;
} line[MAXN];

struct Graph
{
    int to, nex, capacity;
    long long cost;
} es[MAXN * MAXN * 2];

void addFlow(int u, int v, int capacity, long long cost)
{
    es[ecnt] = {v, head[u], capacity, cost};
    head[u] = ecnt++;
    es[ecnt] = {u, head[v], 0, -cost};
    head[v] = ecnt++;
}

long long getLen(long long a, long long b, long long c, long long d)
{
    return (long long)sqrt((c - a) * (c - a) + (d - b) * (d - b));
}

bool spfa()
{
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

int dfs(int u, int inFlow, pair<int, long long> &ans)
{
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

pair<int, long long> MCMFDinic()
{
    pair<int, long long> ans{0, 0};
    int flow = 0;
    while (spfa()) {
        memcpy(cur, head, sizeof(head));
        while ((flow = dfs(s, 0x3f3f3f3f, ans)) != 0) { ans.first += flow; }
    }
    return ans;
}

int main()
{
	ios::sync_with_stdio(false);
    memset(head, 0xff, sizeof(head));
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a >> b >> c >> d;
        line[i].len = getLen(a, b, c, d);
        a *= 2;
        c *= 2;
        if (a == c) { c++; }
        else { a++; }
        node[a] = 1;
        node[c] = 1;
        line[i].left = a;
        line[i].right = c;
    }
    for (const auto &item : node) { id[item.first] = ++idCnt; }
    for (int i = 0; i < n; i++) {
        line[i].left = id[line[i].left];
        line[i].right = id[line[i].right];
    }
    s = 0, t = idCnt + 1;
    for (int i = 0; i <= idCnt; i++) { addFlow(i, i + 1, k, 0); }
    for (int i = 0; i < n; i++) { addFlow(line[i].left, line[i].right, 1, line[i].len); }
    cout << MCMFDinic().second << "\n";
	return 0;
}
