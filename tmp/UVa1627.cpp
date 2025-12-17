#include <bits/stdc++.h>

using namespace std;

bool dfs(int u, int col, vector<vector<int>> &g, vector<int> &color) {
    color[u] = col;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (color[v] != -1 && color[v] != (col ^ 1)) { return false; }
        if (color[v] == -1 && !dfs(v, col ^ 1, g, color)) { return false; }
    }
    return true;
}

void print(int i,
           int j,
           vector<vector<bool>> &dp,
           vector<int> &val,
           vector<pair<vector<int>, vector<int>>> &person,
           vector<int> &ans0,
           vector<int> &ans1,
           int sum) {
    if (i == 0) {
        if (j == val[i] + sum) {
            for (int k = 0; k < person[i].first.size(); k++) { ans0.push_back(person[i].first[k]); }
            for (int k = 0; k < person[i].second.size(); k++) {
                ans1.push_back(person[i].second[k]);
            }
        } else {
            for (int k = 0; k < person[i].first.size(); k++) { ans1.push_back(person[i].first[k]); }
            for (int k = 0; k < person[i].second.size(); k++) {
                ans0.push_back(person[i].second[k]);
            }
        }
        return;
    }
    if (j - val[i] >= 0 && j - val[i] < sum * 2 + 1 && dp[i - 1][j - val[i]]) {
        print(i - 1, j - val[i], dp, val, person, ans0, ans1, sum);
        for (int k = 0; k < person[i].first.size(); k++) { ans0.push_back(person[i].first[k]); }
        for (int k = 0; k < person[i].second.size(); k++) { ans1.push_back(person[i].second[k]); }
    } else if (j + val[i] >= 0 && j + val[i] < sum * 2 + 1 && dp[i - 1][j + val[i]]) {
        print(i - 1, j + val[i], dp, val, person, ans0, ans1, sum);
        for (int k = 0; k < person[i].first.size(); k++) { ans1.push_back(person[i].first[k]); }
        for (int k = 0; k < person[i].second.size(); k++) { ans0.push_back(person[i].second[k]); }
    }
}

int main() {
    ios::sync_with_stdio(false);
    int T, N;
    cin >> T;
    vector<vector<int>> g;
    while (T--) {
        cin >> N;
        g.clear();
        g.resize(N + 1);
        for (int i = 1; i <= N; i++) {
            int who;
            vector<bool> know(N + 1, false);
            know[i] = true;
            while (cin >> who && who != 0) { know[who] = true; }
            for (int j = 1; j <= N; j++) {
                if (!know[j]) {
                    g[i].push_back(j);
                    g[j].push_back(i);
                }
            }
        }
        vector<int> color(N + 1, -1);
        vector<int> vis(N + 1, false);
        vector<int> val;
        vector<pair<vector<int>, vector<int>>> person;
        vector<int> ans0, ans1;
        bool ok = true;
        for (int i = 1; i <= N; i++) {
            if (color[i] == -1) {
                if (!dfs(i, 0, g, color)) {
                    ok = false;
                    break;
                } else {
                    int col0 = 0, col1 = 0;
                    vector<int> person0, person1;
                    for (int i = 1; i <= N; i++) {
                        if (!vis[i] && color[i] != -1) {
                            vis[i] = true;
                            if (color[i] == 0) {
                                person0.push_back(i);
                                col0++;
                            } else {
                                person1.push_back(i);
                                col1++;
                            }
                        }
                    }
                    val.push_back(col0 - col1);
                    person.push_back({person0, person1});
                }
            }
        }
        if (!ok) {
            cout << "No solution" << endl;
        } else {
            int sum = 0;
            vector<vector<bool>> dp;
            for (int i = 0; i < val.size(); i++) { sum += abs(val[i]); }
            dp.resize(val.size());
            for (int i = 0; i < val.size(); i++) { dp[i].resize(sum * 2 + 1, false); }
            for (int i = 0; i < val.size(); i++) {
                if (i == 0) {
                    dp[i][val[i] + sum] = true;
                    dp[i][-val[i] + sum] = true;
                    continue;
                }
                for (int j = 0; j < sum * 2 + 1; j++) {
                    if (j - val[i] >= 0 && j - val[i] < sum * 2 + 1) {
                        dp[i][j] = max(dp[i][j], dp[i - 1][j - val[i]]);
                    }
                    if (j + val[i] >= 0 && j + val[i] < sum * 2 + 1) {
                        dp[i][j] = max(dp[i][j], dp[i - 1][j + val[i]]);
                    }
                }
            }
            int ans = numeric_limits<int>::max(), ansj = 0;
            for (int j = 0; j < sum * 2 + 1; j++) {
                if (dp[val.size() - 1][j]) {
                    int temp = abs(j - sum);
                    if (temp < ans) {
                        ans = temp;
                        ansj = j;
                    }
                }
            }
            print(val.size() - 1, ansj, dp, val, person, ans0, ans1, sum);
            cout << ans0.size();
            for (int i = 0; i < ans0.size(); i++) { cout << " " << ans0[i]; }
            cout << endl << ans1.size();
            for (int i = 0; i < ans1.size(); i++) { cout << " " << ans1[i]; }
            cout << endl;
        }
        if (T != 0) { cout << endl; }
    }
    return 0;
}