// problem statement: https://www.luogu.com.cn/problem/P3805

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

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

int main() {
    std::ios::sync_with_stdio(false);
    std::string str;
    std::cin >> str;
    auto &&p = manacher(str);
    std::cout << *std::max_element(p.begin(), p.end()) - 1 << '\n';
    return 0;
}
