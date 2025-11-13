// problem statement: https://leetcode.cn/problems/replace-the-substring-for-balanced-string/

#include <string>
#include <vector>

class Solution {
public:
    int get_id(char c) {
        if (c == 'Q') {
            return 0;
        } else if (c == 'W') {
            return 1;
        } else if (c == 'E') {
            return 2;
        } else if (c == 'R') {
            return 3;
        } else {
            return 4;
        }
    }

    int balancedString(std::string s) {
        std::vector<int> cnt(5);
        for (char c : s) { cnt[get_id(c)]++; }
        const int target = s.size() / 4;
        int l = 0, r = 0, ans = s.size();
        while (l < s.size()) {
            while (
                r < s.size() &&
                (std::any_of(cnt.begin(), cnt.end() - 1, [target](int x) { return x > target; }) ||
                 cnt[4] > 0)) {
                cnt[get_id(s[r++])]--;
            }
            if (std::all_of(cnt.begin(), cnt.end() - 1, [target](int x) { return x <= target; }) &&
                cnt[4] == 0) {
                ans = std::min(ans, r - l);
            }
            cnt[get_id(s[l++])]++;
        }
        return ans;
    }
};
