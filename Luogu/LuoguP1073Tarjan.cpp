// problem statement: https://www.luogu.com.cn/problem/P1073

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;
constexpr int MAXM = 5e5 + 10;

int n, m, u, v, type, cnt, colorCnt;
int price[MAXN], dfn[MAXN], low[MAXN], color[MAXN], minPrice[MAXN], maxPrice[MAXN], inDegree[MAXN], dp[MAXN];
bool ins[MAXN];

stack<int> s;

vector<int> g[MAXN], dag[MAXN];

void tarjan(int u)
{
    dfn[u] = low[u] = ++cnt;
    s.push(u);
    ins[u] = true;
    for (int v : g[u]) {
        if (dfn[v] == 0) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (ins[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        colorCnt++;
        while (s.top() != u) {
            color[s.top()] = colorCnt;
            ins[s.top()] = false;
            minPrice[colorCnt] = min(minPrice[colorCnt], price[s.top()]);
            maxPrice[colorCnt] = max(maxPrice[colorCnt], price[s.top()]);
            s.pop();
        }
        color[s.top()] = colorCnt;
        ins[s.top()] = false;
        minPrice[colorCnt] = min(minPrice[colorCnt], price[s.top()]);
        maxPrice[colorCnt] = max(maxPrice[colorCnt], price[s.top()]);
        s.pop();
    }
}

void bfs(){
	queue<int> q;
	q.push(color[1]);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v : dag[u]) {
			minPrice[v] = min(minPrice[v], minPrice[u]);
			dp[v] = max(dp[v], max(dp[u], maxPrice[v] - minPrice[v]));
			if ((--inDegree[v]) == 0) { q.push(v); }
		}
	}
}

int main()
{
    ios::sync_with_stdio(false);
    memset(minPrice, 0x3f, sizeof(minPrice));
    cin >> n >> m;
    for (int i = 1; i <= n; i++) { cin >> price[i]; }
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> type;
        g[u].push_back(v);
        if (type == 2) { g[v].push_back(u); }
    }
    tarjan(1);
    for (int u = 1; u <= n; u++) {
        for (int v : g[u]) {
            if (color[u] == color[v]) { continue; }
            dag[color[u]].push_back(color[v]);
            inDegree[color[v]]++;
        }
    }
    bfs();
    cout << dp[color[n]] << endl;
 	return 0;
}
