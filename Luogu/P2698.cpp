// problem statement: https://www.luogu.com.cn/problem/P2698

#include <array>
#include <cstdint>
#include <iostream>
#include <deque>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, D;
    std::cin >> N >> D;
    std::vector<std::array<int, 2>> items(N);
    for (int i = 0; i < N; i++) { std::cin >> items[i][0] >> items[i][1]; }
    std::sort(items.begin(), items.end());
    int l = 0, r = 0, ans = -1;
    std::deque<int> q1, q2;
    while (l < N) {
        while (r < N && (r - l == 0 || items[q2.front()][1] - items[q1.front()][1] < D)) {
            while (!q1.empty() && items[q1.back()][1] >= items[r][1]) { q1.pop_back(); }
            q1.push_back(r);
            while (!q2.empty() && items[q2.back()][1] <= items[r][1]) { q2.pop_back(); }
            q2.push_back(r);
            r++;
        }
        if (r - l > 0 && items[q2.front()][1] - items[q1.front()][1] >= D &&
            (ans == -1 || ans > items[r - 1][0] - items[l][0])) {
            ans = items[r - 1][0] - items[l][0];
        }
        l++;
        while (!q1.empty() && q1.front() < l) { q1.pop_front(); }
        while (!q2.empty() && q2.front() < l) { q2.pop_front(); }
    }
    std::cout << ans << std::endl;
    return 0;
}
