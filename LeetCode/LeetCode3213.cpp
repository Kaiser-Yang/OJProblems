// problem statement: https://leetcode.cn/problems/construct-string-with-minimum-cost/

#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
    class aho_corasick_automation {
    public:
        vector<vector<int>> son;
        vector<int> cost, fail, len, last;
        int tot = 0;
        void add(const string &s, int s_cost) {
            int u = 0;
            for (char c : s) {
                if (tot >= son.size()) { son.push_back(vector<int>(26)); }
                int v = c - 'a';
                if (!son[u][v]) { son[u][v] = ++tot; }
                if (tot >= son.size()) { son.push_back(vector<int>(26)); }
                u = son[u][v];
            }
            if (tot >= cost.size()) { cost.resize(tot + 1, std::numeric_limits<int>::max()); }
            if (tot >= len.size()) { len.resize(tot + 1, 0); }
            cost[u] = min(cost[u], s_cost);
            len[u] = s.size();
        }
        void build() {
            fail.resize(tot + 1);
            last.resize(tot + 1);
            queue<int> q;
            for (int i = 0; i < 26; i++) {
                if (son[0][i]) { q.push(son[0][i]); }
            }
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int i = 0; i < 26; i++) {
                    if (son[u][i]) {
                        q.push(son[u][i]);
                        fail[son[u][i]] = son[fail[u]][i];
                        last[son[u][i]] =
                            len[fail[son[u][i]]] > 0 ? fail[son[u][i]] : last[fail[son[u][i]]];
                    } else {
                        son[u][i] = son[fail[u]][i];
                    }
                }
            }
        }
    };

public:
    int minimumCost(string target, vector<string> &words, vector<int> &costs) {
        aho_corasick_automation ac;
        for (auto &&word : words) { ac.add(word, costs[&word - &words[0]]); }
        ac.build();
        int n = target.size();
        vector<int> dp(n + 1, std::numeric_limits<int>::max() / 2);
        dp[0] = 0;
        int cur = 0;
        for (int i = 1; i <= n; i++) {
            cur = ac.son[cur][target[i - 1] - 'a'];
            if (ac.len[cur] != 0) { dp[i] = min(dp[i], dp[i - ac.len[cur]] + ac.cost[cur]); }
            for (int j = ac.last[cur]; j != 0; j = ac.last[j]) {
                if (ac.len[j] != 0) { dp[i] = min(dp[i], dp[i - ac.len[j]] + ac.cost[j]); }
            }
        }
        return dp[n] == std::numeric_limits<int>::max() / 2 ? -1 : dp[n];
    }
};
