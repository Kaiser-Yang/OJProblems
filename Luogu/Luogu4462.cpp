// problem statement: https://www.luogu.com.cn/problem/P4462

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<int> a(n), pre(n + 1), suf(n);
    for (int i = 0; i < n; i++) { std::cin >> a[i]; }
    for (int i = 0; i < n; i++) { pre[i + 1] = pre[i] ^ a[i]; }
    for (int i = n - 1; i >= 0; i--) { suf[i] = (i == n - 1 ? 0 : suf[i + 1]) ^ a[i]; }
    std::vector<std::array<int, 3>> query(m);
    for (int i = 0; i < m; i++) {
        int l, r;
        std::cin >> l >> r;
        l--;
        query[i] = {l, r, i};
    }
    const int block_size = sqrt(n);
    std::sort(query.begin(), query.end(), [&block_size](const auto &x, const auto &y) {
        auto blk1 = x[0] / block_size, blk2 = y[0] / block_size;
        if (blk1 != blk2) {
            return blk1 < blk2;
        } else if (blk1 & 1) {
            return x[1] > y[1];
        } else {
            return x[1] < y[1];
        }
    });
    std::vector<std::array<long long, 2>> ans(m);
    std::unordered_map<int, int> cnt1, cnt2;
    int current_l = 0, current_r = 0;
    long long current_cnt = 0;
    auto add = [&](int i) {
        cnt1[pre[i + 1]]++;
        cnt2[suf[i]]++;
        if (i == current_l) {
            current_cnt += cnt1[pre[i] ^ k];
        } else {
            current_cnt += cnt2[(i + 1 == n ? 0 : suf[i + 1]) ^ k];
        }
    };
    auto remove = [&](int i) {
        if (i == current_r) {
            current_cnt -= cnt2[(i + 1 == n ? 0 : suf[i + 1]) ^ k];
        } else {
            current_cnt -= cnt1[pre[i] ^ k];
        }
        cnt2[suf[i]]--;
        cnt1[pre[i + 1]]--;
    };
    for (auto &&[l, r, i] : query) {
        while (current_l > l) { add(--current_l); }
        while (current_r < r) { add(current_r++); }
        while (current_l < l) { remove(current_l++); }
        while (current_r > r) { remove(--current_r); }
        ans[i] = {i, current_cnt};
    }

    sort(ans.begin(), ans.end());
    for (auto &&[_, cnt] : ans) { std::cout << cnt << '\n'; }
    return 0;
}
