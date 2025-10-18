// problem statement: https://www.luogu.com.cn/problem/P3397

#include <cstdint>
#include <iostream>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> a(n, std::vector<int>(n, 0));
    auto update = [&](int x1, int y1, int x2, int y2) {
        a[x1][y1] += 1;
        if (x2 < n && y2 < n) { a[x2][y2] += 1; }
        if (x2 < n) { a[x2][y1] -= 1; }
        if (y2 < n) { a[x1][y2] -= 1; }
    };
    for (int i = 0; i < m; i++) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        x1--;
        y1--;
        update(x1, y1, x2, y2);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i - 1 >= 0) { a[i][j] += a[i - 1][j]; }
            if (j - 1 >= 0) { a[i][j] += a[i][j - 1]; }
            if (i - 1 >= 0 && j - 1 >= 0) { a[i][j] -= a[i - 1][j - 1]; }
            std::cout << a[i][j] << (j == n - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
