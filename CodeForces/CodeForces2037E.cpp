// problem statement: https://codeforces.com/problemset/problem/2037/E

#include <bits/stdc++.h>

using namespace std;

int T, n;

int query(int l, int r) {
    cout << "? " << l << ' ' << r << '\n';
    cout.flush();
    int res;
    cin >> res;
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin >> T;
    while (T--) {
        cin >> n;
        string ans;
        int l = 1, r = 1, last_res = 0;
        bool found_first = false;
        while (r < n && ans.size() < n) {
            r++;
            int now_res = query(l, r);
            if (now_res == last_res && found_first) {
                ans.push_back('0');
            } else if (now_res != last_res) {
                if (!found_first) {
                    for (int i = 0; i < (r - l + 1 - 2 - (now_res - 1)); i++) {
                        ans.push_back('1');
                    }
                    for (int i = 0; i < now_res - 1; i++) { ans.push_back('0'); }
                    ans.push_back('0');
                    ans.push_back('1');
                    found_first = true;
                } else {
                    ans.push_back('1');
                }
                last_res = now_res;
            }
        }
        if (ans.size() < n) {
            cout << "! IMPOSSIBLE\n";
            continue;
        }
        cout << "! " << ans << '\n';
    }
    return 0;
}
