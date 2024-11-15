// problem statement: http://poj.org/problem?id=1236
// Tag: having been in my blog

#include <cstring>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

const int MAXN = 110;

int n, colorCnt, cnt, ans1, ans2;
int dfn[MAXN], low[MAXN], color[MAXN], inDegree[MAXN], outDegree[MAXN];
bool ins[MAXN], vis[MAXN];
stack<int> s;

vector<int> g[MAXN];

void tarjan(int u) {
    dfn[u] = low[u] = ++cnt;
    s.push(u);
    ins[u] = true;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
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
            s.pop();
        }
        color[s.top()] = colorCnt;
        ins[s.top()] = false;
        s.pop();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int v = 0;
        while (cin >> v && v != 0) { g[i].push_back(v); }
    }
    for (int i = 1; i <= n; i++) {
        if (dfn[i] != 0) { continue; }
        tarjan(i);
    }
    for (int u = 1; u <= n; u++) {
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (color[u] == color[v]) { continue; }
            outDegree[color[u]]++;
            inDegree[color[v]]++;
        }
    }
    for (int i = 1; i <= colorCnt; i++) {
        if (inDegree[i] == 0) { ans1++; }
        if (outDegree[i] == 0) { ans2++; }
    }
    if (colorCnt == 1) {
        cout << 1 << endl << 0 << endl;
        return 0;
    }
    ans2 = max(ans1, ans2);
    cout << ans1 << endl << ans2 << endl;
    return 0;
}
