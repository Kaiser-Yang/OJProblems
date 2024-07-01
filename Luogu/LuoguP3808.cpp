// problem statement: https://www.luogu.com.cn/problem/P3808

#include <bits/stdc++.h>

const int MAX_PATTERN_NUM = 1e6 + 10;
const int MAX_TEXT_LEN    = 1e6 + 10;

using namespace std;

int n;
string pattern, text;

template <size_t MAX_NODE_NUM, size_t MAX_ALPHABET_SIZE>
struct ac_automaton {
    ac_automaton() {
        memset(to, 0, sizeof(to));
        memset(fail, 0, sizeof(fail));
        memset(word_num, 0, sizeof(word_num));
    }

    void add_word(const string &pattern) {
        int now = root;
        for (int i = 0; i < pattern.length(); i++) {
            int x = pattern[i] - 'a';
            if (to[now][x] != 0) {
                now = to[now][x];
            } else {
                to[now][x] = ++node_num;
                now        = node_num;
            }
        }
        word_num[now]++;
    }

    void build() {
        queue<size_t> q;
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

    size_t to[MAX_NODE_NUM][MAX_ALPHABET_SIZE];
    size_t fail[MAX_NODE_NUM];
    int word_num[MAX_NODE_NUM];
    size_t node_num              = 1;
    constexpr static size_t root = 1;
};

ac_automaton<MAX_PATTERN_NUM, 26> ac;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> pattern;
        ac.add_word(pattern);
    }
    ac.build();
    cin >> text;
    int now = ac.root, ans = 0;
    for (int i = 0; i < text.length(); i++) {
        now = ac.to[now][text[i] - 'a'];
        for (int j = now; j != ac.root; j = ac.fail[j]) {
            if (ac.word_num[j] == -1) { break; }
            ans += ac.word_num[j];
            ac.word_num[j] = -1;
        }
    }
    cout << ans << endl;
    return 0;
}
