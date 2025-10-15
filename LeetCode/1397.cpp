// problem statement: https://leetcode.cn/problems/find-all-good-strings/
#include <cassert>
#include <functional>
#include <string>
#include <vector>

class Solution {
public:
    int findGoodStrings(int n, std::string s1, std::string s2, std::string evil) {
        constexpr int mod = 1e9 + 7;
        auto &&next = get_next(evil);
        std::function<int(const std::string &)> work = [&](const std::string &s) {
            std::vector<std::vector<std::array<int, 2>>> dp(
                n + 1, std::vector<std::array<int, 2>>(evil.size() + 1, {-1, -1}));
            std::function<int(int, int, bool)> dfs = [&](int i, int j, bool k) {
                if (dp[i][j][k] != -1) { return dp[i][j][k]; }
                if (j == evil.size()) { return dp[i][j][k] = 0; }
                if (i == n) { return dp[i][j][k] = 1; }
                auto &res = dp[i][j][k] = 0;
                auto up = k ? s[i] : 'z';
                for (char c = 'a'; c <= up; c++) {
                    int nj = j;
                    while (nj >= 0 && c != evil[nj]) { nj = next[nj]; }
                    nj++;
                    res = (res + dfs(i + 1, nj, k && (c == up))) % mod;
                }
                return res;
            };
            return dfs(0, 0, 1);
        };
        int ans = work(s2) - work(s1);
        ans = (ans % mod + mod) % mod;
        if (kmp(s1, evil).size() == 0) { ans = (ans + 1) % mod; }
        return ans;
    }

private:
    template <typename T>
    std::vector<int> get_next(const T &word) {
        assert(word.size() > 0);
        std::vector<int> next(word.size() + 1);
        next[0] = -1;
        next[1] = 0;
        int i = 1, j = 0;
        while (i < word.size()) {
            if (word[i] == word[j]) {
                i++;
                j++;
                next[i] = j;
            } else if (j == 0) {
                i++;
            } else {
                j = next[j];
            }
        }
        return next;
    }

    // Return the match position, zero-indexed
    template <typename T>
    std::vector<int> kmp(const T &text, const T &word) {
        std::vector<int> res;
        auto &&next = get_next(word);
        int i = 0, j = 0;
        while (i < text.size()) {
            if (text[i] == word[j]) {
                i++;
                j++;
                if (j == word.size()) {
                    res.emplace_back(i - j);
                    j = next[j];
                }
            } else if (j == 0) {
                i++;
            } else {
                j = next[j];
            }
        }
        return res;
    }
};
