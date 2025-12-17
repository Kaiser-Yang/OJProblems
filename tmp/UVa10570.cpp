#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int n;
    vector<int> a;
    while (cin >> n && n != 0) {
        a.resize(n);
        for (int i = 0; i < n; i++) { cin >> a[i]; }
        int ans = n;
        for (int i = 0; i < n; i++) {
            vector<int> tmp(n);
            for (int j = 0; j < n; j++) { tmp[j] = a[(i + j) % n]; }
            int cnt = 0;
            for (int j = 0; j < n; ) {
                if (tmp[j] != j + 1) {
                    cnt++;
                    swap(tmp[j], tmp[tmp[j] - 1]);
                } else {
                    j++;
                }
            }
            ans = min(ans, cnt);
            cnt = 0;
            for (int j = 0; j < n; j++) { tmp[j] = a[(i + j) % n]; }
            for (int j = 0; j < n;) {
                if (tmp[j] != n - j) {
                    cnt++;
                    swap(tmp[j], tmp[n - tmp[j]]);
                } else {
                    j++;
                }
            }
            ans = min(ans, cnt);
            if (ans == 0) { break; }
        }
        cout << ans << endl;

    }
    return 0;
}
