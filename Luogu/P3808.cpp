// problem statement: https://www.luogu.com.cn/problem/P3808

#include <array>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

const int MAX_PATTERN_NUM = 1e6 + 10;
const int MAX_TEXT_LEN = 1e6 + 10;

template <int MAX_NODE_NUM, int ALPHABET_SIZE, typename id_generator>
class aho_corasick_automaton {
public:
    struct node {
        int fail{};
        std::vector<int> word_ids;
        std::array<int, ALPHABET_SIZE> to{};
    };

    int node_count{1};
    std::array<node, MAX_NODE_NUM + 1> trie;

    template <typename T>
    void add(const T &word, int word_id = 0) {
        int u = 0;
        for (auto &&ch : word) {
            int c = get_id(ch);
            if (trie[u].to[c] == 0) { trie[u].to[c] = node_count++; }
            u = trie[u].to[c];
        }
        trie[u].word_ids.emplace_back(word_id);
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

aho_corasick_automaton<MAX_PATTERN_NUM, 26, generator> ac;

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::string word;
    for (int i = 0; i < n; i++) {
        std::cin >> word;
        ac.add(word);
    }
    ac.build();
    std::string text;
    std::cin >> text;
    int ans = 0, now = 0;
    std::vector<bool> visited(ac.node_count, false);
    for (auto &&ch : text) {
        int c = ch - 'a';
        now = ac.trie[now].to[c];
        for (int j = now; j != 0; j = ac.trie[j].fail) {
            if (visited[j]) { break; }
            visited[j] = true;
            ans += ac.trie[j].word_ids.size();
        }
    }
    std::cout << ans << std::endl;
    return 0;
}
