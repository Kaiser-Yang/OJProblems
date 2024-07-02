// problem statement: https://vjudge.net/problem/HDU-6184
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;
constexpr int MAXM = 2e5 + 10;

int n, m, ecnt, ans;
int head[MAXN], u[MAXM], v[MAXM], degree[MAXN], cnt[MAXM], edgeId[MAXN];

struct Graph {
    int to, nex;
} es[MAXM];

void addEdge(int u, int v) {
    es[ecnt].to  = v;
    es[ecnt].nex = head[u];
    head[u]      = ecnt++;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> m) {
        ecnt = 0;
        memset(head + 1, 0xff, sizeof(int) * n);
        memset(degree + 1, 0x00, sizeof(int) * n);
        memset(cnt, 0x00, sizeof(int) * m);
        memset(edgeId + 1, 0xff, sizeof(int) * n);
        for (int i = 0; i < m; i++) {
            cin >> u[i] >> v[i];
            degree[u[i]]++;
            degree[v[i]]++;
        }
        for (int i = 0; i < m; i++) {
            if (degree[u[i]] > degree[v[i]] || (degree[u[i]] == degree[v[i]] && u[i] > v[i])) {
                swap(u[i], v[i]);
            }
            addEdge(u[i], v[i]);
        }
        for (int a = 1; a <= n; a++) {
            for (int i = head[a]; i != -1; i = es[i].nex) { edgeId[es[i].to] = i; }
            for (int i = head[a]; i != -1; i = es[i].nex) {
                int b = es[i].to;
                for (int j = head[b]; j != -1; j = es[j].nex) {
                    int c = es[j].to;
                    if (edgeId[c] != -1) {
                        cnt[i]++;
                        cnt[j]++;
                        cnt[edgeId[c]]++;
                    }
                }
            }
            for (int i = head[a]; i != -1; i = es[i].nex) { edgeId[es[i].to] = -1; }
        }
        ans = 0;
        for (int i = 0; i < ecnt; i++) { ans += cnt[i] * (cnt[i] - 1) / 2; }
        cout << ans << endl;
    }
    return 0;
}
