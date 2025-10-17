// problem statement: https://www.luogu.com.cn/problem/P3311

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
    int operator()(char ch) const { return ch - '0'; }
};

constexpr int MAX_SIGMA_WORD_LEN = 1500;
constexpr int MOD = 1000000007;

aho_corasick_automaton<MAX_SIGMA_WORD_LEN, 10, generator> ac;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string n;
    std::cin >> n;
    int m;
    std::cin >> m;
    std::string word;
    for (int i = 0; i < m; i++) {
        std::cin >> word;
        ac.add(word);
    }
    ac.build();

    std::vector<std::array<i64, 4>> dp(ac.node_count, std::array<i64, 4>{0, 0, 0, 0});
    dp[0][0] = 1;
    for (size_t i = 0; i < n.size(); i++) {
        std::vector<std::array<i64, 4>> ndp(ac.node_count, std::array<i64, 4>{0, 0, 0, 0});
        for (int u = 0; u < ac.node_count; u++) {
            for (int t = 0; t < 2; t++) {
                for (int s = 0; s < 2; s++) {
                    int st = t * 2 + s;
                    if (dp[u][st] == 0) { continue; }
                    for (int c = 0; c < 10; c++) {
                        if (t == 0 && c > n[i] - '0') { continue; }
                        int nt = (t == 1 || c < n[i] - '0'), v = -1, nst = -1;
                        if (s == 0) {
                            if (c == 0) {
                                v = 0;
                                nst = nt * 2 + 0;
                            } else {
                                v = ac.trie[0].to[c];
                                nst = nt * 2 + 1;
                            }
                        } else {
                            v = ac.trie[u].to[c];
                            nst = nt * 2 + 1;
                        }
                        if (ac.trie[v].out) { continue; }
                        ndp[v][nst] = (ndp[v][nst] + dp[u][st]) % MOD;
                    }
                }
            }
        }
        dp = std::move(ndp);
    }

    i64 ans = 0;
    for (int u = 0; u < ac.node_count; u++) {
        ans = (ans + dp[u][0 * 2 + 1]) % MOD;
        ans = (ans + dp[u][1 * 2 + 1]) % MOD;
    }
    std::cout << ans << '\n';
    return 0;
}
