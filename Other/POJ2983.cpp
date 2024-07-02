// problem statement: http://poj.org/problem?id=2983
// Tag: having been in my blog

#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MAXN = 1010;
const int MAXM = 1e5 + 10;

int n, m, u, v, w;
int dis[MAXN];
string type;

struct Edge {
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

vector<Edge> edge;

void addEdge(int u, int v, int w) { edge.push_back(Edge(u, v, w)); }

bool bellmanFord() {
    memset(dis, 0x3f, sizeof(int) * (n + 1));
    dis[0]    = 0;
    bool flag = false;
    for (int i = 0; i <= n; i++) {
        flag = false;
        for (int j = 0; j < edge.size(); j++) {
            int u = edge[j].u, v = edge[j].v, w = edge[j].w;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                flag   = true;
            }
        }
        if (!flag) { break; }
    }
    return flag;
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n >> m) {
        edge.clear();
        for (int i = 0; i < m; i++) {
            cin >> type;
            if (type == "P") {
                cin >> u >> v >> w;
                addEdge(u, v, -w);
                addEdge(v, u, w);
            } else {
                cin >> u >> v;
                addEdge(u, v, -1);
            }
        }
        for (int i = 1; i <= n; i++) { addEdge(0, i, 0); }
        cout << (bellmanFord() ? "Unreliable" : "Reliable") << endl;
    }
    return 0;
}
