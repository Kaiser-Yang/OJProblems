// problem statement: https://codeforces.com/contest/2042/problem/B

#include <bits/stdc++.h>

using namespace std;

int T, n;
vector<int> a;
map<int, int> cnt;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        a.resize(n);
        cnt.clear();
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            cnt[a[i]]++;
        }
        int cnt1 = 0, ans = 0;
        for (auto &&[k, v] : cnt) {
            if (v == 1) {
                cnt1++;
            } else {
                ans++;
            }
        }
        ans += (cnt1 + 1) / 2 * 2;
        cout << ans << '\n';
    }
    return 0;
}
