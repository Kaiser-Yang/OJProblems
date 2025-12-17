/*
    To begin with, there are one red balloon. After every one hour, every red balloon will become
three red balloons and one blue balloon, and every blue ballon will become four blue blue balloons.
You are given k, a, and b, and you need answer after k hours, how many are there red ballons from
line a to line b.
*/
#include <bits/stdc++.h>

using namespace std;

int quickPow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) { res *= a; }
        a *= a;
        b >>= 1;
    }
    return res;
}

long long f(int k, int i, vector<long long> &c)
{
    if (i == 0) { return 0; }
    else if (k == 0) { return 1; }
    else if (i <= quickPow(2, k -1)) { return f(k - 1, i, c) * 2; }
    else { return 2 * c[k - 1] + f(k - 1, i - quickPow(2, k - 1), c); }
    return 0;
}

int main()
{
    ios::sync_with_stdio(false);
    int T, a, b, k;
    vector<long long> c(31);
    c[0] = 1;
    for (int i = 1; i <= 30; i++) { c[i] = c[i - 1] * 3; }
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cin >> k >> a >> b;
        cout << "Case " << i << ": " << f(k, b, c) - f(k, a - 1, c) << endl;
    }
    return 0;
}