// problem statement: 

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1510;
constexpr int MAXM = 1510;

int N, M, ans;
int grid[MAXN][MAXM];
int l[MAXN][MAXM], r[MAXN][MAXM], u[MAXN][MAXM];

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> grid[i][j];
		}
	}
	for (int i = 1; i <= N; i++) {
		l[i][1] = 1;
		for (int j = 2; j <= M; j++) {
			if (grid[i][j] != grid[i][j - 1]) {
				l[i][j] = l[i][j - 1];
			} else {
				l[i][j] = j;
			}
		}
	}
	for (int i = 1; i <= N; i++) {
		r[i][M] = M;
		for (int j = M - 1; j >= 1; j--) {
			if (grid[i][j] != grid[i][j + 1]) {
				r[i][j] = r[i][j + 1];
			} else {
				r[i][j] = j;
			}
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (i > 1 && grid[i][j] != grid[i - 1][j]) {
				u[i][j] = u[i - 1][j];
				l[i][j] = max(l[i][j], l[i - 1][j]);
				r[i][j] = min(r[i][j], r[i - 1][j]);
			} else {
				u[i][j] = i;
			}
			int len1 = i - u[i][j] + 1;
			int len2 = r[i][j] - l[i][j] + 1;
			int len = min(len1, len2);
			ans = max(ans, len);
		}
	}
    cout << ans << endl;
	return 0;
}