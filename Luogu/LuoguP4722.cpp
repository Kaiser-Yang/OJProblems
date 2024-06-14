// problem statement: https://www.luogu.com.cn/problem/P4722

#include <bits/stdc++.h>

constexpr int MAXN = 1.2e3 + 10;
constexpr int MAXM = 1.2e5 + 10;

using namespace std;

int n, m, s, t, u, v, ecnt, maxHeight;
long long w;
int head[MAXN], height[MAXN], gap[MAXN];
long long ex[MAXN];
bool inBucket[MAXN];
stack<int> bucket[MAXN];

struct Graph
{
    int to, nex;
    long long capacity;
}es[MAXM << 1];

void addEdge(int u, int v, long long w)
{
    es[ecnt].to = v;
    es[ecnt].capacity = w;
    es[ecnt].nex = head[u];
    head[u] = ecnt++;
}

bool bfs()
{
    memset(height, 0xff, sizeof(height));
    queue<int> q;
    q.push(t);
    height[t] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = es[i].nex) {
            int v = es[i].to;
            if (es[i].capacity == 0 && height[v] == -1) { 
                height[v] = height[u] + 1;
                q.push(v);
            }
        }
    }
    return height[s] != -1;
}


int select()
{
    while (bucket[maxHeight].empty() && maxHeight > -1) { maxHeight--; }
    return maxHeight == -1 ? 0 : bucket[maxHeight].top();
}

bool push(int u)
{
    bool init = (u == s);
    for (int i = head[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        //  checking height[v] == -1 is necessary, because in function relabel the height could be -1
        if (es[i].capacity == 0 || (!init && height[u] != height[v] + 1) || height[v] == -1) { continue; }
        long long flow = init ? es[i].capacity : min(es[i].capacity, ex[u]);
        ex[u] -= flow;
        ex[v] += flow;
        es[i].capacity -= flow;
        es[i ^ 1].capacity += flow;
        if (v != s && v != t && ex[v] != 0 && !inBucket[v]) {
            bucket[height[v]].push(v);
            inBucket[v] = true;
            maxHeight = max(maxHeight, height[v]);
        }
        if (ex[u] == 0) { return false; }
    }
    return true;
}

void relabel(int u)
{
    height[u] = -1;
    for (int i = head[u]; i != -1; i = es[i].nex) {
        int v = es[i].to;
        if (es[i].capacity == 0) { continue; }
        if (height[u] == -1 || height[u] > height[v]) { height[u] = height[v]; }
    }
    if (++height[u] < n) {
        if (!inBucket[u]) {
            bucket[height[u]].push(u);
            maxHeight = max(maxHeight, height[u]);
        }
        gap[height[u]]++;
    }
}

int hlpp()
{
    if (!bfs()) { return 0; }
    for (int i = 1; i <= n; i++) { if (height[i] != -1) { gap[height[i]]++; } }
    height[s] = n;
    push(s);
    int u;
    while ((u = select())) {
        bucket[maxHeight].pop();
        inBucket[u] = false;
        if (push(u)) {
            if (--gap[height[u]] == 0) {
                for (int i = 1; i <= n; i++) {
                    if (i == s || height[i] < height[u] || height[i] > n) { continue; }
                    height[i] = n + 1;
                }
            }
            relabel(u);
        }
    }
    return ex[t];
}

int main()
{
	ios::sync_with_stdio(false);
    cin >> n >> m >> s >> t;
    memset(head, 0xff, sizeof(head));
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        addEdge(u, v, w);
        addEdge(v, u, 0);
    }
    cout << hlpp() << "\n";
	return 0;
}
