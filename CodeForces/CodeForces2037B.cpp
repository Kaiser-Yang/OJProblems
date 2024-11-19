// problem statement: https://codeforces.com/problemset/problem/2037/B

#include <bits/stdc++.h>

using namespace std;

int T, k;
vector<int> a;
map<int, int> cnt;

int main() {
    ios::sync_with_stdio(0);
    cin >> T;
    while (T--) {
        cin >> k;
        a.resize(k);
        for (int i = 0; i < k; i++) {
            cin >> a[i];
            cnt[a[i]]++;
        }
        int ans1 = 0, ans2 = 0;
        for (int i = 0; i < k; i++) {
            if ((k - 2) % a[i] != 0) { continue; }
            cnt[a[i]]--;
            if (cnt[(k - 2) / a[i]] > 0) {
                ans1 = a[i];
                ans2 = (k - 2) / a[i];
                break;
            }
            cnt[a[i]]++;
        }
        cout << ans1 << " " << ans2 << '\n';
        cnt.clear();
    }
    return 0;
}
