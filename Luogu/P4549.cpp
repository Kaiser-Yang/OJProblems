// problem statement: https://www.luogu.com.cn/problem/P4549

#include <cstdint>
#include <iostream>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

template <typename T>
static T gcd(T a, T b) {
    return b == 0 ? a : gcd(b, a % b);
}

template <typename T>
static T gcd(const std::vector<T> &a) {
    T res = 0;
    for (auto &&x : a) { res = gcd(res, x); }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i] = std::abs(a[i]);
    }
    std::cout << gcd(a) << std::endl;
    return 0;
}
