// problem statement: https://codeforces.com/contest/2040/problem/A

#include <bits/stdc++.h>

using namespace std;

int T, n, k;
vector<int> a;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> k;
        a.resize(n);
        for (int i = 0; i < n; i++) { cin >> a[i]; }
        int ans = -1;
        for (int i = 0; i < n; i++) {
            bool done = true;
            for (int j = 0; j < n; j++) {
                if (j == i) { continue; }
                if (abs(a[i] - a[j]) % k == 0) {
                    done = false;
                    break;
                }
            }
            if (done) {
                ans = i + 1;
                break;
            }
        }
        if (ans == -1) {
            cout << "NO\n";
        } else {
            cout << "YES\n" << ans << "\n";
        }
    }
    return 0;
}
