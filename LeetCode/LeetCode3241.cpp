// problem statement: https://leetcode.cn/problems/time-taken-to-mark-all-nodes/

#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
    int get_w(int u) { return u % 2 == 0 ? 2 : 1; }

    void dfs(int u, int par) {
        for (auto &&v : g[u]) {
            if (v == par) { continue; }
            dfs(v, u);
            dis[u] = max(dis[u], dis[v]);
            if (farthest_child[u][0] == -1 || dis[v] > dis[farthest_child[u][0]]) {
                farthest_child[u][1] = farthest_child[u][0];
                farthest_child[u][0] = v;
            } else if (farthest_child[u][1] == -1 || dis[v] > dis[farthest_child[u][1]]) {
                farthest_child[u][1] = v;
            }
        }
        if (u != 0) { dis[u] += get_w(u); }
    }

    void dp(int u, int par) {
        for (auto &&v : g[u]) {
            if (v == par) { continue; }
            int child_u = farthest_child[u][0] == v ? farthest_child[u][1] : farthest_child[u][0];
            ans[v] = get_w(u);
            if (child_u != -1) { ans[v] += dis[child_u]; }
            int child_v = farthest_child[v][0];
            if (child_v != -1) { ans[v] = max(ans[v], dis[child_v]); }
            int tmp_dis_u = dis[u];
            int tmp_dis_v = dis[v];
            int tmp_child_0 = farthest_child[v][0];
            int tmp_child_1 = farthest_child[v][1];
            dis[u] = get_w(u);
            if (child_u != -1) { dis[u] += dis[child_u]; }
            dis[v] = max(dis[v] - get_w(v), dis[u]);
            if (farthest_child[v][0] == -1 || dis[u] > dis[farthest_child[v][0]]) {
                farthest_child[v][1] = farthest_child[v][0];
                farthest_child[v][0] = u;
            } else if (farthest_child[v][1] == -1 || dis[u] > dis[farthest_child[v][1]]) {
                farthest_child[v][1] = u;
            }
            dp(v, u);
            dis[u] = tmp_dis_u;
            dis[v] = tmp_dis_v;
            farthest_child[v][0] = tmp_child_0;
            farthest_child[v][1] = tmp_child_1;
        }
    }

    vector<vector<int>> g, farthest_child;
    vector<int> dis, ans;

public:
    vector<int> timeTaken(vector<vector<int>> &edges) {
        int n = edges.size() + 1;
        g.clear();
        farthest_child.clear();
        g.resize(n);
        farthest_child.resize(n, vector<int>(2, -1));
        dis.clear();
        dis.resize(n);
        for (auto edge : edges) {
            int u = edge[0], v = edge[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(0, -1);
        ans.clear();
        ans.resize(n);
        ans[0] = dis[0];
        dp(0, -1);
        return ans;
    }
};
