#include <array>
#include <cassert>
#include <cstdint>
#include <queue>
#include <string>
#include <vector>

using u64 = uint64_t;

class string_utils {
public:
    template <typename T>
    std::vector<int> kmp_next(const T &word) {
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
        auto &&next = kmp_next(word);
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

    template <typename T>
    std::vector<int> manacher(const T &s) {
        int n = s.size();
        if (n == 0) { return {}; }
        std::vector<int> p(2 * n + 1);
        T t(2 * n + 1, s[0]);
        for (int i = 0; i < n; i++) {
            t[2 * i] = s[0];
            t[2 * i + 1] = s[i];
        }
        t[2 * n] = s[0];
        int center = -1, right = 0;
        for (int i = 0; i < t.size(); i++) {
            if (i < right) { p[i] = std::min(p[2 * center - i], right - i); }
            while (i - p[i] >= 0 && i + p[i] < t.size() && t[i - p[i]] == t[i + p[i]]) { p[i]++; }
            if (i + p[i] > right) {
                center = i;
                right = i + p[i];
            }
        }
        return p;
    }

    template <typename T = u64, T base = T(131), T mod = T(1e9 + 7)>
    class hash {
    public:
        hash(const std::string &s) { build(s); }

        // [0, pos)
        T get(int pos) const {
            assert(pos >= 0 && pos < prefix_hash.size());
            return prefix_hash[pos];
        }

        // [l, r)
        T get(int l, int r) const {
            assert(l >= 0 && r < prefix_hash.size() && l < r);
            return (prefix_hash[r] - prefix_hash[l] * power[r - l] % mod + mod) % mod;
        }

    private:
        void build(const std::string &s) {
            auto n = s.size();
            prefix_hash.resize(n + 1, 0);
            power.resize(n + 1, 1);
            for (int i = 0; i < n; i++) {
                prefix_hash[i + 1] = (prefix_hash[i] * base + s[i]) % mod;
                power[i + 1] = (power[i] * base) % mod;
            }
        }

        std::vector<T> prefix_hash;
        std::vector<T> power;
    };

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
