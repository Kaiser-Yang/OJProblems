// problem statement: https://codeforces.com/contest/2047/problem/C

#include <bits/stdc++.h>

using namespace std;

int T, n;
vector<int> a, b;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; i++) { cin >> a[i]; }
        b.resize(n);
        for (int i = 0; i < n; i++) { cin >> b[i]; }
        long long ans = 0;
        vector<int> rest;
        for (int i = 0; i < n; i++) {
            if (a[i] > b[i]) {
                ans += a[i];
                rest.push_back(b[i]);
            } else {
                ans += b[i];
                rest.push_back(a[i]);
            }
        }
        int max_rest = rest[0];
        for (int i = 1; i < rest.size(); i++) {
            max_rest = max(max_rest, rest[i]);
        }
        ans += max_rest;
        cout << ans << '\n';
    }
    return 0;
}
