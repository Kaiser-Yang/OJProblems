// problem statement: 

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXM = 101;
constexpr int MAX_COST_TIME = 101;

int T, M;
int costTime[MAXM], value[MAXM], dp[MAXM][MAXM * MAX_COST_TIME];

int main()
{
	cin >> T >> M;
	for (int i = 1; i <= M; i++) {
		cin >> costTime[i] >> value[i];
	}
	for (int i = 1; i <= M; i++) {
		for (int j = 0; j <= T; j++) {
			dp[i][j] = dp[i - 1][j];
			if (j >= costTime[i]) {
				dp[i][j] = max(dp[i][j], dp[i - 1][j - costTime[i]] + value[i]);
			}
		}
	}
	cout << dp[M][T] << endl;
	return 0;
}