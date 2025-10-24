// problem statement: https://www.luogu.com.cn/problem/P1833

#include <array>
#include <cstdint>
#include <deque>
#include <iostream>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int sh, sm, eh, em;
    char _;
    std::cin >> sh >> _ >> sm >> eh >> _ >> em;
    int t = (eh - sh) * 60 + (em - sm);
    int n;
    std::cin >> n;
    std::vector<std::array<int, 3>> a(n);  // cost, value, count
    for (int i = 0; i < n; i++) { std::cin >> a[i][0] >> a[i][1] >> a[i][2]; }
    std::vector<int> dp(t + 1);
    for (int i = 0; i < n; i++) {
        if (a[i][2] == 0) {
            for (int j = a[i][0]; j <= t; j++) {
                dp[j] = std::max(dp[j], dp[j - a[i][0]] + a[i][1]);
            }
            continue;
        }
        std::vector<int> ndp(t + 1);
        for (int r = 0; r < a[i][0]; r++) {
            std::deque<int> q;
            for (int j = r, k = 0; j <= t; j += a[i][0], k++) {
                while (!q.empty() && q.front() < k - a[i][2]) { q.pop_front(); }
                while (!q.empty() &&
                       dp[q.back() * a[i][0] + r] - q.back() * a[i][1] <= dp[j] - k * a[i][1]) {
                    q.pop_back();
                }
                q.push_back(k);
                ndp[j] = dp[q.front() * a[i][0] + r] - q.front() * a[i][1] + k * a[i][1];
            }
        }
        dp = std::move(ndp);
    }
    std::cout << dp[t] << '\n';
    return 0;
}
