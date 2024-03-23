// problem statement: https://leetcode.cn/problems/egg-drop-with-2-eggs-and-n-floors/description/

class Solution {
private:
    static constexpr int MAXN = 1e3 + 10;
    int dp[MAXN][3];
public:
    int twoEggDrop(int n) {
        dp[0][1] = dp[0][2] = 0;
        for (int i = 1; i <= n; i++) {
            dp[i][1] = dp[i][2] = i;
            for (int j = 1; j < i; j++) {
                dp[i][2] = min(dp[i][2], max(dp[j - 1][1], dp[i - j][2]) + 1);
            }
        }
        return dp[n][2];
    }
};
