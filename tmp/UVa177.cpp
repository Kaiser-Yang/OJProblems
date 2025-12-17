#include <bits/stdc++.h>

using namespace std;

enum MOVEMENT_ENUM { UP, DOWN, LEFT, RIGHT };

void getMovement(int n, vector<MOVEMENT_ENUM> &movement) {
    if (n == 1) {
        movement.push_back(RIGHT);
        movement.push_back(UP);
        return;
    }
    getMovement(n - 1, movement);
    int size = movement.size();
    for (int i = 0; i < size / 2; i++) { movement.push_back(MOVEMENT_ENUM(movement[i] ^ 1)); }
    for (int i = size / 2; i < size; i++) { movement.push_back(MOVEMENT_ENUM(movement[i])); }
}

int main() {
    ios::sync_with_stdio(false);
    int n;
    vector<MOVEMENT_ENUM> movement;
    while (cin >> n && n != 0) {
        movement.clear();
        getMovement(n, movement);
        int x = 0, y = 0;
        int minC = 0, maxC = 0, minR = 0, maxR = 0;
        vector<pair<int, int>> place;
        place.push_back(make_pair(0, 0));
        for (int i = 1; i < movement.size(); i++) {
            if (movement[i] == UP) {
                if (movement[i - 1] == RIGHT) {
                    y++;
                } else if (movement[i - 1] == LEFT) {
                    y--;
                }
            } else if (movement[i] == DOWN) {
                if (movement[i - 1] == RIGHT) {
                    x++;
                    y++;
                } else if (movement[i - 1] == LEFT) {
                    x++;
                    y--;
                }
            } else if (movement[i] == LEFT) {
                if (movement[i - 1] == UP) {
                    x--;
                    y--;
                } else if (movement[i - 1] == DOWN) {
                    y--;
                }
            } else {
                if (movement[i - 1] == UP) {
                    x--;
                    y++;
                } else if (movement[i - 1] == DOWN) {
                    y++;
                }
            }
            minR = min(minR, x);
            maxR = max(maxR, x);
            maxC = max(maxC, y);
            minC = min(minC, y);
            place.push_back(make_pair(x, y));
        }
        maxR -= minR;
        maxC -= minC;
        vector<vector<char>> ans;
        ans.resize(maxR + 1);
        for (int i = 0; i <= maxR; i++) { ans[i].resize(maxC + 1, ' '); }
        for (int i = 0; i < movement.size(); i++) {
            if (movement[i] == UP || movement[i] == DOWN) {
                ans[place[i].first - minR][place[i].second - minC] = '|';
            } else {
                ans[place[i].first - minR][place[i].second - minC] = '_';
            }
        }
        for (int i = 0; i <= maxR; i++) {
            int right = maxC;
            while (ans[i][right] == ' ') { right--; }
            for (int j = 0; j <= right; j++) { cout << ans[i][j]; }
            cout << endl;
        }
        cout << "^" << endl;
    }

    return 0;
}
