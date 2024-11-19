// problem statement: https://codeforces.com/problemset/problem/2038/N

#include <bits/stdc++.h>

using namespace std;

int T;
string s;

int main() {
    ios::sync_with_stdio(0);
    cin >> T;
    while (T--) {
        cin >> s;
        if (s[0] < s[2]) {
            cout << s[0] << '<' << s[2] << '\n';
        } else if (s[0] > s[2]) {
            cout << s[0] << '>' << s[2] << '\n';
        } else if (s[0] == s[2]) {
            cout << s[0] << '=' << s[2] << '\n';
        }
    }
    return 0;
}
