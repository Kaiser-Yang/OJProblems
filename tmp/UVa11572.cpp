/*
    You need to find the maximum subsequence that is subject to that there is no repetition of any number in the subsequence.
*/
#include <bits/stdc++.h>

using namespace std;

int main()
{
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    ios::sync_with_stdio(false);
    int T, n;
    vector<int> a;
    map<int, int> cnt;
    cin >> T;
    while (T--) {
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; i++) { cin >> a[i]; }
        cnt.clear();
        int left = 0, right = 0, ans = 0;
        // cnt[a[0]] = 1;
        while (left < n) {
            while (right < n && cnt[a[right]] == 0) {
                cnt[a[right]]++;
                right++;
            }
            // cout << left << " " << right << endl;
            ans = max(ans, right - left);
            cnt[a[left]]--;
            left++;
        }
        cout << ans << endl;
    }
    return 0;
}
