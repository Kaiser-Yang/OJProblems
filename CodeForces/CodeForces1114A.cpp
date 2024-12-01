// problem statement: https://codeforces.com/contest/1114/problem/A

#include <bits/stdc++.h>

using namespace std;

int x, y, z, a, b, c;

int main() {
    ios::sync_with_stdio(false);
    cin >> x >> y >> z >> a >> b >> c;
    if (a < x) {
        cout << "NO" << endl;
    } else {
        a -= x;
        if (a + b < y) {
            cout << "NO" << endl;
        } else {
            if (a + b + c - y < z) {
                cout << "NO" << endl;
            } else {
                cout << "YES" << endl;
            }
        }
    }
    return 0;
}
