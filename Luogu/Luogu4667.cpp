#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 510;
constexpr int MAXM = 510;
constexpr int  INF = 0x3f3f3f3f;

int n, m;
string grid[MAXN];
int dis[MAXN][MAXM];

enum DIRECTION
{
	LEFT_TOP, RIGHT_BOTTOM, RIGHT_TOP, LEFT_BOTTOM, MAX_DIRECTION,
};
int dx[] = {-1, 1, -1, 1};
int dy[] = {-1, 1, 1, -1};

bool bound(int x, int y)
{
	return x >= 0 && x <= n && y >= 0 && y <= m;
}

void bfs()
{
	memset(dis, 0x3f, sizeof(dis));
	using Node = pair<int, int>;
	deque<Node> q;
	q.push_front({0, 0});
	dis[0][0] = 0;
	while (!q.empty()) {
		auto front = q.front();
		q.pop_front();
		int x = front.first, y = front.second;
		for (int i = 0; i < MAX_DIRECTION; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (!bound(nx, ny)) { continue; }
			if ((i == LEFT_TOP && grid[nx][ny] != '\\') ||
			    (i == RIGHT_BOTTOM && grid[x][y] != '\\') ||
			    (i == RIGHT_TOP && grid[nx][y] != '/') ||
			    (i == LEFT_BOTTOM && grid[x][ny] != '/')) {
				if (dis[nx][ny] > dis[x][y] + 1) {
					dis[nx][ny] = dis[x][y] + 1;
					q.push_back({nx, ny});
				}
			} else {
				if (dis[nx][ny] > dis[x][y]) {
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
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> grid[i];
	}
	bfs();
	if (dis[n][m] != INF) {
		cout << dis[n][m] << endl;
	} else {
		cout << "NO SOLUTION\n";
	}
	return 0;
}
