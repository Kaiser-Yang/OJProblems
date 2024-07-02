// problem statement: 

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 3e5 + 10;

int n, k;
long long ans;
long long a[MAXN];
int l[MAXN], r[MAXN];
bool canPlanted[MAXN];
priority_queue<pair<long long, int>> q;

int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		q.push(make_pair(a[i], i));
		l[i] = i - 1;
		r[i] = i + 1;
	}
	l[n + 1] = n;
	r[0] = 1;
	memset(canPlanted, 1, sizeof(canPlanted));
	for (int i = 0; i < k; i++) {
		while (!q.empty() && !canPlanted[q.top().second]) { q.pop(); }
		if (q.empty()) { break; }
		auto top = q.top();
		q.pop();
		if (top.first <= 0) { break; }
		ans += top.first;
		top.first = a[top.second] = a[l[top.second]] + a[r[top.second]] - a[top.second];
		canPlanted[l[top.second]] = canPlanted[r[top.second]] = false;
		l[top.second] = l[l[top.second]];
		r[top.second] = r[r[top.second]];
		l[r[top.second]] = top.second;
		r[l[top.second]] = top.second;
		q.push(top);
	}
	cout << ans << endl;
	return 0;
}