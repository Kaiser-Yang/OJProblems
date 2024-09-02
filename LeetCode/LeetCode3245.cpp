// problem statement: https://leetcode.cn/problems/alternating-groups-iii

#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
    class binary_indexed_tree {
    public:
        binary_indexed_tree(int n) : n(n), c(n + 1) {}
        void add(int x, int v) {
            for (int i = x; i <= n; i += lowbit(i)) { c[i] += v; }
        }
        int query(int x) {
            int res = 0;
            for (int i = x; i; i -= lowbit(i)) { res += c[i]; }
            return res;
        }

    private:
        int lowbit(int x) { return x & -x; }
        int n;
        vector<int> c;
    };

    template <class T>
    void check_zero_update(int n, T &t) {
        if (t == 0) { t = n; }
    }

    template <class T0, class... LEN_ARGS>
    void check_zero_update(int n, T0 &t0, LEN_ARGS &...lens) {
        if (t0 == 0) { t0 = n; }
        check_zero_update(n, lens...);
    }

public:
    vector<int> numberOfAlternatingGroups(vector<int> &colors, vector<vector<int>> &queries) {
        int n = colors.size();
        binary_indexed_tree t_sum(n), t_cnt(n);
        vector<int> ans;
        set<int> s;
        auto update = [&](int pre, int now, int nex, bool is_insert) {
            int multiplier = 0;
            if (is_insert) {
                multiplier = 1;
            } else {
                multiplier = -1;
            }
            // seperate the old length into two parts
            int old_len = (nex - pre + n) % n;
            int len1 = (now - pre + n) % n;
            int len2 = (nex - now + n) % n;
            check_zero_update(n, old_len, len1, len2);
            t_cnt.add(old_len, -multiplier);
            t_cnt.add(len1, multiplier);
            t_cnt.add(len2, multiplier);
            t_sum.add(old_len, -multiplier * old_len);
            t_sum.add(len1, multiplier * len1);
            t_sum.add(len2, multiplier * len2);
        };
        auto insert_end_pos = [&](int now) {
            auto iter = s.insert(now).first;
            if (s.size() == 1) {
                // insert the first the end pos means there is only one group whose length is n
                t_sum.add(n, n);
                t_cnt.add(n, 1);
            } else {
                int pre = (iter == s.begin() ? *prev(s.end()) : *prev(iter));
                int nex = (next(iter) == s.end() ? *s.begin() : *next(iter));
                update(pre, now, nex, true);
            }
        };
        auto delete_end_pos = [&](int now) {
            // iter points to the next one of the deleted one
            auto iter = s.erase(s.find(now));
            if (s.empty()) {
                t_sum.add(n, -n);
                t_cnt.add(n, -1);
            } else {
                int pre = (iter == s.begin() ? *prev(s.end()) : *prev(iter));
                int nex = (iter == s.end() ? *s.begin() : *iter);
                update(pre, now, nex, false);
            }
        };
        for (int i = 0; i < n; i++) {
            if (colors[i] == colors[(i + 1) % n]) { insert_end_pos(i); }
        }
        for (auto &&item : queries) {
            int op_code = item[0], x = item[1];
            // query
            if (op_code == 1) {
                if (s.empty()) {
                    ans.push_back(n);
                    continue;
                }
                int sum = t_sum.query(n) - t_sum.query(x - 1);
                int cnt = t_cnt.query(n) - t_cnt.query(x - 1);
                ans.push_back(sum - (x - 1) * cnt);
            } else {
                int now = x, pre = (x - 1 + n) % n, nex = (x + 1) % n, new_col = item[2];
                if (colors[pre] == colors[now]) { delete_end_pos(pre); }
                if (colors[now] == colors[nex]) { delete_end_pos(now); }
                colors[now] = new_col;
                if (colors[pre] == colors[now]) { insert_end_pos(pre); }
                if (colors[now] == colors[nex]) { insert_end_pos(now); }
            }
        }
        return ans;
    }
};

int main() {
    vector<int> colors = {0, 1, 1, 0, 1};
    vector<vector<int>> queries = {{2, 1, 0}, {1, 4}};
    Solution().numberOfAlternatingGroups(colors, queries);
    return 0;
}
