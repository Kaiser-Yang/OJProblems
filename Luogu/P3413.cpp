// problem statement: https://www.luogu.com.cn/problem/P3413

#include <cstdint>
#include <cstring>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;

constexpr int MOD = 1000000007;
constexpr int MAXN = 1000;

struct node {
    bool vis{};
    int palindrome{};
    int non_palindrome{};
} dp[MAXN][11][11][2][2][2];

node dfs(int pos,
         int last,
         int current,
         bool palindrome,
         bool limited,
         bool started,
         const std::string &s) {
    if (pos == s.size()) { return {true, 0, started}; }
    auto limit = (limited ? s[pos] - '0' : 9);
    auto &res = dp[pos][last][current][palindrome][limited][started];
    if (res.vis) { return res; }
    res.vis = true;
    for (int j = 0; j <= limit; j++) {
        auto new_limited = limited && (j == s[pos] - '0');
        auto new_started = started || (j != 0);
        auto new_palindrome = palindrome || j == current || j == last;
        auto new_last = new_started ? current : 10;
        auto new_current = new_started ? j : 10;
        auto child =
            dfs(pos + 1, new_last, new_current, new_palindrome, new_limited, new_started, s);
        res.palindrome = (res.palindrome + child.palindrome) % MOD;
        if (new_palindrome) {
            res.palindrome = (res.palindrome + child.non_palindrome) % MOD;
        } else {
            res.non_palindrome = (res.non_palindrome + child.non_palindrome) % MOD;
        }
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string a, b;
    std::cin >> a >> b;
    auto res_a = dfs(0, 10, 10, false, true, false, a);
    memset(dp, 0, sizeof(dp));
    auto res_b = dfs(0, 10, 10, false, true, false, b);
    auto ans = (res_b.palindrome - res_a.palindrome + MOD) % MOD;
    for (int i = 1; i < a.size(); i++) {
        if (a[i] == a[i - 1] || i - 2 >= 0 && a[i] == a[i - 2]) {
            ans++;
            break;
        }
    }
    std::cout << ans << "\n";
    return 0;
}
