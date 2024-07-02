// problem statement: 

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXK = 20;

int n, k, ans;
int value[MAXK], ansValue[MAXK];
vector<int> dp;

int getMaxValue(int depth, int nowValue)
{
	depth++;
	int maxValue = nowValue * n;
	dp.clear();
	dp.resize(maxValue + 1, numeric_limits<int>::max() / 2);
	dp[0] = 0;
	for (int i = 0; i < depth; i++) {
		for (int j = value[i]; j <= maxValue; j++) {
			if (dp[j - value[i]] + 1 <= n) {
				dp[j] = min(dp[j], dp[j - value[i]] + 1);
			}
		}
	}
	for (int i = 1; i <= maxValue; i++) {
		if (dp[i] == numeric_limits<int>::max() / 2) {
			return i - 1;
		}
	}
	return maxValue;
}

void dfs(int depth, int lastValue, int maxValue)
{
	if (depth == k) {
		if (maxValue > ans) {
			ans = maxValue;
			memcpy(ansValue, value, sizeof(int) * k);
		}
		return;
	}
	for (int i = lastValue + 1; i <= maxValue + 1; i++) {
		value[depth] = i;
		int x = getMaxValue(depth, i);
		if (x > maxValue) {
			dfs(depth + 1, i, x);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> k;
	dfs(0, 0, 0);
	for (int i = 0; i < k; i++) { cout << ansValue[i] << " "; }
	cout << endl << "MAX=" << ans << endl;
	return 0;
}
