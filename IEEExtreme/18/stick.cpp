// problem statement: https://csacademy.com/ieeextreme-practice/task/stick

#include <bits/stdc++.h>

using namespace std;

int main() {
    long long n, k, l;
    cin >> n >> k >> l;
    unsigned long long x, y;
    long long x_left = max(k - l, 2 * k - l);
    long long y_bottom = max(k - l, 2 * k - l);
    long long x_right = min(k + l, 2 * k + l);
    long long y_top = min(k + l, 2 * k + l);
    if (x_left > x_right || y_bottom > y_top) {
        x = y = 0;
    } else {
        x = x_right - x_left;
        y = y_top - y_bottom;
    }
    unsigned long long u_n = n;
    unsigned long long u_l = l;
    cout << u_n * (4 * u_l * u_l - x * y) + x * y << endl;
    return 0;
}
