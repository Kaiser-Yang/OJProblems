// problem statement: https://csacademy.com/ieeextreme-practice/task/kings-order

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e3 + 10;

int n, m;
int id[MAXN], indegree[MAXN];
int ans[MAXN];
vector<int> g[MAXN];
int cnt = 0;

struct Comparator {
    bool operator()(int a, int b) {
        if (id[a] == id[b]) { return a > b; }
        return id[a] > id[b];
    }
};

void toposort() {
    priority_queue<int, vector<int>, Comparator> q;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) { q.push(i); }
    }
    while (!q.empty()) {
        int u = q.top();
        q.pop();
        ans[cnt++] = u;
        for (int v : g[u]) {
            indegree[v]--;
            if (indegree[v] == 0) { q.push(v); }
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) { cin >> id[i]; }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        indegree[v]++;
    }
    toposort();
    if (cnt != n) {
        cout << "-1\n";
    } else {
        for (int i = 0; i < n; i++) { cout << ans[i] << (i == n - 1 ? "\n" : " "); }
    }
    return 0;
}
