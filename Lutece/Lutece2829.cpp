#include <bits/stdc++.h>

using namespace std;

int n, m, s = -1;

int sum(int i)
{
    return (1 + i) * i / 2 * (1 + i) * i / 2;
}

int maxVolumn(int i, int r, int h)
{
    int res = 0;
    for (int rr = r - 1, hh = h - 1; i > 0; i--, rr--, hh--) {
        res += rr * rr * hh;
    }
    return res;
}

void dfs(int depth, int nowN, int nowS, int lasR, int lasH)
{
    if (depth == m) {
        if (nowN != 0) { return; }
        if (s == -1) { s = nowS; }
        else { s = min(s, nowS); }
        return;
    }
    if (s != -1 && nowS >= s) { return; }
    if (nowN < sum(m - depth)) { return; }
    if (nowN > maxVolumn(m - depth, lasR, lasH)) { return; }
    for (int r = m - depth; r < lasR; r++) {
        for (int h = m - depth; h < lasH; h++) {
            int newN = nowN - r * r * h;
            int newS = nowS + 2 * r * h;
            if (depth == 0) { newS +=  r * r; }
            dfs(depth + 1, newN, newS, r, h);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    int maxR = sqrt((n - sum(m - 1)) / m + 1) + 1;
    int maxH = (n - sum(m - 1)) / (m * m) + 1;
    dfs(0, n, 0, maxR, maxH);
    if (s == -1) { s = 0; }
    cout << s << endl;
    return 0;
}