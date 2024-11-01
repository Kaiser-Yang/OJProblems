// problem statement: https://csacademy.com/ieeextreme-practice/task/sierpinski

#include <bits/stdc++.h>

using namespace std;

int T, x, y;

int dfs(int x, int y) {
    int las_end = 0;
    int cnt = 1, now_end = 2;
    while (now_end < x) {
        las_end = now_end;
        now_end = now_end * 2 + 1;
        cnt++;
    }
    if (y >= x - las_end && y <= x - (x - las_end - 1)) {
        return 0;
    } else if (y < x - las_end) {
        return dfs(x - las_end - 1, y);
    } else {
        return dfs(x - las_end - 1, y - (x - (x - las_end - 1)));
    }
}

int main() {
    cin >> T;
    while (T--) {
        cin >> x >> y;
        cout << dfs(x, y) << endl;
    }
    return 0;
}
