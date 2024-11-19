// problem statement: https://codeforces.com/problemset/problem/2029/B

#include <bits/stdc++.h>

using namespace std;

int T, n;
string a, b;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> a >> b;
        int cnt1 = 0, cnt0 = 0;
        for (int i = 0; i < a.size(); i++) {
            if (a[i] == '0') { cnt0++; }
            else { cnt1++; }
        }
        bool ok = true;
        for (int i = 0; i < b.size(); i++) {
            if (cnt0 == 0 || cnt1 == 0) {
                ok = false;
                break;
            }
            if (b[i] == '0') {
                cnt1--;
            } else {
                cnt0--;
            }
        }
        cout << (ok ? "YES\n" : "NO\n");
    }
    return 0;
}
