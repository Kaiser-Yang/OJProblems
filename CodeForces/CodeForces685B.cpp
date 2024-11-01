// problem statement: https://codeforces.com/problemset/problem/685/B
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 3e5 + 10;

int n, q, node;
int centroid[MAXN], parent[MAXN], siz[MAXN], maxSonSize[MAXN];

vector<int> g[MAXN];

void dfs(int u) {
    siz[u] = 1;
    maxSonSize[u] = 0;
    for (int v : g[u]) {
        dfs(v);
        siz[u] += siz[v];
        maxSonSize[u] = max(maxSonSize[u], siz[v]);
    }
    centroid[u] = u;
    for (int v : g[u]) {
        int node = centroid[v];
        int newCentroid = centroid[v];
        while (parent[node] != u) {
            node = parent[node];
            if (max(maxSonSize[node], siz[u] - siz[node]) <
                max(maxSonSize[newCentroid], siz[u] - siz[newCentroid])) {
                newCentroid = node;
            } else {
                break;
            }
        }
        if (max(maxSonSize[newCentroid], siz[u] - siz[newCentroid]) <
            max(maxSonSize[centroid[u]], siz[u] - siz[centroid[u]])) {
            centroid[u] = newCentroid;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> q;
    for (int i = 2; i <= n; i++) {
        cin >> node;
        g[node].push_back(i);
        parent[i] = node;
    }
    dfs(1);
    for (int i = 0; i < q; i++) {
        cin >> node;
        cout << centroid[node] << endl;
    }
    return 0;
}
