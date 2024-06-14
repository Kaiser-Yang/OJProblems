// problem statement: https://www.luogu.com.cn/problem/P6066
// Tag: having been in my blog

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e4 + 10;
constexpr int MAXM = 5e4 + 10;

int n, m, u, v;
int cnt[MAXN];

stack<int> ans;

vector<int> g[MAXN];

void hierholzer(int u)
{
	for (int &i = cnt[u]; i < g[u].size(); ) {
		int v = g[u][i];
		i++;
		hierholzer(v);
	}
	ans.push(u);
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	hierholzer(1);
	while (!ans.empty()) {
		cout << ans.top() << endl;
		ans.pop();
	}
	return 0;
}
