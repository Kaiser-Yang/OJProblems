// problem statement: https://www.luogu.com.cn/problem/P3879

#include <bits/stdc++.h>

using namespace std;

template <size_t MAX_ALPHABET_NUM>
struct trie {
    trie() { clear(); }
    void clear() {
        to.resize(2, vector<size_t>(MAX_ALPHABET_NUM));
        index.resize(2, set<size_t>());
    }
    void add_word(const string &word, size_t index) {
        int now = root;
        for (auto &&ch : word) {
            if (to[now][ch - 'a'] == 0) {
                to[now][ch - 'a'] = to.size();
                to.emplace_back(MAX_ALPHABET_NUM);
                this->index.emplace_back();
            }
            now = to[now][ch - 'a'];
        }
        this->index[now].insert(index);
    }
    void query(const string &word) {
        int now = root;
        for (auto &&ch : word) {
            if (to[now][ch - 'a'] == 0) {
                now = 0;
                break;
            }
            now = to[now][ch - 'a'];
        }
        for (auto iter = this->index[now].begin(); iter != this->index[now].end(); iter++) {
            cout << *iter << (next(iter) == this->index[now].end() ? "" : " ");
        }
        cout << '\n';
    }

    static constexpr size_t root = 1;
    vector<vector<size_t>> to;
    vector<set<size_t>> index;
};

trie<26> t;

size_t n, m, word_num;
string word;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (size_t i = 1; i <= n; i++) {
        cin >> word_num;
        for (size_t j = 0; j < word_num; j++) {
            cin >> word;
            t.add_word(word, i);
        }
    }
    cin >> m;
    for (size_t i = 0; i < m; i++) {
        cin >> word;
        t.query(word);
    }
    return 0;
}
