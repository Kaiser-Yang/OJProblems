// problem statement: https://www.luogu.com.cn/problem/P2148

#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T;
    std::cin >> T;
    while (T--) {
        int n;
        std::cin >> n;
        int nim = 0;
        for (int i = 0; i < n / 2; i++) {
            int a, b;
            std::cin >> a >> b;
            a--;
            b--;
            int tmp = a | b;
            int cnt = 0;
            while (tmp & 1) {
                cnt++;
                tmp >>= 1;
            }
            nim ^= cnt;
        }
        std::cout << (nim ? "YES\n" : "NO\n");
    }
    return 0;
}
