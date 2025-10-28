// problem statement: https://www.luogu.com.cn/problem/T386911

#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) { std::cin >> a[i]; }
    std::reverse(a.begin(), a.end());
    for (int i = 0; i < n; i++) { a[i] = -a[i]; }
    std::vector<int> dp(n + 1), g(n);
    int len = 1;
    dp[1] = a[0];
    g[0] = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] > dp[len]) {
            dp[++len] = a[i];
            g[i] = len;
        } else {
            auto idx = std::lower_bound(dp.begin() + 1, dp.begin() + len + 1, a[i]) - dp.begin();
            dp[idx] = a[i];
            g[i] = idx;
        }
    }
    std::vector<int> ans(len, std::numeric_limits<int>::max());
    for (int i = n - 1; i >= 0; i--) {
        int cur = len - g[i];
        if (cur == 0 || -a[i] > ans[cur - 1]) { ans[cur] = std::min(ans[cur], -a[i]); }
    }
    for (int i = 0; i < len; i++) { std::cout << ans[i] << " \n"[i == len - 1]; }
    return 0;
}
