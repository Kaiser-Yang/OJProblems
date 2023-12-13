#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1010;

string s;
int dp[MAXN][MAXN];

int main()
{
	ios::sync_with_stdio(false);
	cin >> s;
	int n = s.length();
	memset(dp, 0x3f, sizeof(dp));
	for (int i = 0; i < n; i++) { dp[i][i] = 0; }
	for (int i = 0; i < n - 1; i++) { dp[i][i + 1] = (s[i] == s[i + 1] ? 0 : 1); }
	for (int len = 3; len <= n; len++) {
		for (int l = 0; l + len - 1 < n; l++) {
			int r = l + len - 1;
			if (s[l] == s[r]) { dp[l][r] = dp[l + 1][r - 1]; }
			dp[l][r] = min(dp[l][r], dp[l + 1][r] + 1);
			dp[l][r] = min(dp[l][r], dp[l][r - 1] + 1);
		}
	}
	cout << dp[0][n - 1] << endl;
	return 0;
}