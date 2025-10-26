// problem statement: https://www.luogu.com.cn/problem/P3205

#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, H;
    std::cin >> N >> H;
    std::vector<int> p(N), c(N);
    for (int i = 0; i < N; i++) { std::cin >> p[i] >> c[i]; }
    auto &&max_p = *std::max_element(p.begin(), p.end());
    std::vector<int> dp(H + max_p + 1, std::numeric_limits<int>::max() / 2);
    dp[0] = 0;
    int ans = std::numeric_limits<int>::max();
    for (int i = 0; i < N; i++) {
        for (int j = p[i]; j <= H + max_p; j++) {
            dp[j] = std::min(dp[j], dp[j - p[i]] + c[i]);
            if (j >= H) { ans = std::min(ans, dp[j]); }
        }
    }
    std::cout << ans << '\n';
    return 0;
}
