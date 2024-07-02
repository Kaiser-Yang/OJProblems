// problem statement: 

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 2e5 + 10;

using Dot = pair<double, double>;
int n;
Dot dot[MAXN];


double getDis(Dot a, Dot b) { return hypot(fabs(a.first - b.first), fabs(a.second - b.second)); }

double closestDistance(int l, int r)
{
	if (r - l + 1 == 2) {
		return getDis(dot[l], dot[r]);
	} else if (r - l + 1 == 3) {
		return min(getDis(dot[l], dot[l + 1]), min(getDis(dot[l], dot[r]), getDis(dot[l + 1], dot[r])));
	} else {
		int mid = l + r >> 1;
		double dis = min(closestDistance(l, mid), closestDistance(mid + 1, r));
		vector<Dot> res;
		res.push_back(dot[mid]);
		for (int i = mid + 2; i <= r; i++) {
			if (fabs(dot[i].first - dot[mid].first) >= dis) { break; }
			res.push_back(dot[i]);
		}
		res.push_back(dot[mid + 1]);
		for (int i = mid - 1; i >= l; i--) {
			if (fabs(dot[i].first - dot[mid + 1].first) >= dis) { break; }
			res.push_back(dot[i]);
		}
		sort(res.begin(), res.end(), [](const Dot &a, const Dot &b) {
			return a.second < b.second;
		});
		for (int i = 0; i < res.size(); i++) {
			for (int j = i + 1; j < res.size(); j++) {
				if (res[j].second - res[i].second >= dis) { break; }
				dis = min(dis, getDis(res[i], res[j]));
			}
		}
		return dis;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++) { cin >> dot[i].first >> dot[i].second; }
	sort(dot + 1, dot + 1 + n);
	cout << fixed << setprecision(4) << closestDistance(1, n) << endl;
	return 0;
}
