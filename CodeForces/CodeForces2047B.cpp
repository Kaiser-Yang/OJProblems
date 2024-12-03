// problem statement: https://codeforces.com/contest/2047/problem/B

#include <bits/stdc++.h>

using namespace std;

int T, n;
string s;

int main()
{
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> s;
        map<char, int> cnt;
        for (int i = 0; i < n; i++) { cnt[s[i]]++; }
        int min_i = -1, max_i = -1;
        for (int i = 0; i < n; i++) {
            if (min_i == -1) {
                min_i = i;
            } else if (cnt[s[i]] < cnt[s[min_i]]) {
                min_i = i;
            }
            if (max_i == -1) {
                max_i = i;
            } else if (cnt[s[i]] > cnt[s[max_i]]) {
                max_i = i;
            }
        }
        if (min_i == max_i) {
            for (int i = 0; i < n; i++) {
                if (s[i] != s[min_i]) {
                    max_i = i;
                    break;
                }
            }
        }
        // cout << min_i << " " << max_i << '\n';
        s[min_i] = s[max_i];
        cout << s << '\n';
    }
    return 0;
}
