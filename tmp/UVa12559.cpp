#include <bits/stdc++.h>

using namespace std;

struct Circle
{
    int r, x, y;
    bool operator < (const Circle &rhs) {
        if (r != rhs.r) { return r < rhs.r; }
        if (x != rhs.x) { return x < rhs.x; }
        return y < rhs.y;
    }
};

bool check(int r, int x, int y, vector<string> &g)
{
    int tot = 0, valid = 0;
    for (int i = x - r; i <= x + r; i++) {
        for (int j = y - r; j <= y + r; j++) {
            double dis = (x - i) * (x - i) + (y - j) * (y - j);
            dis = sqrt(dis);
            if (fabs(dis - r) <= 0.5) {
                tot++;
                if (g[i][j] == '1') { valid++; }
            } else if (j > y && dis > r) {
                break;
            } else if (j < y && dis < r) {
                j = 2 * y - j;
            }

        }
    }
    return valid * 1.0 / tot > 0.95;
}

int main()
{
    ios::sync_with_stdio(false);
    int T, w, h;
    vector<string> g;
    vector<Circle> circle;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> w >> h;
        g.resize(h);
        for (int i = 0; i < h; i++) { cin >> g[i]; }
        circle.clear();
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                for (int r = 5; r <= min(h, w); r++) {
                    if (i - r < 0 || i + r >= h || j - r < 0 || j + r >= w) { continue; }
                    if (check(r, i, j, g)) {
                        circle.push_back({r, j, i});
                    }
                }
            }
        }
        sort(circle.begin(), circle.end());
        cout << "Case " << t << ": " << circle.size();
        for (int i = 0; i < circle.size(); i++) {
            cout << " (" << circle[i].r << "," << circle[i].x << "," << circle[i].y << ")";
        }
        cout << endl;
    }
    return 0;
}
