// problem statement: https://codeforces.com/problemset/problem/2028/A

#include <bits/stdc++.h>

using namespace std;

int T;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        int n, a, b;
        string str;
        cin >> n >> a >> b >> str;
        int x = 0, y = 0;
        bool done = false;
        for (int i = 0; i < n; i++) {
            if (str[i] == 'N') {
                y++;
            } else if (str[i] == 'E') {
                x++;
            } else if (str[i] == 'S') {
                y--;
            } else {
                x--;
            }
            if (x == a && y == b) {
                done = true;
                break;
            }
        }
        if (done) {
            cout << "YES\n";
            continue;
        }
        if (x == 0 && y == 0) {
            cout << "NO\n";
            continue;
        }
        int dx = 0, dy = 0;
        for (int i = 0; i < n; i++) {
            if (str[i] == 'N') {
                dy++;
            } else if (str[i] == 'E') {
                dx++;
            } else if (str[i] == 'S') {
                dy--;
            } else {
                dx--;
            }
            if (x == 0 && a - dx != 0) { continue; }
            if (y == 0 && b - dy != 0) { continue; }
            if (x == 0 && abs(b - dy) % abs(y) == 0 && (b - dy) / y > 0) { done = true; }
            if (y == 0 && abs(a - dx) % abs(x) == 0 && (a - dx) / x > 0) { done = true; }
            if (x != 0 && y != 0 && abs(a - dx) % abs(x) == 0 && abs(b - dy) % abs(y) == 0 &&
                (a - dx) / x == (b - dy) / y && (a - dx) / x > 0) {
                done = true;
            }
        }
        if (done) {
            cout << "YES\n";
            continue;
        }
        cout << "NO\n";
    }
    return 0;
}
