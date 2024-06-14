// problem statement: 

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 55;
constexpr int MAXM = 55;

int n, m, maxN, maxM;
int height[MAXN][MAXM];
char ans[MAXN * 10][MAXM * 10];
char cuboid[6][10] {
	"  +---+",
	" /   /|",
	"+---+ |",
	"|   | +",
	"|   |/",
	"+---+",
};

int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> height[i][j];
		}
	}
	memset(ans, '.', sizeof(ans));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int h = 1; h <= height[i][j]; h++) {
				int x = (n - i) * 2 + 1 + 3 * (h - 1);
				int y = (n - i) * 2 + 1 + 4 * (j - 1);
				for (int a = 5; a >= 0; a--) {
					for (int b = 0; b < strlen(cuboid[a]); b++) {
						if ((a == 0 && b < 2) || (a == 1 && b < 1)) { continue; }
						ans[x + 5 - a][y + b] = cuboid[a][b];
						maxN = max(maxN, 5 - a + x);
						maxM = max(maxM, y + b);
					}
				}
			}
		}
	}
	for (int i = maxN; i >= 1; i--) {
		for (int j = 1; j <= maxM; j++) {
			cout << ans[i][j];
		}
		cout << endl;
	}
	return 0;
}
