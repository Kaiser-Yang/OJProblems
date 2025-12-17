#include <bits/stdc++.h>

using namespace std;

struct Cube
{
    int a, b, c;
    Cube() = default;
    Cube(int a, int b, int c)
    {
        if (a > b) { swap(a, b); }
        if (a > c) { swap(a, c); }
        if (b > c) { swap(b, c); }
        this->a = a;
        this->b = b;
        this->c = c;
    }

    int& operator[](int index)
    {
        if (index == 0) { return a; }
        if (index == 1) { return b; }
        return c;
    }
};

int dp(int index, int k, vector<vector<int>> &d, vector<Cube> &cube)
{
    int &ans = d[index][k];
    if (ans != -1) { return ans; }

    int n = d.size();
    int nowa = -1;
    int nowb = -1;
    for (int kk = 0; kk < 3; kk++) {
        if (kk == k) {
            continue;
        } else if (nowa == -1) {
            nowa = cube[index][kk];
        } else if (nowb == -1) {
            nowb = cube[index][kk];
        }
    }

    ans = 0;

    for (int i = 0; i < n; i++) {
        if (nowa > cube[i][1] && nowb > cube[i][2]) {
            ans = max(ans, dp(i, 0, d, cube));
        }
        if (nowa > cube[i][0] && nowb > cube[i][2]) {
            ans = max(ans, dp(i, 1, d, cube));
        }
        if (nowa > cube[i][0] && nowb > cube[i][1]) {
            ans = max(ans, dp(i, 2, d, cube));
        }
    }

    ans += cube[index][k];

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int n, a, b, c, kase = 0;
    vector<Cube> cube;
    vector<vector<int>> d;
    while (cin >> n && n != 0) {
        cube.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> a >> b >> c;
            cube[i] = Cube(a, b, c);

        }
        kase++;
        cout << "Case " << kase << ": maximum height = ";
        d.clear();
        d.resize(n);
        for (int i = 0; i < n; i++) { d[i].resize(3, -1); }
        int ans = -1;
        for (int i = 0; i < n; i++) {
            ans = max(ans, dp(i, 0, d, cube));
            ans = max(ans, dp(i, 1, d, cube));
            ans = max(ans, dp(i, 2, d, cube));
        }
        cout << ans << endl;
    }
    return 0;
}
