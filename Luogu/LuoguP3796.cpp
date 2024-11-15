// problem statement: https://www.luogu.com.cn/problem/P3796

#include <bits/stdc++.h>

const int MAX_TEXT_LEN = 1E6 + 10;
const int MAX_PATTERN_NUM = 150 + 10;

using namespace std;

int pattern_num;
string text;
vector<string> pattern;

template <size_t MAX_NODE_NUM, size_t MAX_ALPHABET_SIZE>
struct ac_automaton {
    ac_automaton() { clear(); }

    void add_word(const string &word, const size_t &index) {
        size_t now = root;
        for (int i = 0; i < word.length(); i++) {
            if (to[now][word[i] - 'a'] == 0) { to[now][word[i] - 'a'] = ++node_num; }
            now = to[now][word[i] - 'a'];
        }
        this->index[now] = index;
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
            int u = q.front();
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

    void clear() {
        node_num = 1;
        memset(fail, 0, sizeof(fail));
        memset(to, 0, sizeof(to));
        memset(index, -1, sizeof(index));
    }

    static constexpr size_t root = 1;
    size_t node_num = 1;
    size_t fail[MAX_NODE_NUM];
    size_t to[MAX_NODE_NUM][MAX_ALPHABET_SIZE];
    size_t index[MAX_NODE_NUM];
};

ac_automaton<MAX_PATTERN_NUM * 70, 26> ac;

size_t cnt[MAX_PATTERN_NUM * 70];

map<size_t, vector<size_t>> ans;

bool vis[MAX_PATTERN_NUM * 70];

void dfs(int u) {
    vis[u] = true;
    if (cnt[u] > 0) {
        if (ans.count(cnt[u]) == 0) { ans[cnt[u]] = vector<size_t>(); }
        ans[cnt[u]].push_back(ac.index[u]);
    }
    for (int i = 0; i < 26; i++) {
        if (ac.to[u][i] != 0 && !vis[ac.to[u][i]]) { dfs(ac.to[u][i]); }
    }
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> pattern_num && pattern_num != 0) {
        pattern.resize(pattern_num);
        for (int i = 0; i < pattern_num; i++) {
            cin >> pattern[i];
            ac.add_word(pattern[i], i);
        }
        ac.build();
        cin >> text;
        int now = ac.root;
        for (int i = 0; i < text.length(); i++) {
            now = ac.to[now][text[i] - 'a'];
            for (int j = now; j != ac.root; j = ac.fail[j]) {
                if (ac.index[j] != -1) {
                    cnt[j]++;
                    break;
                }
            }
        }
        for (int i = 1; i <= ac.node_num; i++) {
            if (cnt[i] == 0) { continue; }
            for (int j = i; j != ac.root; j = ac.fail[j]) {
                if (ac.index[ac.fail[j]] == -1 || vis[ac.fail[j]]) { continue; }
                cnt[ac.fail[j]] += cnt[i];
                vis[ac.fail[j]] = true;
            }
        }
        memset(vis, 0, sizeof(vis));
        dfs(ac.root);
        if (ans.size() == 0) {
            cout << "0\n";
            continue;
        }
        cout << ans.rbegin()->first << "\n";
        sort(ans.rbegin()->second.begin(), ans.rbegin()->second.end());
        for (int i = 0; i < ans.rbegin()->second.size(); i++) {
            cout << pattern[ans.rbegin()->second[i]] << "\n";
        }
        ac.clear();
        ans.clear();
        memset(cnt, 0, sizeof(cnt));
        memset(vis, 0, sizeof(vis));
    }
    return 0;
}
