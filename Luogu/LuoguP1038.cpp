// problem statement:

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 110;

int n, p, x, y, z;
int c[MAXN], u[MAXN], w[MAXN][MAXN], inDegree[MAXN], outDegree[MAXN];
bool connected[MAXN][MAXN], has;

void toposort() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (inDegree[i] == 0) { q.push(i); }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (c[u] <= 0) { continue; }
        for (int v = 1; v <= n; v++) {
            c[v] += c[u] * w[u][v];
            if (connected[u][v] && --inDegree[v] == 0) {
                c[v] -= ::u[v];
                q.push(v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> p;
    for (int i = 1; i <= n; i++) { cin >> c[i] >> u[i]; }
    for (int i = 0; i < p; i++) {
        cin >> x >> y >> z;
        w[x][y] = z;
        connected[x][y] = true;
        inDegree[y]++;
        outDegree[x]++;
    }
    toposort();
    for (int i = 1; i <= n; i++) {
        if (outDegree[i] == 0 && c[i] > 0) {
            has = true;
            cout << i << " " << c[i] << endl;
        }
    }
    if (!has) { cout << "NULL\n"; }
    return 0;
}
