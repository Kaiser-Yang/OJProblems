// problem statement: https://leetcode.cn/problems/super-egg-drop/description/

class Solution {
private:
    static constexpr int MAXN = 1e4 + 10;
    static constexpr int MAXK = 110;
    int dp[MAXN][MAXK];
public:
    int superEggDrop(int k, int n) {
        memset(dp, 0x3f, sizeof(dp));
        for (int j = 0; j <= k; j++) { dp[0][j] = 0; }
        for (int j = 1; j <= k; j++) {
            int ii = 0;
            for (int i = 1; i <= n; i++) {
                while(ii + 1 < i &&
                      max(dp[ii - 1][j - 1], dp[i - ii][j]) >
                      max(dp[ii][j - 1], dp[i - ii - 1][j])) { ii++; }
                dp[i][j] = min(i, max(dp[ii - 1][j - 1], dp[i - ii][j]) + 1);
            }
        }
        return dp[n][k];
    }
};