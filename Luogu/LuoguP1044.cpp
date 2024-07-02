// problem statement: 

#include <bits/stdc++.h>

using namespace std;

int n;

int main()
{
	ios::sync_with_stdio(false);
	cin >> n;
	long long ans = 1;
	for (int i = 1; i <= n; i++) {
		ans = ans * (2 * n - i + 1) / i;
	}
	ans /= n + 1;
	cout << ans << endl;
	return 0;
}
