// problem statement: https://www.luogu.com.cn/problem/P3185

#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::vector<int> a(n), sg(n);
        for (int i = 0; i < n; i++) { std::cin >> a[i]; }
        for (int i = n - 1; i >= 0; i--) {
            std::unordered_map<int, int> vis;
            for (int j = i + 1; j < n; j++) {
                for (int k = j; k < n; k++) { vis[sg[j] ^ sg[k]] = true; }
            }
            for (int j = 0;; j++) {
                if (!vis[j]) {
                    sg[i] = j;
                    break;
                }
            }
        }
        int nim = 0, cnt = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] & 1) { nim ^= sg[i]; }
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j; k < n; k++) {
                    if ((nim ^ sg[i] ^ sg[j] ^ sg[k]) == 0) {
                        cnt++;
                        if (cnt == 1) { std::cout << i << ' ' << j << ' ' << k << '\n'; }
                    }
                }
            }
        }
        if (!nim) { std::cout << "-1 -1 -1\n"; }
        std::cout << cnt << '\n';
    }
    return 0;
}
