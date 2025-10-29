// problem statement: https://www.luogu.com.cn/problem/P1064

#include <array>
#include <cstdint>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::tuple<int, int, int>> tmp(m);
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        auto &&[v, p, q] = tmp[i];
        std::cin >> v >> p >> q;
        q--;
        if (q < 0) { cnt++; }
    }
    std::vector<std::vector<std::array<int, 2>>> items(cnt);
    auto get_id = [](int i) {
        static std::unordered_map<int, int> ids;
        if (ids.count(i) == 0) { ids[i] = ids.size(); }
        return ids[i];
    };
    auto init = [&](bool prime) {
        for (int i = 0; i < m; i++) {
            auto &&[v, p, q] = tmp[i];
            int id = -1;
            if (q >= 0) {
                if (prime) { continue; }
                id = get_id(q);
            } else {
                if (!prime) { continue; }
                id = get_id(i);
            }
            items[id].push_back({v, p});
        }
    };
    init(true);
    init(false);
    std::vector<int> dp(n + 1);
    for (int i = 0; i < cnt; i++) {
        for (int j = n; j >= 0; j--) {
            for (int s = 1; s < (1 << items[i].size()); s++) {
                if (!(s & 1)) { continue; }
                int sum_v = 0, sum_p = 0;
                for (int k = 0; k < items[i].size(); k++) {
                    if (s & (1 << k)) {
                        sum_v += items[i][k][0];
                        sum_p += items[i][k][0] * items[i][k][1];
                    }
                }
                if (j >= sum_v) { dp[j] = std::max(dp[j], dp[j - sum_v] + sum_p); }
            }
        }
    }
    std::cout << dp[n] << std::endl;
    return 0;
}
