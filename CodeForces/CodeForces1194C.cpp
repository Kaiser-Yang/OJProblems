// problem satement: https://codeforces.com/contest/1194/problem/C

#include <bits/stdc++.h>

using namespace std;

int T;
vector<int> cnt1(26), cnt2(26), cnt3(26);
string s, t, p;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> s >> t >> p;
        fill(cnt1.begin(), cnt1.end(), 0);
        fill(cnt2.begin(), cnt2.end(), 0);
        fill(cnt3.begin(), cnt3.end(), 0);
        for (int i = 0; i < s.length(); i++) { cnt1[s[i] - 'a']++; }
        for (int i = 0; i < t.length(); i++) { cnt2[t[i] - 'a']++; }
        for (int i = 0; i < p.length(); i++) { cnt3[p[i] - 'a']++; }
        bool flag = true;
        for (int i = 0; i < 26; i++) {
            if (cnt1[i] + cnt3[i] < cnt2[i]) flag = false;
        }
        if (flag) {
            int pos = 0;
            for (int i = 0; i < s.length(); i++) {
                if (pos >= t.length()) {
                    flag = false;
                    break;
                }
                bool found = false;
                for (; pos < t.length();) {
                    if (t[pos] == s[i]) {
                        found = true;
                        pos++;
                        break;
                    }
                    pos++;
                }
                if (!found) {
                    flag = false;
                    break;
                }
            }
        }
        cout << (flag ? "YES\n" : "NO\n");
    }
    return 0;
}
