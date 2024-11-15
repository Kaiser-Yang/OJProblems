// problem statement:

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXS = 110;
constexpr int MAX_NODE = 400 + 1;

int T, S, t, A, B, price;

using Node = pair<int, int>;

Node p[4];
vector<Node> node;
map<Node, int> id;
vector<int> g[MAXS * 4];
vector<double> w[MAXS * 4];
double dis[MAXS * 4];

double getDis(const Node &a, const Node &b) {
    return sqrt((a.first - b.first) * (a.first - b.first) +
                (a.second - b.second) * (a.second - b.second));
}

int getDisSquare(const Node &a, const Node &b) {
    return (a.first - b.first) * (a.first - b.first) +
           (a.second - b.second) * (a.second - b.second);
}

double getDis(int u, int v) {
    if (u == MAX_NODE + 1 || u == MAX_NODE || v == MAX_NODE || v == MAX_NODE + 1) { return 0; }
    return getDis(node[u], node[v]);
}

void addEdge(int u, int v, int price) {
    g[u].push_back(v);
    w[u].push_back(getDis(u, v) * price);
}

void getLastPoint() {
    if (getDisSquare(p[0], p[2]) + getDisSquare(p[1], p[2]) == getDisSquare(p[0], p[1])) {
        swap(p[2], p[1]);
    }
    if (getDisSquare(p[0], p[1]) + getDisSquare(p[0], p[2]) == getDisSquare(p[1], p[2])) {
        swap(p[0], p[1]);
    }
    p[3] = p[2];
    p[3].first += p[0].first - p[1].first;
    p[3].second += p[0].second - p[1].second;
}

// TODO update wrong codes
void SPFA() {
    fill(dis, dis + MAX_NODE + 2, 0x3f3f3f3f);
    struct Comparor {
        bool operator()(int u, int v) { return dis[u] > dis[v]; }
    };
    vector<int> inq(MAX_NODE + 2, false);
    priority_queue<int, vector<int>, Comparor> q;
    q.push(MAX_NODE);
    dis[MAX_NODE] = 0;
    inq[MAX_NODE] = true;
    while (!q.empty()) {
        int u = q.top();
        q.pop();
        inq[u] = false;
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (dis[v] > dis[u] + w[u][i]) {
                dis[v] = dis[u] + w[u][i];
                if (!inq[v]) {
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> S >> t >> A >> B;
        for (int i = 1; i <= S; i++) {
            for (int j = 0; j < 3; j++) { cin >> p[j].first >> p[j].second; }
            getLastPoint();
            for (int j = 0; j < 4; j++) {
                node.push_back(p[j]);
                id[p[j]] = node.size() - 1;
            }
            cin >> price;
            for (int j = 0; j < 4; j++) {
                for (int k = j + 1; k < 4; k++) {
                    addEdge(id[p[j]], id[p[k]], price);
                    addEdge(id[p[k]], id[p[j]], price);
                }
            }
        }
        for (int i = 1; i <= S; i++) {
            for (int j = i + 1; j <= S; j++) {
                for (int k = 0; k < 4; k++) {
                    for (int l = 0; l < 4; l++) {
                        addEdge(id[node[(i - 1) * 4 + k]], id[node[(j - 1) * 4 + l]], t);
                        addEdge(id[node[(j - 1) * 4 + l]], id[node[(i - 1) * 4 + k]], t);
                    }
                }
            }
        }
        for (int i = 0; i < 4; i++) {
            addEdge(MAX_NODE, id[node[(A - 1) * 4 + i]], 0);
            addEdge(id[node[(B - 1) * 4 + i]], MAX_NODE + 1, 0);
        }
        SPFA();
        cout << fixed << setprecision(1) << dis[MAX_NODE + 1] << endl;
    }
    return 0;
}
