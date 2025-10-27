// problem statement: http://poj.org/problem?id=1742

#include <cmath>
#include <cstring>
#include <iostream>

const int MAX_N = 100, MAX_M = 100000;

int a[MAX_N], c[MAX_N], dp[MAX_M + 1];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m;
    while (std::cin >> n >> m) {
        if (n == 0 && m == 0) { break; }
        for (int i = 0; i < n; i++) { std::cin >> a[i]; }
        for (int i = 0; i < n; i++) { std::cin >> c[i]; }
        memset(dp, 0, sizeof(int) * (m + 1));
        dp[0] = 1;
        for (int i = 0; i < n; i++) {
            int tmp = c[i];
            for (int x = 1; tmp > 0; tmp -= x, x <<= 1) {
                x = std::min(x, tmp);
                int w = a[i] * x;
                for (int j = m; j >= w; j--) { dp[j] |= dp[j - w]; }
            }
        }
        int sum = 0;
        for (int i = 1; i <= m; i++) { sum += dp[i]; }
        std::cout << sum << "\n";
    }
    return 0;
}
