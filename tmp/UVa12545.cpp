#include <bits/stdc++.h>

using namespace std;

int main()
{
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    ios::sync_with_stdio(false);
    int T;
    string str1, str2;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> str1 >> str2;
        int len = str1.length();
        int cnt = 0;
        for (int i = 0; i < len; i++) {
            if (str1[i] == '0' || str1[i] == '?') { cnt++; }
            if (str2[i] == '0') { cnt--; }
        }
        int ans = -1;
        if (cnt >= 0) {
            ans = cnt = 0;
            for (int i = 0; i < len; i++) {
                if (str1[i] == '0') { cnt++; }
                if (str2[i] == '0') { cnt--; }
            }
            if (cnt >= 0) {
                for (int i = 0; i < len; i++) {
                    if (str1[i] == '?') {
                        str1[i] = '1';
                        ans++;
                    }
                }
                for (int i = 0; i < len && cnt > 0; i++) {
                    if (str1[i] == '0' && str2[i] == '1') {
                        ans++;
                        str1[i] = '1';
                        cnt--;
                    }
                }
                for (int i = 0; i < len && cnt > 0; i++) {
                    if (str1[i] == '0') {
                        ans++;
                        str1[i] = '1';
                        cnt--;
                    }
                }
            } else {
                for (int i = 0; i < len && cnt < 0; i++) {
                    if (str1[i] == '?' && str2[i] == '0') {
                        str1[i] = '0';
                        cnt++;
                        ans++;
                    }
                }
                for (int i = 0; i < len && cnt < 0; i++) {
                    if (str1[i] == '?') {
                        str1[i] = '0';
                        cnt++;
                        ans++;
                    }
                }
                for (int i = 0; i < len; i++) {
                    if (str1[i] == '?') {
                        str1[i] = '1';
                        ans++;
                    }
                }
            }
            cnt = 0;
            for (int i = 0; i < len; i++) {
                if (str1[i] != str2[i]) {
                    cnt++;
                }
            }
            ans += cnt / 2;
        }
        cout << "Case " << t << ": " << ans << endl;
    }
    return 0;
}
