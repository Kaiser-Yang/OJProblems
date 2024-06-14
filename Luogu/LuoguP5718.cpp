// problem statement: https://www.luogu.com.cn/problem/P5718

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 110;

int n, ans = numeric_limits<int>::max();
int a[MAXN];

int main()
{
	ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) { cin >> a[i]; }
    for_each(a, a + n, [](auto val){ ans = min(ans, val); });
    cout << ans << endl;
	return 0;
}
