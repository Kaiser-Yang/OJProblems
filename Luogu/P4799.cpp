// problem statement: https://www.luogu.com.cn/problem/P4799

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N;
    i64 M;
    std::cin >> N >> M;
    std::vector<i64> a(N);
    for (int i = 0; i < N; i++) { std::cin >> a[i]; }
    auto solve = [&](int start, int len) {
        std::vector<i64> res;
        for (int st = 0; st < (1 << len); st++) {
            i64 sum = 0;
            for (int i = 0; i < len; i++) {
                if (st & (1 << i)) { sum += a[start + i]; }
            }
            res.push_back(sum);
        }
        return res;
    };
    auto left = solve(0, N / 2), right = solve(N / 2, N - N / 2);
    std::sort(right.begin(), right.end());
    i64 ans = 0;
    for (auto &&left_sum : left) {
        if (left_sum > M) { continue; }
        i64 target = M - left_sum;
        ans += std::upper_bound(right.begin(), right.end(), target) - right.begin();
    }
    std::cout << ans << std::endl;
    return 0;
}
