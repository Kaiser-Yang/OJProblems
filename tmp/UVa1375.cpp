#include <bits/stdc++.h>

using namespace std;

int cnt;
map<string, int> id;
map<int, string> name;

int ID(const string &s) {
    if (!id.count(s)) {
        name[cnt] = s;
        id[s] = cnt++;
    }
    return id[s];
}

bool isAllLowerCase(const string &s) {
    for (auto ch : s) {
        if (ch != tolower(ch)) { return false; }
    }
    return true;
}

string myMin(const string &s1, const string &s2) {
    if (s1 != "-" && s2 != "-") { return min(s1, s2); }
    return s1 == "-" ? s2 : s1;
}

int main() {
    ios::sync_with_stdio(false);
    int n, l;
    vector<string> rule;
    vector<vector<pair<int, int>>> g;
    vector<vector<string>> dp;
    vector<int> head, tail;
    while (cin >> n >> l && !(n == 0 && l == 0)) {
        rule.resize(n);
        id.clear();
        cnt = 0;
        name.clear();
        ID("");
        g.clear();
        g.resize(n * 20 + n + 2 + 10);
        head.clear();
        head.resize(g.size());
        tail.clear();
        tail.resize(g.size());
        for (int i = 0; i < n; i++) {
            cin >> rule[i];
            int left = ID(rule[i].substr(0, 1));
            int right = ID(rule[i].substr(2));
            int len = rule[i].length();
            g[right].push_back({left, ID("")});
            for (int j = 2; j < len; j++) {
                string S = rule[i].substr(j);
                int s = ID(S);
                if (S.length() < 2) { continue; }
                int h = ID(S.substr(0, 1));
                int t = ID(S.substr(1, S.length() - 1));
                g[h].push_back({s, t});
                g[t].push_back({s, h});
                head[s] = h;
                tail[s] = t;
            }
        }
        dp.clear();
        dp.resize(cnt);
        for (int i = 0; i < cnt; i++) { dp[i].resize(l + 1, "-"); }
        dp[0][0] = "";
        for (int j = 0; j <= l; j++) {
            for (int i = 0; i < cnt; i++) {
                if (name[i].length() == j && isAllLowerCase(name[i])) { dp[i][j] = name[i]; }
                if (name[i].length() < 2) { continue; }
                int s1 = head[i], s2 = tail[i];
                for (int k = 1; k < j; k++) {
                    if (dp[s1][k] != "-" && dp[s2][j - k] != "-") {
                        dp[i][j] = myMin(dp[i][j], dp[s1][k] + dp[s2][j - k]);
                    }
                }
            }
            vector<bool> vis(cnt);
            priority_queue<pair<string, int>, vector<pair<string, int>>, greater<pair<string, int>>>
                q;
            for (int i = 0; i < cnt; i++) {
                if (dp[i][j] != "-") { q.push({dp[i][j], i}); }
            }
            while (!q.empty()) {
                auto top = q.top();
                q.pop();
                int &&u = std::move(top.second);
                string &&s = std::move(top.first);
                if (vis[u]) { continue; }
                vis[u] = true;
                for (int k = 0; k < g[u].size(); k++) {
                    int target = g[u][k].first;
                    int empty = g[u][k].second;
                    if (dp[empty][0] == "" && (dp[target][j] == "-" || s < dp[target][j])) {
                        dp[target][j] = s;
                        q.push({s, target});
                    }
                }
            }
        }
        if (ID("S") >= dp.size()) {
            cout << "-" << endl;
        } else {
            cout << dp[ID("S")][l] << endl;
        }
    }
    return 0;
}
