// problem statement: https://codeforces.com/contest/1185/problem/B

#include <bits/stdc++.h>

using namespace std;

int T;
string s, t;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> s >> t;
        int i = 0;
        bool ok = true;
        for (int j = 0; j < t.size(); j++) {
            if (i < s.size() && s[i] == t[j]) {
                i++;
            } else if (i > 0 && s[i - 1] == t[j]) {
                continue;
            } else {
                ok = false;
                break;
            }
        }
        cout << (ok && i == s.size() ? "YES" : "NO") << '\n';
    }
    return 0;
}
