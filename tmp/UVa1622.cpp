#include <bits/stdc++.h>

using namespace std;

long long solve(long long r, long long c, long long n, long long s, long long w, long long e)
{
    if (n < s) { swap(n, s); }
    if (w < e) { swap(w, e); }
    long long res = 0;
    if (s != 0) {
        res += r * c;
        r--;
        n -= s;
        if (n != 0) {
            res += r * c * 2 * s;
            n--;
        } else {
            res += r * c * (2 * s - 1);
        }
        s = 0;
    }
    if (e != 0) {
        w -= e;
        if (w) {
            e *= 2;
            w--;
        } else {
            e = 2 * e - 1;
        }
        while (c + (c - 1) * e <= r && n != 0) {
            res += r * c;
            r--;
            n--;
        }
        res += r * c;
        c--;
        res += e * r * c;
        e = 0;
    }
    while (n + w > 0 && r * c > 0) {
        res += r * c;
        if ((c > r && w != 0) || n == 0) {
            c--;
            w--;
        } else {
            n--;
            r--;
        }
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    int r, c;
    int n, s, w, e;
    int t = 0;
    while (cin >> r >> c && r != 0 && c != 0) {
        cin >> n >> s >> w >> e;
        t++;
        cout << "Case " << t << ": " << max(solve(r, c, n, s, w, e), solve(c, r, w, e, n, s)) << endl;
    }
    return 0;
}
