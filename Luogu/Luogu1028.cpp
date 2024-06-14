// problem statement: 

#include <bits/stdc++.h>

const int MAXN = 1010;

using namespace std;

int n;
int dp[MAXN];

int main()
{
	cin >> n;
	dp[0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= i / 2; j++) {
			dp[i] += dp[j];
		}
	}
	cout << dp[n] << endl;
	return 0;
}