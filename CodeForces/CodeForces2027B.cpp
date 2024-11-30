// problem statement: https://codeforces.com/contest/2027/problem/B

#include <bits/stdc++.h>

using namespace std;

int T, n;
vector<int> a;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; i++) { cin >> a[i]; }
        int ans = n;
        for (int i = 0; i < n; i++) {
            int cnt = 0;
            for (int j = 0; j < n; j++) {
                if (a[j] > a[i]) { cnt++; }
                if (j < i && a[j] < a[i]) { cnt++; }
            }
            ans = min(ans, cnt);
        }
        cout << ans << '\n';
    }
    return 0;
}
