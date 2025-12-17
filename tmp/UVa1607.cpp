/*
    You are given a net which is made from NAND-gate. The net's inputs are all zero or all 1.
Your task is to find some inputs as many as possible and fix them. After doing this, you need
to make sure that the rest of inputs has the same effect with that before doing this.
*/
#include <bits/stdc++.h>

using namespace std;

void addEdge(int u, int v, vector<vector<int>> &g)
{
    g[u].push_back(v);
}

int topoSort(vector<int> &input, int n, int m, vector<int> degree, vector<vector<int>> &g)
{
    queue<int> q;
    vector<int> val(n + (m - 1) * 3 + 3 + 1, 0);
    for (int i = 1; i <= m; i++) { if (degree[i] == 0) { q.push(i); } }
    for (int i = 1; i <= n; i++) {
        for (size_t j = 0; j < g[i].size(); j++) {
            val[g[i][j]] = input[i];
        }
    }
    int res = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        int in1 = (u - 1) * 3 + 1 + n;
        int in2 = (u - 1) * 3 + 2 + n;
        int out = (u - 1) * 3 + 3 + n;
        res = val[out] = !(val[in1] & val[in2]);
        for (size_t i = 0; i < g[out].size(); i++) {
            val[g[out][i]] = val[out];
            int v = (g[out][i] - n - 1) / 3 + 1;
            if (--degree[v] == 0) { q.push(v); }
        }
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    int T, n, m, a, b;
    vector<int> degree, input;
    vector<vector<int>> g;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        degree.clear();
        g.clear();
        degree.resize(m + 1);
        g.resize(n + (m - 1) * 3 + 3 + 1);
        for (int i = 1; i <= m; i++) {
            cin >> a >> b;
            int in1 = (i - 1) * 3 + 1 + n;
            int in2 = (i - 1) * 3 + 2 + n;
            int node = 0;
            if (a < 0) {
                node = -a;
            } else {
                node = (a - 1) * 3 + 3 + n;
                degree[i]++;
            }
            addEdge(node, in1, g);
            if (b < 0) {
                node = -b;
            } else {
                node = (b - 1) * 3 + 3 + n;
                degree[i]++;
            }
            addEdge(node, in2, g);
        }
        input.clear();
        input.resize(n + 1, 0);
        int res1 = topoSort(input, n, m, degree, g);
        for (int i = 1; i <= n; i++) { input[i] = 1; }
        int res2 = topoSort(input, n, m, degree, g);
        if (res1 == res2) {
            for (int i = 0; i < n; i++) { cout << "0"; }
            cout << endl;
        } else {
            int left = 1, right = n;
            while (left <= right) {
                int mid = (left + right) >> 1;
                for (int i = 1; i <= n; i++) { input[i] = i <= mid ? 1 : 0; }
                if (topoSort(input, n, m, degree, g) != res1) { right = mid - 1; }
                else { left = mid + 1; }
            }
            for (int i = 1; i <= n; i++) { cout << (i <  left ? "1" : (i == left ? "x" : "0")); }
            cout << endl;
        }
    }
    return 0;
}
