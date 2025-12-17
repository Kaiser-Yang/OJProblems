#include <bits/stdc++.h>

using namespace std;

enum Direction { UP, DOWN, LEFT, RIGHT, MAX_DIRECTION };

Direction getDirection(char ch) {
    if (ch == 'U') { return UP; }
    if (ch == 'D') { return DOWN; }
    if (ch == 'L') { return LEFT; }
    return RIGHT;
}

int cost(int oldPlace, int newPlace, int nowFoot, int lastFoot) {
    if (nowFoot != lastFoot) { return 1; }
    if (newPlace == oldPlace) { return 3; }
    if (oldPlace == UP) {
        if (newPlace == DOWN) { return 7; }
        return 5;
    } else if (oldPlace == DOWN) {
        if (newPlace == UP) { return 7; }
        return 5;
    } else if (oldPlace == LEFT) {
        if (newPlace == RIGHT) { return 7; }
        return 5;
    } else {
        if (newPlace == LEFT) { return 7; }
        return 5;
    }
}

int main() {
    ios::sync_with_stdio(false);
    string str;
    vector<vector<vector<vector<int>>>> dp;
    vector<vector<vector<vector<pair<int, int>>>>> nex;
    vector<vector<vector<vector<char>>>> ans;
    while (cin >> str && str[0] != '#') {
        int n = str.length();
        dp.clear();
        dp.resize(n + 1);
        nex.resize(n);
        ans.resize(n);
        for (int i = 0; i < n; i++) {
            dp[i].resize(MAX_DIRECTION);
            nex[i].resize(MAX_DIRECTION);
            ans[i].resize(MAX_DIRECTION);
            for (int j = 0; j < MAX_DIRECTION; j++) {
                dp[i][j].resize(MAX_DIRECTION);
                nex[i][j].resize(MAX_DIRECTION);
                ans[i][j].resize(MAX_DIRECTION);
                for (int k = 0; k < MAX_DIRECTION; k++) {
                    dp[i][j][k].resize(3, numeric_limits<int>::max() / 2);
                    nex[i][j][k].resize(3);
                    ans[i][j][k].resize(3);
                }
            }
        }
        dp[n].resize(MAX_DIRECTION);
        for (int a = 0; a < MAX_DIRECTION; a++) {
            dp[n][a].resize(MAX_DIRECTION);
            for (int b = 0; b < MAX_DIRECTION; b++) {
                dp[n][a][b].resize(3, numeric_limits<int>::max() / 2);
                if (a == b) { continue; }
                if (a == RIGHT && b == LEFT) { continue; }
                for (int s = 0; s < 3; s++) { dp[n][a][b][s] = 0; }
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int a = 0; a < MAX_DIRECTION; a++) {
                for (int b = 0; b < MAX_DIRECTION; b++) {
                    if (a == b) { continue; }
                    if (a == RIGHT && b == LEFT) { continue; }
                    for (int s = 0; s < 3; s++) {
                        if (str[i] == '.') {
                            for (int k = 0; k < MAX_DIRECTION; k++) {
                                if (!((a == UP || a == DOWN) && b == LEFT) &&
                                    dp[i][a][b][s] > dp[i + 1][k][b][1] + cost(a, k, 1, s)) {
                                    dp[i][a][b][s] = dp[i + 1][k][b][1] + cost(a, k, 1, s);
                                    nex[i][a][b][s] = {k, b};
                                    ans[i][a][b][s] = 'L';
                                }
                                if (!((b == UP || b == DOWN) && a == RIGHT) &&
                                    dp[i][a][b][s] > dp[i + 1][a][k][2] + cost(b, k, 2, s)) {
                                    dp[i][a][b][s] = dp[i + 1][a][k][2] + cost(b, k, 2, s);
                                    nex[i][a][b][s] = {a, k};
                                    ans[i][a][b][s] = 'R';
                                }
                            }
                            if (dp[i][a][b][s] > dp[i + 1][a][b][0]) {
                                dp[i][a][b][s] = dp[i + 1][a][b][0];
                                nex[i][a][b][s] = {a, b};
                                ans[i][a][b][s] = '.';
                            }
                        } else {
                            if (!((a == UP || a == DOWN) && b == LEFT &&
                                  a != getDirection(str[i])) &&
                                dp[i][a][b][s] > dp[i + 1][getDirection(str[i])][b][1] +
                                                     cost(a, getDirection(str[i]), 1, s)) {
                                dp[i][a][b][s] = dp[i + 1][getDirection(str[i])][b][1] +
                                                 cost(a, getDirection(str[i]), 1, s);
                                nex[i][a][b][s] = {getDirection(str[i]), b};
                                ans[i][a][b][s] = 'L';
                            }
                            if (!((b == UP || b == DOWN) && a == RIGHT &&
                                  b != getDirection(str[i])) &&
                                dp[i][a][b][s] > dp[i + 1][a][getDirection(str[i])][2] +
                                                     cost(b, getDirection(str[i]), 2, s)) {
                                dp[i][a][b][s] = dp[i + 1][a][getDirection(str[i])][2] +
                                                 cost(b, getDirection(str[i]), 2, s);
                                nex[i][a][b][s] = {a, getDirection(str[i])};
                                ans[i][a][b][s] = 'R';
                            }
                        }
                    }
                }
            }
        }
        int a = LEFT, b = RIGHT, s = 0;
        for (int i = 0; i < n; i++) {
            cout << ans[i][a][b][s];
            int temma = a, tempb = b;
            a = nex[i][temma][tempb][s].first;
            b = nex[i][temma][tempb][s].second;
            if (ans[i][temma][tempb][s] == '.') {
                s = 0;
            } else if (ans[i][temma][tempb][s] == 'L') {
                s = 1;
            } else {
                s = 2;
            }
        }
        cout << endl;
    }
    return 0;
}