#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, W;
    std::cin >> n >> W;
    std::vector<int> w(n), t(n);
    double left = 0, right = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> w[i] >> t[i];
        right += t[i];
    }
    auto check = [&](double x) {
        std::vector<double> v(n);
        for (int i = 0; i < n; i++) { v[i] = t[i] - x * w[i]; }
        std::vector<double> dp(W + 1, std::numeric_limits<double>::lowest());
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            auto tmp = std::vector<double>(W + 1, std::numeric_limits<double>::lowest());
            for (int j = 0; j <= W; j++) {
                if (dp[j] == std::numeric_limits<double>::lowest()) { continue; }
                if (j + w[i] >= W) {
                    tmp[W] = std::max(tmp[W], dp[j] + v[i]);
                } else {
                    tmp[j + w[i]] = std::max(tmp[j + w[i]], dp[j] + v[i]);
                }
                tmp[j] = std::max(tmp[j], dp[j]);
            }
            dp = std::move(tmp);
        }
        return dp[W] >= 0;
    };
    while (right - left >= 1e-5) {
        double mid = (left + right) / 2;
        if (check(mid)) {
            ans = mid;
            left = mid;
        } else {
            right = mid;
        }
    }
    ans += 1e-5;
    std::cout << (int)(ans * 1000) << std::endl;
    return 0;
}
