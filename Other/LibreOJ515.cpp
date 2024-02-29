// problem statement: https://loj.ac/p/515

#include <bits/stdc++.h>

constexpr int MAXN = 110;

using namespace std;

int n;
int a[MAXN], b[MAXN];
bitset<MAXN * MAXN * MAXN> dp[MAXN];

int main()
{
	ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) { cin >> a[i] >> b[i]; }
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = a[i]; j <= b[i]; j++) {
            dp[i] |= (dp[i - 1] << (j * j));
        }
    }
    cout << dp[n].count() << "\n";
	return 0;
}
