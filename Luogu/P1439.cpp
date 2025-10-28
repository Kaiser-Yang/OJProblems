// problem statement: https://www.luogu.com.cn/problem/P1439

#include <cstdint>
#include <iostream>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n), p(n + 1);
    for (int i = 0; i < n; i++) { std::cin >> a[i]; }
    for (int i = 0; i < n; i++) {
        int b;
        std::cin >> b;
        p[b] = i;
    }
    for (int i = 0; i < n; i++) { a[i] = p[a[i]]; }
    std::vector<int> dp(n + 1);
    int len = 1;
    dp[1] = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > dp[len]) {
            dp[++len] = a[i];
        } else {
            auto idx = std::lower_bound(dp.begin() + 1, dp.begin() + len + 1, a[i]) - dp.begin();
            dp[idx] = a[i];
        }
    }
    std::cout << len << std::endl;
    return 0;
}
