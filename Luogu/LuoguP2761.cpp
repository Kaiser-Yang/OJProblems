// problem statement: https://www.luogu.com.cn/problem/P2761

#include <bits/stdc++.h>

constexpr int MAXM = 100 + 10;
constexpr int INF  = 0x3f3f3f3f;

using namespace std;

int n, m;

struct Patch {
    int cost;
    string a, b;
} patch[MAXM];

bool canUse(int now, int id) {
    for (int i = 0; i < patch[id].a.length(); i++) {
        if (patch[id].a[i] == '+' && !(now & (1 << i))) {
            return false;
        } else if (patch[id].a[i] == '-' && (now & (1 << i))) {
            return false;
        }
    }
    return true;
}

int getNewState(int now, int id) {
    for (int i = 0; i < patch[id].b.length(); i++) {
        if (patch[id].b[i] == '+') {
            now |= (1 << i);
        } else if (patch[id].b[i] == '-' && (now & (1 << i))) {
            now -= (1 << i);
        }
    }
    return now;
}

int dijkstra() {
    vector<bool> used(1 << n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    vector<int> dis(1 << n, INF);
    q.push({0, (1 << n) - 1});
    dis[(1 << n) - 1] = 0;
    while (!q.empty()) {
        auto now = q.top();
        q.pop();
        if (used[now.second]) { continue; }
        used[now.second] = true;
        for (int i = 0; i < m; i++) {
            if (!canUse(now.second, i)) { continue; }
            int newState = getNewState(now.second, i);
            if (dis[newState] > dis[now.second] + patch[i].cost) {
                dis[newState] = dis[now.second] + patch[i].cost;
                q.push({dis[newState], newState});
            }
        }
    }
    return dis[0];
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < m; i++) { cin >> patch[i].cost >> patch[i].a >> patch[i].b; }
    int ans = dijkstra();
    if (ans >= INF) {
        cout << "0\n";
    } else {
        cout << ans << "\n";
    }
    return 0;
}
