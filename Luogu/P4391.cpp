// problem statement: https://www.luogu.com.cn/problem/P4391

#include <cassert>
#include <vector>
#include <cstdint>
#include <iostream>
#include <string>

using i64 = int64_t;
using u64 = uint64_t;

template<typename T>
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
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    auto &&next = get_next(s);
    int x = next[s.size()];
    std::cout << n - x << std::endl;
    return 0;
}
