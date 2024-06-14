// problem statement: 

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 5e4 + 10;

int n, ans = numeric_limits<int>::max();

using Student = pair<int, int>;

Student want[MAXN]; // want[i] : the two students who the i-th student wants to stand aside.
int pos[MAXN]; // pos[i] : the position of the i-th student.

void minOperations()
{
	vector<int> cnt(n, 0);
	for (int i = 1; i <= n; i++) {
		cnt[((pos[i] - i) % n + n) % n]++;
	}
	for (int i = 0; i < n; i++) {
		ans = min(ans, n - cnt[i]);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++) { cin >> want[i].first >> want[i].second; }
	pos[1] = 1; // put the 1st stuent one at 1st position;
	pos[n] = want[1].first;
	pos[2] = want[1].second;
	for (int i = 3; i < n; i++) {
		if (want[pos[i- 1]].first == pos[i - 2]) {
			pos[i] = want[pos[i - 1]].second;
		} else if (want[pos[i- 1]].second == pos[i - 2]) {
			pos[i] = want[pos[i - 1]].first;
		} else {
			cout << "-1\n" << endl;
			return 0;
		}
	}
	minOperations();
	reverse(pos + 1, pos + 1 + n);
	minOperations();
	cout << ans << endl;
	return 0;
}
