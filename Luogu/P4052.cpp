// problem statement: https://www.luogu.com.cn/problem/P4052

#include <array>
#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

template <int MAX_NODE_NUM, int ALPHABET_SIZE, typename id_generator>
class aho_corasick_automaton {
public:
    struct node {
        int fail{};
        bool out{};
        std::vector<int> word_ids;
        std::array<int, ALPHABET_SIZE> to{};
    };

    int node_count{1};
    std::array<node, MAX_NODE_NUM + 1> trie;

    template <typename T>
    int add(const T &word, int word_id = 0) {
        int u = 0;
        for (auto &&ch : word) {
            int c = get_id(ch);
            if (trie[u].to[c] == 0) { trie[u].to[c] = node_count++; }
            u = trie[u].to[c];
        }
        trie[u].word_ids.emplace_back(word_id);
        trie[u].out = true;
        return u;
    }

    void build() {
        std::queue<int> q;
        for (int c = 0; c < ALPHABET_SIZE; c++) {
            if (trie[0].to[c]) { q.push(trie[0].to[c]); }
        }
        while (!q.empty()) {
            int u = q.front();
            trie[u].out = trie[u].out || trie[trie[u].fail].out;
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
    int operator()(char ch) { return ch - 'A'; }
};

aho_corasick_automaton<100 * 60, 26, generator> ac;

constexpr int MOD = 1e4 + 7;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::string word;
    for (int i = 0; i < n; i++) {
        std::cin >> word;
        ac.add(word);
    }
    ac.build();
    std::vector<std::array<int, 2>> dp(ac.node_count, {0, 0});
    dp[0][0] = 1;
    for (int i = 0; i < m; i++) {
        std::vector<std::array<int, 2>> ndp(ac.node_count, {0, 0});
        for (int u = 0; u < ac.node_count; u++) {
            for (int t = 0; t < 2; t++) {
                if (dp[u][t] == 0) { continue; }
                for (int c = 0; c < 26; c++) {
                    int v = ac.trie[u].to[c];
                    int nt = t || ac.trie[v].out;
                    ndp[v][nt] = (ndp[v][nt] + dp[u][t]) % MOD;
                }
            }
        }
        dp = std::move(ndp);
    }
    int ans = 0;
    for (int u = 0; u < ac.node_count; u++) { ans = (ans + dp[u][1]) % MOD; }
    std::cout << ans << '\n';
    return 0;
}
