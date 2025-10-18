// problem statement: https://www.luogu.com.cn/problem/P3067

#include <cmath>
#include <cstdint>
#include <functional>
#include <iostream>
#include <numeric>
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
    std::vector<bool> ok(1 << n);
    std::unordered_map<int, std::vector<int>> left;
    std::function<void(int, int, int, int, int)> dfs =
        [&](int start, int len, int cur, int cur_depth, int mask) {
            if (cur_depth == len) {
                if (start == 0) {
                    left[cur].push_back(mask);
                } else if (left.count(-cur)) {
                    for (auto &&m : left[-cur]) { ok[(m << (n - n / 2)) | mask] = true; }
                }
                return;
            }
            dfs(start, len, cur + a[start + cur_depth], cur_depth + 1, mask | (1 << cur_depth));
            dfs(start, len, cur, cur_depth + 1, mask);
            dfs(start, len, cur - a[start + cur_depth], cur_depth + 1, mask | (1 << cur_depth));
        };
    dfs(0, n / 2, 0, 0, 0);
    dfs(n / 2, n - n / 2, 0, 0, 0);
    std::cout << std::accumulate(ok.begin() + 1, ok.end(), 0) << '\n';
    return 0;
}
