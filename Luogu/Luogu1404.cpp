// problem statement: 

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;

int n, m;
int a[MAXN], cnt[MAXN];
double dp[MAXN];
long long ans;

int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) { cin >> a[i]; a[i] += a[i - 1]; }
	dp[m] = 1.0 * a[m] / m;
	cnt[m] = m;
	ans = (long long)(dp[m] * 1000);
	for (int i = m + 1; i <= n; i++) {
		dp[i] = 1.0 * (a[i] - a[i - m]) / m;
		cnt[i] = m;
		if ((dp[i - 1] * cnt[i - 1] + a[i] - a[i - 1]) / (cnt[i - 1] + 1) > dp[i]) {
			cnt[i] = cnt[i - 1] + 1;
			dp[i] = (dp[i - 1] * cnt[i - 1] + a[i] - a[i - 1]) / cnt[i];
		}
		ans = max(ans, (long long)(dp[i] * 1000));
	}
	cout << ans << endl;
	return 0;
}
