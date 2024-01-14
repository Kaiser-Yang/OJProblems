#include <bits/stdc++.h>

using namespace std;

int m, n, k, ans;
vector<string> grid;
vector<pair<int, int>> emptyGrid, fullGrid;

bool pairCmp(const pair<int, int> &lhs, const pair<int, int> &rhs)
{
    if (lhs.second != rhs.second) {
        return lhs.second < rhs.second;
    }
    return lhs.first < rhs.first;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> m >> n >> k;
    grid.resize(m);
    for (int i = 0; i < m; i++) { cin >> grid[i]; }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '0' && i * n + j + 1 <= k) {
                emptyGrid.push_back({i, j});
            } else if (grid[i][j] == '1' && i * n + j + 1 > k) {
                fullGrid.push_back({i, j});
            }
        }
    }
    sort(emptyGrid.begin(), emptyGrid.end(), pairCmp);
    sort(fullGrid.begin(), fullGrid.end(), pairCmp);

    for (int i = 0; i < emptyGrid.size(); i++) {
        ans += abs(fullGrid[i].first - emptyGrid[i].first) + abs(fullGrid[i].second - emptyGrid[i].second);
    }

    cout << ans << endl;
    return 0;
}