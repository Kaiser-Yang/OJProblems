// problem statement: https://www.luogu.com.cn/problem/P3709

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) { std::cin >> a[i]; }
    std::unordered_map<int, int> id;
    for (int i = 0; i < n; i++) {
        if (id.count(a[i]) == 0) { id[a[i]] = id.size(); }
        a[i] = id[a[i]];
    }
    std::vector<std::array<int, 3>> query;
    for (int i = 0; i < m; i++) {
        int l, r;
        std::cin >> l >> r;
        l--;
        query.push_back({l, r, i});
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
    int current_l = 0, current_r = 0, max_cnt = 0;
    std::vector<int> cnt(n), freq(n + 1);
    auto add = [&](int i) {
        freq[cnt[a[i]]]--;
        cnt[a[i]]++;
        freq[cnt[a[i]]]++;
        if (cnt[a[i]] > max_cnt) { max_cnt = cnt[a[i]]; }
    };
    auto remove = [&](int i) {
        freq[cnt[a[i]]]--;
        cnt[a[i]]--;
        freq[cnt[a[i]]]++;
        if (freq[max_cnt] == 0) { max_cnt--; }
    };
    std::vector<std::array<int, 2>> ans;
    for (auto &&[l, r, i] : query) {
        while (current_l > l) { add(--current_l); }
        while (current_r < r) { add(current_r++); }
        while (current_l < l) { remove(current_l++); }
        while (current_r > r) { remove(--current_r); }
        ans.push_back({i, max_cnt});
    }
    sort(ans.begin(), ans.end());
    for (auto &&[_, v] : ans) { std::cout << -v << "\n"; }
    return 0;
}
