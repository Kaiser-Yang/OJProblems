// problem statement: https://www.luogu.com.cn/problem/P2602

#include <array>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>

using i64 = int64_t;
using u64 = uint64_t;

struct node {
    bool vis{};
    u64 total{};
    std::array<u64, 10> cnt{};
};

constexpr int MAXN = 12;

node dp[MAXN][2][2];

node dfs(int pos, bool limited, bool started, const std::string &s) {
    if (pos == s.size()) { return {true, 1, std::array<u64, 10>{}}; }
    auto &res = dp[pos][limited][started];
    if (res.vis) { return dp[pos][limited][started]; }
    res.vis = true;
    int limit = limited ? s[pos] - '0' : 9;
    for (int digit = 0; digit <= limit; digit++) {
        bool new_limited = limited && (digit == limit);
        bool new_started = started || (digit != 0);
        auto next = dfs(pos + 1, new_limited, new_started, s);
        res.total += next.total;
        for (int k = 0; k < 10; k++) { res.cnt[k] += next.cnt[k]; }
        if (new_started) { res.cnt[digit] += next.total; }
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string a, b;
    std::cin >> a >> b;
    auto res_a = dfs(0, true, false, a);
    memset(dp, 0, sizeof(dp));
    auto res_b = dfs(0, true, false, b);
    for (auto &&ch : a) { res_a.cnt[ch - '0']--; }
    for (int i = 0; i < 10; i++) { std::cout << res_b.cnt[i] - res_a.cnt[i] << " \n"[i == 9]; }
    return 0;
}
