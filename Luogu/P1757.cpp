// problem statement: https://www.luogu.com.cn/problem/P1757

#include <array>
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> m >> n;
    std::unordered_map<int, int> id;
    std::vector<std::vector<std::array<int, 2>>> items;
    for (int i = 0; i < n; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        if (!id.count(c)) { id[c] = id.size(); }
        items.resize(id.size());
        items[id[c]].push_back({a, b});
    }
    std::vector<i64> dp(m + 1);
    for (int i = 0; i < items.size(); i++) {
        std::vector<i64> ndp(m + 1);
        for (int j = 0; j <= m; j++) {
            ndp[j] = dp[j];
            for (const auto &item : items[i]) {
                if (j >= item[0]) { ndp[j] = std::max(ndp[j], dp[j - item[0]] + item[1]); }
            }
        }
        dp = std::move(ndp);
    }
    std::cout << dp[m] << "\n";
    return 0;
}
