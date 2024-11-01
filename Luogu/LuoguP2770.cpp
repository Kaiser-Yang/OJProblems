// problem statement: https://www.luogu.com.cn/problem/P2770

#include <bits/stdc++.h>

constexpr int MAXN = 100 + 10;
constexpr int MAXM = MAXN * MAXN / 2;
constexpr int INF = 0x3f3f3f3f;

using namespace std;

int n, m, idCnt;
string uString, vString;
unordered_map<string, int> id;
unordered_map<int, string> name;
int s, t, ecnt;
int head[2 * MAXN], cur[2 * MAXN], dis[2 * MAXN];
bool vis[2 * MAXN];
bool ok;
vector<int> path;

struct Graph {
    int to, nex, capacity, cost;
} es[4 * MAXM + 2 * MAXN];

void addEdge(int u, int v, int capacity, int cost) {
    es[ecnt] = {v, head[u], capacity, cost};
    head[u] = ecnt++;
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
    vis[u] = true;
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

void findPath(int u) {
    path.push_back(u - n);
    for (int i = head[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (i % 2 == 0 && es[i ^ 1].capacity > 0) {
            es[i ^ 1].capacity = 0;
            findPath(v + n);
            break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    memset(head, 0xff, sizeof(head));
    cin >> n >> m;
    s = 1, t = 2 * n;
    for (int i = 1; i <= n; i++) {
        cin >> name[i];
        id[name[i]] = i;
    }
    for (int i = 0; i < m; i++) {
        cin >> uString >> vString;
        int u = id[uString], v = id[vString];
        if (u > v) { swap(u, v); }
        if (u == 1 && v == n) { ok = true; }
        addEdge(u + n, v, 1, 0);
        addEdge(v, u + n, 0, 0);
    }
    for (int i = 1; i <= n; i++) {
        if (i != 1 && i != n) {
            addEdge(i, i + n, 1, 1);
            addEdge(i + n, i, 0, -1);
        } else {
            addEdge(i, i + n, 2, 1);
            addEdge(i + n, i, 0, -1);
        }
    }
    auto ans = MCMFDinic();
    if (ans.first == 2) {
        cout << ans.second - 2 << "\n";
        findPath(1 + n);
        findPath(1 + n);
        for (int i = 0; i < path.size(); i++) {
            if (i != 0 && path[i] == 1) { break; }
            cout << name[path[i]] << "\n";
        }
        for (int i = path.size() - 2; i >= 0; i--) {
            cout << name[path[i]] << "\n";
            if (path[i] == 1) { break; }
        }
    } else if (ans.first == 1 && ok) {
        cout << "2\n";
        cout << name[1] << "\n" << name[n] << "\n" << name[1] << "\n";
    } else {
        cout << "No Solution!\n";
    }
    return 0;
}
