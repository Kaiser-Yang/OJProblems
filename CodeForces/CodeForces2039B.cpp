// problem statement: https://codeforces.com/contest/2039/problem/B

#include <bits/stdc++.h>

using namespace std;

int T;
string str;

int main() {
    ios::sync_with_stdio(0);
    cin >> T;
    while (T--) {
        cin >> str;
        if (str.length() == 1) {
            cout << "-1\n";
        } else {
            bool ok = false;
            for (int i = 0; i + 1 < str.length(); i++) {
                if (str[i] == str[i + 1]) {
                    ok = true;
                    cout << str[i] << str[i + 1] << '\n';
                    break;
                }
            }
            if (!ok && str.length() == 2) {
                cout << "-1\n";
            } else if (!ok) {
                for (int i = 0; i + 2 < str.length(); i++) {
                    if (str[i] != str[i + 1] && str[i + 1] != str[i + 2] && str[i] != str[i + 2]) {
                        ok = true;
                        cout << str[i] << str[i + 1] << str[i + 2] << '\n';
                        break;
                    }
                }
                if (!ok) { cout << "-1\n"; }
            }
        }
    }
    return 0;
}
