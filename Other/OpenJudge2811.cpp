// problem statement: http://bailian.openjudge.cn/practice/2811

#include <bits/stdc++.h>

using namespace std;

array<array<bool, 6>, 5> state, temp, ans;
int dx[] = {0, 1, -1, 0, 0};
int dy[] = {0, 0, 0, 1, -1};

void update(array<array<bool, 6>, 5> &s, int i, int j)
{
    for (int k = 0; k < 5; k++) {
        int nx = i + dx[k];
        int ny = j + dy[k];
        if (nx >= 0 && nx < 5 && ny >= 0 && ny < 6) { s[nx][ny] = !s[nx][ny]; }
    }
}

bool allZero(const array<bool, 6> &s)
{
    for (int i = 0; i < 6; i++) { if (s[i]) { return false; } }
    return true;
}

int main()
{
	ios::sync_with_stdio(false);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			cin >> state[i][j];
		}
	}
	for (int s = 0; s < (1 << 6); s++) {
        temp = state;
        for (int j = 0; j < 6; j++) {
            if (s & (1 << j)) {
                update(temp, 0, j);
                ans[0][j] = 1;
            } else {
                ans[0][j] = 0;
            }
        }
        for (int i = 1; i < 5; i++) {
            for (int j = 0; j < 6; j++) {
                if (temp[i - 1][j] == 1) {
                    update(temp, i, j);
                    ans[i][j] = 1;
                } else {
                    ans[i][j] = 0;
                }
            }
        }
        if (allZero(temp[4])) { break; }
	}
    for (int i = 0; i < 5; i++, cout << "\n") {
        for (int j = 0; j < 6; j++) {
            cout << ans[i][j] << " ";
        }
    }
	return 0;
}
