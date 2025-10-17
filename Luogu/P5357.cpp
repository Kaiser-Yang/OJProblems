// problem statement: https://www.luogu.com.cn/problem/P3357

#include <array>
#include <cstdint>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

const int MAX_SIGMA_WORD_LEN = 2e5 + 10;

template <int MAX_NODE_NUM, int ALPHABET_SIZE, typename id_generator>
class aho_corasick_automaton {
public:
    struct node {
        int fail{};
        std::vector<int> word_ids;
        std::array<int, ALPHABET_SIZE> to{};
    };

    int node_count{1};
    std::array<node, MAX_NODE_NUM> trie;

    template <typename T>
    int add(const T &word, int word_id = 0) {
        int u = 0;
        for (auto &&ch : word) {
            int c = get_id(ch);
            if (trie[u].to[c] == 0) { trie[u].to[c] = node_count++; }
            u = trie[u].to[c];
        }
        trie[u].word_ids.emplace_back(word_id);
        return u;
    }

    void build() {
        std::queue<int> q;
        for (int c = 0; c < ALPHABET_SIZE; c++) {
            if (trie[0].to[c]) { q.push(trie[0].to[c]); }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int c = 0; c < ALPHABET_SIZE; c++) {
                int v = trie[u].to[c];
                if (v == 0) {
                    trie[u].to[c] = trie[trie[u].fail].to[c];
                } else {
                    trie[v].fail = trie[trie[u].fail].to[c];
                    q.push(v);
                }
            }
        }
    }

private:
    id_generator get_id;
};

struct generator {
    int operator()(char ch) { return ch - 'a'; }
};

aho_corasick_automaton<MAX_SIGMA_WORD_LEN, 26, generator> ac;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::string word;
    std::vector<int> pos(n);
    for (int i = 0; i < n; i++) {
        std::cin >> word;
        pos[i] = ac.add(word);
    }
    ac.build();
    std::string text;
    std::cin >> text;
    int now = 0;
    std::vector<int> cnt(ac.node_count);
    for (auto &&ch : text) {
        now = ac.trie[now].to[ch - 'a'];
        cnt[now]++;
    }
    std::vector<std::vector<int>> g(ac.node_count);
    for (int i = 1; i < ac.node_count; i++) {
        g[ac.trie[i].fail].emplace_back(i);
    }
    std::function<void(int)> dfs = [&](int u) {
        for (auto &&v : g[u]) {
            dfs(v);
            cnt[u] += cnt[v];
        }
    };
    dfs(0);
    for (int i = 0; i < n; i++) { std::cout << cnt[pos[i]] << '\n'; }
    return 0;
}
