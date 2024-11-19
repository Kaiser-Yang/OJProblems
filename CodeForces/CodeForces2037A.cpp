// problem statement: https://codeforces.com/problemset/problem/2037/A

#include <bits/stdc++.h>

using namespace std;

int T, n, a[22];
map<int, int> cnt;

int main() {
    ios::sync_with_stdio(0);
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            cnt[a[i]]++;
        }
        int ans = 0;
        for (auto [x, y] : cnt) { ans += y / 2; }
        cout << ans << '\n';
        cnt.clear();
    }
    return 0;
}
