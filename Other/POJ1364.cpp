// problem statement: http://poj.org/problem?id=1364

#include <string>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

const int MAXN = 110;

int n, m, u, v, w;
int dis[MAXN];
string op;

struct Edge
{
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

vector<Edge> edge;

void addEdge(int u, int v, int w) 
{
    edge.push_back(Edge(u, v, w));
}

bool bellmanFord()
{
    memset(dis, 0x3f, sizeof(int) * (n + 2));
    dis[n + 1] = 0;
    bool flag = false;
    for (int i = 0; i <= n + 1; i++) {
        flag = false;
        for (int j = 0; j < edge.size(); j++) {
            int u = edge[j].u, v = edge[j].v, w = edge[j].w;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                flag = true;
            }
        }
        if (!flag) { break; }
    }
    return flag;
}

int main()
{
	ios::sync_with_stdio(false);
    while (cin >> n && n != 0) {
        cin >> m;
        edge.clear();
        for (int i = 0; i < m; i++) {
            cin >> u >> v >> op >> w;
            v += u;
            u--;
            if (op == "lt") { addEdge(u, v, w - 1); } 
            else { addEdge(v, u, -(w + 1)); }
        }
        for (int i = 0; i <= n; i++) { addEdge(n + 1, i, 0); }
        cout << (bellmanFord() ? "successful conspiracy" : "lamentable kingdom") << endl;
    }
	return 0;
}
