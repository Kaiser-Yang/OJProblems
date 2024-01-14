#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN = 110;
const int INF = 0x3f3f3f3f;

int T, n, m, u, v, w, ans;
bool uniqueMST;
int h[MAXN];

struct Edge
{
    int u, v, w;
    Edge() {}
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
    bool operator<(const Edge &other) { return w < other.w; }
};
vector<Edge> edge;

int find(int x) { return x == h[x] ? x : h[x] = find(h[x]); }

bool same(int a, int b) { return find(a) == find(b); }

void join(int a, int b)
{
    int fa = find(a), fb = find(b);
    h[fa] = fb;
}

int main()
{
	ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        edge.clear();
        for (int i = 1; i <= n; i++) { h[i] = i; }
        for (int i = 0; i < m; i++) {
            cin >> u >> v >> w;
            edge.push_back(Edge(u, v, w));
        }
        ans = 0;
        uniqueMST = true;
        sort(edge.begin(), edge.end());
        // cnt is the number of added edges;
        // cnt1 is the number of current weight edges which can be added;
        // cnt2 is the number of current weight edges which have been added.
        int cnt1 = 0, cnt2 = 0, cnt = 0, tail = -1;
        for (int i = 0; i <= edge.size(); i++) {
            if (i > tail) {
                if (cnt1 != cnt2) {
                    uniqueMST = false;
                    break;
                }
                cnt1 = 0;
                cnt2 = 0;
                for (int j = i; j <= edge.size(); j++) {
                    if (j == edge.size() || edge[j].w != edge[i].w) {
                        tail = j - 1;
                        break;
                    }
                    if (!same(edge[j].u, edge[j].v)) { cnt1++; }
                }
            }
            if (i > edge.size() || cnt == n - 1 || same(edge[i].u, edge[i].v)) { continue; }
            join(edge[i].u, edge[i].v);
            ans += edge[i].w;
            cnt++;
            cnt2++;
        }
        if (uniqueMST) { cout << ans << endl; }
        else { cout << "Not Unique!\n"; }
    }
	return 0;
}
