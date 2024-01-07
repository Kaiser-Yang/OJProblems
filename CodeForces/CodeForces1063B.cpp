#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 2010;
constexpr int MAXM = 2010;

int n, m, sx, sy, limitLeft, limitRight, ans;
string grid[MAXN];

int dis[MAXN][MAXM];

enum DIRECTION
{
	UP, DOWN, LEFT, RIGHT, MAX_DIRECTION,
};
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool bound(int x, int y)
{
	return x >= 0 && x < n && y >= 0 && y < m;
}

void bfs()
{
	memset(dis, 0x3f, sizeof(dis));
	using Node = pair<int, int>;
	deque<Node> q;
	q.push_front({sx, sy});
	dis[sx][sy] = 0;
	while (!q.empty()) {
		auto front = q.front();
		q.pop_front();
		int x = front.first, y = front.second;
		for (int i = 0; i < MAX_DIRECTION; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (bound(nx, ny) && grid[nx][ny] != '*') {
				if (i == LEFT && dis[nx][ny] > dis[x][y] + 1) {
					dis[nx][ny] = dis[x][y] + 1;
					q.push_back({nx, ny});
				} else if (i != LEFT && dis[nx][ny] > dis[x][y]) {
					dis[nx][ny] = dis[x][y];
					q.push_front({nx, ny});
				}
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m >> sx >> sy >> limitLeft >> limitRight;
	sx--, sy--;
	for (int i = 0; i < n; i++) { cin >> grid[i]; }
	bfs();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (dis[i][j] <= limitLeft && dis[i][j] + j - sy <= limitRight) {
				ans++;
			}
		}
	}
	cout << ans << endl;
	return 0;
}

