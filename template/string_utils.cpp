#include <array>
#include <cassert>
#include <queue>
#include <vector>

class string_utils {
    template <typename T>
    std::vector<int> get_next(const T &word) {
        assert(word.size() > 0);
        std::vector<int> next(word.size() + 1);
        next[0] = -1;
        next[1] = 0;
        int i = 1, j = 0;
        while (i < word.size()) {
            if (word[i] == word[j]) {
                i++;
                j++;
                next[i] = j;
            } else if (j == 0) {
                i++;
            } else {
                j = next[j];
            }
        }
        return next;
    }

    // Return the match position, zero-indexed
    template <typename T>
    std::vector<int> kmp(const T &text, const T &word) {
        std::vector<int> res;
        auto &&next = get_next(word);
        int i = 0, j = 0;
        while (i < text.size()) {
            if (text[i] == word[j]) {
                i++;
                j++;
                if (j == word.size()) {
                    res.emplace_back(i - j);
                    j = next[j];
                }
            } else if (j == 0) {
                i++;
            } else {
                j = next[j];
            }
        }
        return res;
    }

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
};
