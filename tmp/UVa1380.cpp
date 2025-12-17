#include <bits/stdc++.h>

using namespace std;

const int INF = 1e7;

bool dp(int u, int fa, int x, vector<int> &f, vector<int> &g, vector<vector<pair<int, int>>> &son) {
    if (son[u].size() == 0) {
        f[u] = g[u] = 0;
        return true;
    }
    vector<int> temp;
    int maxSonF = 0, maxSonG = 0;
    for (int i = 0; i < son[u].size(); i++) {
        if (son[u][i].first == fa) { continue; }
        if (!dp(son[u][i].first, u, x, f, g, son)) { return false; }
        if (son[u][i].second == 0) {
            temp.push_back(son[u][i].first);
        } else if (son[u][i].second == 1) {  // downward
            maxSonG = max(maxSonG, g[son[u][i].first] + 1);
        } else {  // upward
            maxSonF = max(maxSonF, f[son[u][i].first] + 1);
        }
    }
    if (temp.empty()) {
        f[u] = maxSonF;
        g[u] = maxSonG;
        if (f[u] + g[u] + 1 > x) { f[u] = g[u] = INF; }
        return f[u] + g[u] + 1 <= x;
    }
    f[u] = g[u] = INF;
    vector<int> maxG(temp.size() + 1), maxF(temp.size() + 1);
    sort(temp.begin(), temp.end(), [&f](int i, int j) { return f[i] < f[j]; });
    for (int i = temp.size() - 1; i >= 0; i--) { maxG[i] = max(g[temp[i]], maxG[i + 1]); }
    for (int i = 0; i <= temp.size(); i++) {
        int maxSonF0 = maxSonF, maxSonG0 = maxSonG;
        if (i > 0) { maxSonF0 = max(maxSonF0, f[temp[i - 1]] + 1); }
        if (i < temp.size()) { maxSonG0 = max(maxSonG0, maxG[i] + 1); }
        if (maxSonF0 + maxSonG0 + 1 <= x) {
            f[u] = maxSonF0;
            break;
        }
    }
    sort(temp.begin(), temp.end(), [&g](int i, int j) { return g[i] < g[j]; });
    for (int i = temp.size() - 1; i >= 0; i--) { maxF[i] = max(f[temp[i]], maxF[i + 1]); }
    for (int i = 0; i <= temp.size(); i++) {
        int maxSonF0 = maxSonF, maxSonG0 = maxSonG;
        if (i > 0) { maxSonG0 = max(maxSonG0, g[temp[i - 1]] + 1); }
        if (i < temp.size()) { maxSonF0 = max(maxSonF0, maxF[i] + 1); }
        if (maxSonF0 + maxSonG0 + 1 <= x) {
            g[u] = maxSonG0;
            break;
        }
    }
    if (f[u] + g[u] + 1 > x) { f[u] = g[u] = INF; }
    return f[u] + g[u] + 1 <= x;
}

int dfs(int u, int fa, vector<vector<pair<int, int>>> &son) {
    int ans = 0;
    for (int i = 0; i < son[u].size(); i++) {
        int v = son[u][i].first;
        if (v == fa) { continue; }
        if (son[u][i].second == 1) { ans = max(ans, dfs(v, u, son) + 1); }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    while (true) {
        string x;
        bool first = true;
        bool father = true;
        int u = 0;
        vector<vector<pair<int, int>>> son(201);
        vector<bool> haveFather(201);
        // int left = 1, right = 0;
        int n = 0;
        while (cin >> x) {
            if (first && x == "0") {
                return 0;
            } else if (!father && x == "0") {
                father = true;
                continue;
            } else if (father && x == "0") {
                break;
            }
            if (!father) {
                int v;
                if (x.back() == 'd') {
                    x.pop_back();
                    v = stoi(x);
                    son[u].push_back({v, 1});
                    son[v].push_back({u, 2});
                } else if (x.back() == 'u') {
                    x.pop_back();
                    v = stoi(x);
                    son[u].push_back({v, 2});
                    son[v].push_back({u, 1});
                } else {
                    v = stoi(x);
                    son[u].push_back({v, 0});
                    son[v].push_back({u, 0});
                }
                haveFather[v] = true;
            } else {
                u = stoi(x);
                father = false;
                n++;
            }
            first = false;
        }
        int root = 0;
        for (int i = 1; i <= n; i++) {
            if (!haveFather[i]) {
                root = i;
                break;
            }
        }
        int longest = 0;
        for (int i = 1; i <= 200; i++) { longest = max(longest, dfs(i, 0, son) + 1); }
        vector<int> f(201), g(201);
        if (dp(root, 0, longest, f, g, son)) {
            cout << longest << endl;
        } else {
            cout << longest + 1 << endl;
        }
    }
    return 0;
}
