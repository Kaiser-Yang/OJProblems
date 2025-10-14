// problem statement: http://poj.org/problem?id=2728

#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>

const int MAXN = 1010;
int city[MAXN][3];
int cost[MAXN][MAXN];
double dist[MAXN][MAXN];
double prim_cost[MAXN][MAXN];
bool vis[MAXN];
double dis[MAXN];

double prim(int n) {
    std::fill(vis, vis + n, false);
    std::fill(dis, dis + n, 1e9);
    dis[0] = 0;
    double res = 0;
    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!vis[j] && (u == -1 || dis[j] < dis[u])) u = j;
        }
        assert(u != -1);
        vis[u] = true;
        res += dis[u];
        for (int v = 0; v < n; v++) {
            if (!vis[v] && prim_cost[u][v] < dis[v]) dis[v] = prim_cost[u][v];
        }
    }
    return res;
}

bool check(double x, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            prim_cost[i][j] = prim_cost[j][i] = cost[i][j] - x * dist[i][j];
        }
        prim_cost[i][i] = 1e9;
    }
    return prim(n) <= 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    std::cout << std::fixed << std::setprecision(3);
    while (std::cin >> n) {
        if (n == 0) break;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 3; j++) { std::cin >> city[i][j]; }
        }

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int dx = city[i][0] - city[j][0];
                int dy = city[i][1] - city[j][1];
                dist[i][j] = dist[j][i] = std::sqrt(dx * dx + dy * dy);
                cost[i][j] = cost[j][i] = std::abs((double)city[i][2] - city[j][2]);
            }
            dist[i][i] = 0;
            cost[i][i] = 0;
        }

        double left = 0, right = 1e2, ans = 0.;
        while (right - left > 1e-5) {
            double mid = (left + right) / 2;
            if (check(mid, n)) {
                ans = mid;
                right = mid;
            } else {
                left = mid;
            }
        }
        std::cout << ans << '\n';
    }
    return 0;
}
