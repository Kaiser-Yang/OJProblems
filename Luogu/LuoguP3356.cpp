// problem statement: https://www.luogu.com.cn/problem/P3356

#include <bits/stdc++.h>

constexpr int MAXN = 35 + 5;
constexpr int MAXP = 35 + 5;
constexpr int MAXQ = 35 + 5;
constexpr int INF  = 0x3f3f3f3f;

using namespace std;

int n, p, q;
int dx[] = {1, 0};
int dy[] = {0, 1};
int mp[MAXP][MAXQ];
int s, t, ecnt;
int head[2 * MAXP * MAXQ], cur[2 * MAXP * MAXQ], dis[2 * MAXP * MAXQ];
bool vis[2 * MAXP * MAXQ];
vector<vector<int>> path;

struct Graph {
    int to, nex, capacity, cost;
} es[8 * MAXP * MAXQ];

void addEdge(int u, int v, int capacity, int cost) {
    es[ecnt] = {v, head[u], capacity, cost};
    head[u]  = ecnt++;
}

bool spfa() {
    memset(dis, 0x3f, sizeof(dis));
    auto &inq = vis;
    queue<int> q;
    q.push(s);
    inq[s] = true;
    dis[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int i = head[u]; i != -1; i = es[i].nex) {
            int v = es[i].to;
            if (dis[v] > dis[u] - es[i].cost && es[i].capacity > 0) {
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
    vis[u]      = true;
    int outFlow = 0;
    for (int &i = cur[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (vis[v] || es[i].capacity == 0 || dis[v] != dis[u] - es[i].cost) { continue; }
        int outFlowV = dfs(v, min(inFlow - outFlow, es[i].capacity), ans);
        if (outFlowV > 0) {
            outFlow += outFlowV;
            es[i].capacity -= outFlowV;
            es[i ^ 1].capacity += outFlowV;
            ans.second += outFlowV * es[i].cost;
            if (outFlow == inFlow) { break; }
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

int getID(int i, int j, int level) { return (i - 1) * q + j + level * p * q; }

void findPath(int u, int len) {
    if (u >= 1 && u <= p * q) { path[len].push_back(u); }
    for (int i = head[u]; i != -1; i = es[i].nex) {
        if (i % 2 == 1 || es[i ^ 1].capacity == 0) { continue; }
        int v = es[i].to;
        es[i ^ 1].capacity--;
        findPath(v, len);
        break;
    }
}

int main() {
    ios::sync_with_stdio(false);
    memset(head, 0xff, sizeof(head));
    cin >> n >> q >> p;
    for (int i = 1; i <= p; i++) {
        for (int j = 1; j <= q; j++) { cin >> mp[i][j]; }
    }
    s = 0, t = getID(p, q, 1) + 1;
    addEdge(s, getID(1, 1, 0), n, 0);
    addEdge(getID(1, 1, 0), s, 0, 0);
    addEdge(getID(p, q, 1), t, n, 0);
    addEdge(t, getID(p, q, 1), 0, 0);
    for (int i = 1; i <= p; i++) {
        for (int j = 1; j <= q; j++) {
            if (mp[i][j] == 1) { continue; }
            if (mp[i][j] == 2) {
                addEdge(getID(i, j, 0), getID(i, j, 1), 1, 1);
                addEdge(getID(i, j, 1), getID(i, j, 0), 0, -1);
            }
            addEdge(getID(i, j, 0), getID(i, j, 1), INF, 0);
            addEdge(getID(i, j, 1), getID(i, j, 0), 0, 0);
            int u = getID(i, j, 1);
            for (int k = 0; k < 2; k++) {
                int nx = i + dx[k], ny = j + dy[k];
                if (nx < 1 || nx > p || ny < 1 || ny > q || mp[nx][ny] == 1) { continue; }
                int v = getID(nx, ny, 0);
                addEdge(u, v, INF, 0);
                addEdge(v, u, 0, 0);
            }
        }
    }
    auto ans = MCMFDinic();
    if (ans.first == 0) { return 0; }
    path.resize(ans.first, vector<int>());
    for (int i = 0; i < ans.first; i++) {
        findPath(s, i);
        for (int j = 1; j < path[i].size(); j++) {
            cout << i + 1 << " ";
            if (path[i][j] == path[i][j - 1] + 1) {
                cout << "1\n";
            } else {
                cout << "0\n";
            }
        }
    }
    return 0;
}
