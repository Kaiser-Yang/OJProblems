// problem statement: https://www.luogu.com.cn/problem/P6033

#include <array>
#include <cstdint>
#include <iostream>
#include <queue>

using i64 = int64_t;
using u64 = uint64_t;

std::array<int, 100001> cnt{};

template <typename T>
void read(T &x) {
    x = 0;
    bool neg = false;
    char ch = 0;
    do {
        ch = getchar();
        if (ch == '-') { neg = true; }
    } while (!isdigit(ch));
    do {
        x = x * 10 + ch - '0';
        ch = getchar();
    } while (isdigit(ch));
    if (neg) { x = -x; }
}

int main() {
    int n;
    read(n);
    for (int i = 0; i < n; i++) {
        int a;
        read(a);
        cnt[a]++;
    }
    std::queue<int> a;
    for (int i = 0; i <= 1e5; i++) {
        while (cnt[i]) {
            cnt[i]--;
            a.push(i);
        }
    }
    i64 ans = 0;
    std::queue<i64> b;
    while (a.size() + b.size() > 1) {
        i64 x, y;
        if (a.empty()) {
            x = b.front();
            b.pop();
            y = b.front();
            b.pop();
        } else if (b.empty()) {
            x = a.front();
            a.pop();
            y = a.front();
            a.pop();
        } else {
            if (b.front() < a.front()) {
                x = b.front();
                b.pop();
            } else {
                x = a.front();
                a.pop();
            }
            if (a.empty() || (!b.empty() && b.front() < a.front())) {
                y = b.front();
                b.pop();
            } else {
                y = a.front();
                a.pop();
            }
        }
        ans += x + y;
        b.push(x + y);
    }
    std::cout << ans << std::endl;
    return 0;
}
