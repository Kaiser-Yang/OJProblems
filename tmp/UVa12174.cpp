/*
    You are given n integers, and an integer s. The n integers are all between [1, n].
You need find how many possible seperations there are that every seperation fits every
subsequence's length are s except the first one and the last one, and ensure every
subsequence has no repetition of any nubmer.
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int T, s, n;
    vector<int> a, cnt;
    vector<bool> filt;
    cin >> T;
    while (T--) {
        cin >> s >> n;
        a.resize(n);
        for (int i = 0; i < n; i++) { cin >> a[i]; }
        int ans = s, num = 0;
        filt.clear();
        filt.resize(s, 0);
        cnt.clear();
        cnt.resize(s + 1, 0);
        for (int i = 0; i < n + s; i++) {
            if (i >= s) {
                cnt[a[i - s]]--;
                if (cnt[a[i - s]] == 1) { num--; }
            }
            if (i < n) {
                cnt[a[i]]++;
                if (cnt[a[i]] == 2) { num++; }
            }
            if (num != 0) { filt[i % s] = true; }
        }
        for (int i = 0; i < s; i++) { ans -= filt[i]; }
        cout << ans << endl;
    }

    return 0;
}
