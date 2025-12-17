#include <bits/stdc++.h>

using namespace std;


int dp(int x, int y, vector<vector<int>> &height, vector<vector<int>> &d)
{
    static const int DIRECTION_NUM = 4;
    static int dx[] = {0, 0, -1, 1};
    static int dy[] = {1, -1, 0, 0};
    int n = height.size();
    int m = height[0].size();

    int &ans = d[x][y];
    if (ans != -1) { return ans; }

    ans = 1;
    for (int i = 0; i < DIRECTION_NUM; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || ny < 0 || nx >= n || ny >= m || height[nx][ny] >= height[x][y]) {
            continue;
        }
        ans = max(ans, dp(nx, ny, height, d) + 1);
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int T, n, m;
    string name;
    vector<vector<int>> height;
    vector<vector<int>> d;
    cin >> T;
    while (T--) {
        cin >> name;
        cin >> n >> m;
        height.resize(n);
        d.clear();
        d.resize(n);
        for (int i = 0; i < n; i++) {
            height[i].resize(m);
            d[i].resize(m, -1);
            for (int j = 0; j < m; j++) {
                cin >> height[i][j];
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans = max(ans, dp(i, j, height, d));
            }
        }
        cout << name << ": " << ans << endl;
    }
    return 0;
}