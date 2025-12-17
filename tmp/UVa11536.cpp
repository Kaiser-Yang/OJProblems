#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int T, n, m, k;
    vector<int> a;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> n >> m >> k;
        a.resize(n + 1);
        a[1] = 1;
        a[2] = 2;
        a[3] = 3;
        for (int i = 4; i <= n; i++) { a[i] = (a[i - 1] + a[i - 2] + a[i - 3]) % m + 1; }
        int l = 1, r = 1, c = 0, ans = -1;
        vector<int> cnt(m + 1);
        while (r <= n) {
            while (r <= n && c < k) {
                if (a[r] <= k && cnt[a[r]] == 0) { c++; }
                cnt[a[r]]++;
                r++;
            }
            if (c == k) {
                if (ans == -1) {
                    ans = r - l;
                } else {
                    ans = min(ans, r - l);
                }
            }
            cnt[a[l]]--;
            if (a[l] <= k && cnt[a[l]] == 0) { c--; }
            l++;
        }

        cout << "Case " << t << ": ";
        if (ans == -1) {cout << "sequence nai" << endl; }
        else { cout << ans << endl; }
    }
    return 0;
}
