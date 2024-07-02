// problem statement: https://www.luogu.com.cn/problem/P5357

#include <bits/stdc++.h>

constexpr size_t MAX_PATTERN_NUM = 2e5 + 10;
constexpr size_t MAX_TEXT_LEN    = 2e6 + 10;

using namespace std;

template <size_t MAX_NODE_NUM, size_t MAX_ALPHABET_SIZE>
struct ac_automaton {
    ac_automaton() { clear(); }

    void clear() {
        node_num = 1;
        memset(to, 0, sizeof(to));
        memset(fail, 0, sizeof(fail));
        memset(pos, 0, sizeof(pos));
    }

    void add_word(const string &word, const size_t &index) {
        size_t now = root;
        for (const auto &ch : word) {
            if (to[now][ch - 'a'] == 0) { to[now][ch - 'a'] = ++node_num; }
            now = to[now][ch - 'a'];
        }
        pos[index] = now;
    }

    void build() {
        queue<size_t> q;
        fail[root] = root;
        for (int i = 0; i < MAX_ALPHABET_SIZE; i++) {
            if (to[root][i] != 0) {
                q.push(to[root][i]);
                fail[to[root][i]] = root;
            } else {
                to[root][i] = root;
            }
        }
        while (!q.empty()) {
            size_t u = q.front();
            q.pop();
            for (int i = 0; i < MAX_ALPHABET_SIZE; i++) {
                if (to[u][i] != 0) {
                    fail[to[u][i]] = to[fail[u]][i];
                    q.push(to[u][i]);
                } else {
                    to[u][i] = to[fail[u]][i];
                }
            }
        }
    }

    size_t node_num              = 1;
    static constexpr size_t root = 1;
    size_t to[MAX_NODE_NUM][MAX_ALPHABET_SIZE];
    size_t fail[MAX_NODE_NUM];
    size_t pos[MAX_PATTERN_NUM];
};

ac_automaton<(size_t)2e5 + 10, 26> ac;

int n;
string pattern, text;
size_t match_cnt[(size_t)2e5 + 10];
vector<int> g[(size_t)2e5 + 10];

void add_edge(int u, int v) { g[u].push_back(v); }

void dfs(int u) {
    for (auto v : g[u]) {
        dfs(v);
        match_cnt[u] += match_cnt[v];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> pattern;
        ac.add_word(pattern, i);
    }
    ac.build();
    cin >> text;
    size_t now = ac.root;
    for (auto ch : text) {
        now = ac.to[now][ch - 'a'];
        match_cnt[now]++;
    }
    for (int i = 2; i <= ac.node_num; i++) { add_edge(ac.fail[i], i); }
    dfs(ac.root);
    for (int i = 0; i < n; i++) { cout << match_cnt[ac.pos[i]] << '\n'; }
    return 0;
}
