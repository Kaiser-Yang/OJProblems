#include <bits/stdc++.h>

using namespace std;

int T, turn;
vector<string> grid;

int dfs(int turn)
{
    bool ok = true;
    int res = 0;
    if (turn == 1) { res = std::numeric_limits<int>::min(); }
    else { res = std::numeric_limits<int>::max(); }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] != '.') { continue; }
            ok = false;
            if (turn == 1) {
                grid[i][j] = 'O';
                res = max(res, dfs(!turn));
            } else {
                grid[i][j] = 'X';
                res = min(res, dfs(!turn));
            }
            grid[i][j] = '.';
        }
    }
    if (ok) {
        res = 0;
        for (int i = 0; i < 3; i++) {
            bool has1 = true, has2 = true;
            for (int j = 0; j < 3; j++) {
                if (grid[i][j] != 'O') {
                    has1 = false;
                }
                if (grid[j][i] != 'O') {
                    has2 = false;
                }
            }
            res += has1 + has2;
        }
        res += (grid[0][0] == 'O' && grid[1][1] == 'O' && grid[2][2] == 'O') +
               (grid[0][2] == 'O' && grid[1][1] == 'O' && grid[2][0] == 'O' );
        for (int i = 0; i < 3; i++) {
            bool has1 = true, has2 = true;
            for (int j = 0; j < 3; j++) {
                if (grid[i][j] != 'X') {
                    has1 = false;
                }
                if (grid[j][i] != 'X') {
                    has2 = false;
                }
            }
            res -= has1 + has2;
        }

        res -= (grid[0][0] == 'X' && grid[1][1] == 'X' && grid[2][2] == 'X') +
               (grid[0][2] == 'X' && grid[1][1] == 'X' && grid[2][0] == 'X' );
        return res;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        grid.clear();
        grid.resize(3);
        cin >> turn >> grid[0] >> grid[1] >> grid[2];
        cout << dfs(turn) << endl;
    }
    return 0;
}