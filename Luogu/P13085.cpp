// problem statement: https://www.luogu.com.cn/problem/P13085

#include <array>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

template <typename T>
using mat2_2 = std::array<std::array<T, 2>, 2>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string a, b;
    std::cin >> a >> b;
    auto work = [&](const std::string &s) {
        int n = s.size();
        // dp[i][j][k]:
        // i: [0, i]
        // j: last digit is j
        // k: 0: limited, 1: not limited
        // l: 0: not started, 1: started
        using mat2_2 = ::mat2_2<i64>;
        std::vector<std::vector<mat2_2>> dp(n, std::vector<mat2_2>(10));
        for (int j = 0; j < 10; j++) {
            if (j > s[0] - '0') { break; }
            dp[0][j][j < s[0] - '0'][j != 0] = 1;
        }
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < 10; j++) {
                if (j == 0) { dp[i][j][1][0] = dp[i - 1][0][1][0]; }
                if (j == s[i] - '0' && std::abs(j - (s[i - 1] - '0')) >= 2) {
                    dp[i][j][0][1] = dp[i - 1][s[i - 1] - '0'][0][1];
                }
                if (j != 0) { dp[i][j][1][1] = dp[i - 1][0][1][0]; }
                if (j < s[i] - '0' && std::abs(j - (s[i - 1] - '0')) >= 2) {
                    dp[i][j][1][1] += dp[i - 1][s[i - 1] - '0'][0][1];
                }
                for (int jj = 0; jj < 10; jj++) {
                    if (std::abs(j - jj) < 2) { continue; }
                    dp[i][j][1][1] += dp[i - 1][jj][1][1];
                }
            }
        }
        i64 ans = 0;
        for (int j = 0; j < 10; j++) { ans += dp[n - 1][j][0][1] + dp[n - 1][j][1][1]; }
        return ans;
    };
    auto ans = work(b) - work(a);
    auto is_windy = true;
    for (int i = 1; i < a.size(); i++) {
        if (std::abs(a[i] - a[i - 1]) < 2) {
            is_windy = false;
            break;
        }
    }
    if (is_windy) { ans++; }
    std::cout << ans << std::endl;
    return 0;
}
