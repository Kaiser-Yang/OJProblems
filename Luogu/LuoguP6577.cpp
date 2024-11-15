// problem statement: https://www.luogu.com.cn/problem/P6577

#include <bits/stdc++.h>

using namespace std;

const long long INF = 0x3f3f3f3f3f3f3f3fLL;
const int MAX_NODE_NUM = 510;

int n, m;
int parent[MAX_NODE_NUM], match[MAX_NODE_NUM];
long long slack[MAX_NODE_NUM], leftWeight[MAX_NODE_NUM], rightWeight[MAX_NODE_NUM],
    edgeWeight[MAX_NODE_NUM][MAX_NODE_NUM];
bool augmented[MAX_NODE_NUM];

void bfs(int startNode) {
    int nextNode = -1, leftNode = -1;
    long long delta = INF;
    memset(augmented, 0, sizeof(augmented));
    memset(parent, 0, sizeof(parent));
    memset(slack, 0x3f, sizeof(slack));
    int u = 0;
    match[u] = startNode;
    do {
        leftNode = match[u];
        augmented[u] = true;
        delta = INF;
        for (int rightNode = 1; rightNode <= m; rightNode++) {
            if (augmented[rightNode]) { continue; }
            if (slack[rightNode] >
                leftWeight[leftNode] + rightWeight[rightNode] - edgeWeight[leftNode][rightNode]) {
                slack[rightNode] =
                    leftWeight[leftNode] + rightWeight[rightNode] - edgeWeight[leftNode][rightNode];
                parent[rightNode] = u;
            }
            if (slack[rightNode] < delta) {
                delta = slack[rightNode];
                nextNode = rightNode;
            }
        }
        for (int rightNode = 0; rightNode <= m; rightNode++) {
            if (augmented[rightNode]) {
                leftWeight[match[rightNode]] -= delta;
                rightWeight[rightNode] += delta;
            } else {
                slack[rightNode] -= delta;
            }
        }
        u = nextNode;
    } while (match[u] != 0);
    while (u != 0) {
        match[u] = match[parent[u]];
        u = parent[u];
    }
}

void km() {
    memset(match, 0, sizeof(match));
    memset(leftWeight, 0, sizeof(leftWeight));
    memset(rightWeight, 0, sizeof(rightWeight));
    for (int leftNode = 1; leftNode <= n; leftNode++) { bfs(leftNode); }
}

int main() {
    ios::sync_with_stdio(false);
    for (int i = 0; i < MAX_NODE_NUM; i++) {
        for (int j = 0; j < MAX_NODE_NUM; j++) { edgeWeight[i][j] = -INF; }
    }
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edgeWeight[u][v] = max<long long>(edgeWeight[u][v], w);
    }
    m = n;
    km();
    long long ans = 0;
    for (int i = 1; i <= n; i++) { ans += edgeWeight[match[i]][i]; }
    cout << ans << endl;
    for (int i = 1; i <= n; i++) { cout << match[i] << " "; }
    cout << endl;
    return 0;
}