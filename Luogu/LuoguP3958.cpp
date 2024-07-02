// problem statement: 

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e3 + 10;

int T, n, height;
long long r;
int h[MAXN];
struct Point
{
	long long x, y, z;
} point[MAXN];

int find(int x) { return x == h[x] ? x : h[x] = find(h[x]); }

bool same(int x, int y) { return find(x) == find(y); }

void join(int x, int y)
{
	int fx = find(x), fy = find(y);
	h[fx] = fy;
}

bool connect(const Point &a, const Point &b)
{
	return (a.x - b.x) * (a.x - b.x) +  (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z) <= 4 * r * r;
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		cin >> n >> height >> r;
		for (int i = 0; i <= n + 1; i++) { h[i] = i; }
		for (int i = 1; i <= n; i++) {
			cin >> point[i].x >> point[i].y >> point[i].z;
			if (abs(point[i].z - 0) <= r) { join(0, i); }
			if (abs(point[i].z - height) <= r) { join (n + 1, i); }
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (connect(point[i], point[j])) {
					join(i, j);
				}
			}
		}
		if (same(0, n + 1)) { cout << "Yes\n"; }
		else { cout << "No\n"; }
	}
	return 0;
}
