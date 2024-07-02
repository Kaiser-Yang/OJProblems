// problem statement: 

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 50 + 10;
constexpr int MAXM = 9 + 3;

int n, m, ans1 = numeric_limits<int>::max(), ans2;
int number[MAXN * 2], sum[MAXN], dp[MAXN][MAXM][2];

int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> number[i];
		number[i + n] = number[i];
	}
	for (int i = 1; i <= n; i++) {
		memset(dp, 0, sizeof(dp));
		memset(sum, 0, sizeof(sum));
		for (int j = 1; j <= n; j++) { sum[j] = sum[j - 1] + number[i + j - 1]; }
		for (int j = 1; j <= n; j++) {
			dp[j][1][0] = dp[j][1][1] = (sum[j] % 10 + 10) % 10;
		}
		for (int j = 2; j <= n; j++) {
			for (int k = 2; k <= min(m, j); k++) {
				dp[j][k][0] = numeric_limits<int>::max();
				dp[j][k][1] = 0;
				for (int kk = k - 1; kk < j; kk++) {
					dp[j][k][0] = min(dp[j][k][0], dp[kk][k - 1][0] * (((sum[j] - sum[kk]) % 10 + 10) % 10));
					dp[j][k][1] = max(dp[j][k][1], dp[kk][k - 1][1] * (((sum[j] - sum[kk]) % 10 + 10) % 10));
				}
			}
		}
		ans1 = min(ans1, dp[n][m][0]);
		ans2 = max(ans2, dp[n][m][1]);
	}
	cout << ans1 << endl << ans2 << endl;
	return 0;
}
