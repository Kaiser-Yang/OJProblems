// problem statement: https://www.luogu.com.cn/problem/P4824

#include <cassert>
#include <cstdint>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s, t;
    std::cin >> s >> t;
    std::stack<std::pair<int, int>> st;
    auto &&next = get_next(t);
    int j = 0;
    for (int i = 0; i < s.size(); i++) {
        while (j >= 0 && s[i] != t[j]) { j = next[j]; }
        j++;
        st.push({i, j});
        if (j == t.size()) {
            for (int k = 0; k < t.size(); k++) { st.pop(); }
            j = st.empty() ? 0 : st.top().second;
        }
    }
    std::string ans;
    while (!st.empty()) {
        ans.push_back(s[st.top().first]);
        st.pop();
    }
    std::reverse(ans.begin(), ans.end());
    std::cout << ans << std::endl;
    return 0;
}
