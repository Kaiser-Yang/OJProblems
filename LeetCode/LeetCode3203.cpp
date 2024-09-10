// problem statement: https://leetcode.cn/problems/find-minimum-diameter-after-merging-two-trees

#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
    vector<int> depth, path;
    int tmp_node;
    int farthest_node(int u, int fa, const vector<vector<int>> &g) {
        if (fa == -1) {
            tmp_node = u;
        } else if (depth[u] > depth[tmp_node]) {
            tmp_node = u;
        }
        for (auto &&v : g[u]) {
            if (v == fa) { continue; }
            depth[v] = depth[u] + 1;
            farthest_node(v, u, g);
        }
        return tmp_node;
    }
    int get_middle(int a, int b, const vector<vector<int>> &g) {
        queue<int> q;
        q.push(a);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == b) { break; }
            for (auto &&v : g[u]) {
                if (path[v] != -1 || v == a) { continue; }
                q.push(v);
                path[v] = u;
            }
        }
        int dis = 0, res = b;
        while (path[res] != -1) {
            res = path[res];
            dis++;
        }
        dis /= 2;
        res = b;
        while (dis--) { res = path[res]; }
        return res;
    }

public:
    int minimumDiameterAfterMerge(vector<vector<int>> &edges1, vector<vector<int>> &edges2) {
        int n1 = edges1.size() + 1, n2 = edges2.size() + 1;
        vector<vector<int>> t1(n1), t2(n2);
        auto create_tree = [](vector<vector<int>> &edges, vector<vector<int>> &g) {
            for (auto &&edge : edges) {
                g[edge[0]].push_back(edge[1]);
                g[edge[1]].push_back(edge[0]);
            }
        };
        create_tree(edges1, t1);
        create_tree(edges2, t2);
        vector<int>(n1).swap(depth);
        int a1 = farthest_node(0, -1, t1);
        vector<int>(n1).swap(depth);
        int b1 = farthest_node(a1, -1, t1);
        vector<int>(n2).swap(depth);
        int a2 = farthest_node(0, -1, t2);
        vector<int>(n2).swap(depth);
        int b2 = farthest_node(a2, -1, t2);
        vector<int>(n1, -1).swap(path);
        int middle1 = get_middle(a1, b1, t1);
        vector<int>(n2, -1).swap(path);
        int middle2 = get_middle(a2, b2, t2);
        vector<vector<int>> t(n1 + n2);
        create_tree(edges1, t);
        for (auto &&edge : edges2) {
            t[edge[0] + n1].push_back(edge[1] + n1);
            t[edge[1] + n1].push_back(edge[0] + n1);
        }
        t[middle1].push_back(middle2 + n1);
        t[middle2 + n1].push_back(middle1);
        vector<int>(n1 + n2).swap(depth);
        int a = farthest_node(0, -1, t);
        vector<int>(n1 + n2).swap(depth);
        int b = farthest_node(a, -1, t);
        return depth[b];
        return 0;
    }
};
