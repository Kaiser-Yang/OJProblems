#include <bits/stdc++.h>

using namespace std;

int T;
vector<string> grid;

int numberNotInPosition() {
    int res                     = 0;
    static const char *result[] = {"11111", "01111", "00*11", "00001", "00000"};
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (grid[i][j] != '*' && result[i][j] != grid[i][j]) { res++; }
        }
    }
    return res;
}

bool dfs(int nowDepth, int maxDepth) {
    static int dx[] = {1, 1, -1, -1, 2, 2, -2, -2};
    static int dy[] = {2, -2, 2, -2, 1, -1, 1, -1};

    if (nowDepth == maxDepth) { return numberNotInPosition() == 0; }
    if (maxDepth - nowDepth < numberNotInPosition()) { return false; }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (grid[i][j] == '*') {
                for (int k = 0; k < 8; k++) {
                    int nx = i + dx[k];
                    int ny = j + dy[k];
                    if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5) { continue; }
                    swap(grid[i][j], grid[nx][ny]);
                    if (dfs(nowDepth + 1, maxDepth)) { return true; }
                    swap(grid[i][j], grid[nx][ny]);
                }
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        grid.clear();
        grid.resize(5);
        cin >> grid[0] >> grid[1] >> grid[2] >> grid[3] >> grid[4];
        bool ok = false;
        for (int i = 0; i <= 15; i++) {
            if (dfs(0, i)) {
                cout << i << endl;
                ok = true;
                break;
            }
        }
        if (!ok) { cout << "-1\n"; }
    }
    return 0;
}