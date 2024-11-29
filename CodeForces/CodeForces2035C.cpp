// problem statement:  https://codeforces.com/contest/2035/problem/C

#include <bits/stdc++.h>

using namespace std;

int T, n;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        int len = 0;
        for (int i = 0; (1 << i) <= n; i++) {
            if (n & (1 << i)) { len = i; }
        }
        vector<int> a;
        int last = -1, last_but_one = -1, last_but_two = -1, last_but_three = -1, last_but_four = -1;
        if (n % 2 == 0) {
            last = n;
            last_but_one = (~n) & ((1 << len) - 1);
            last_but_two = (1 << len) - 1;
            last_but_three = -1;
            last_but_four = -1;
            if (last_but_two == last_but_one) {
                last_but_two--;
                last_but_three = 1;
                last_but_four = 3;
            }
        } else {
            last = n;
            last_but_one = n - 1;
            last_but_two = n & ((1 << len) - 1);
            last_but_three = (last_but_two == 1 ? 3 : 1);
        }
        int now = 1;
        for (int i = 0; i < n - 3 - (last_but_three != -1) - (last_but_four != -1); i++) {
            while (now == last || now == last_but_one || now == last_but_two ||
                   now == last_but_three || now == last_but_four) {
                now++;
            }
            a.push_back(now++);
        }
        if (last_but_four != -1) { a.push_back(last_but_four); }
        if (last_but_three != -1) { a.push_back(last_but_three); }
        a.push_back(last_but_two);
        a.push_back(last_but_one);
        a.push_back(last);
        int k = 0;
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                k &= a[i];
            } else {
                k |= a[i];
            }
        }
        cout << k << '\n';
        for (int i = 0; i < n; i++) { cout << a[i] << " \n"[i == n - 1]; }
    }
    return 0;
}
