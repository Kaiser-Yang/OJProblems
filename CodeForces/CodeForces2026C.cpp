// problem statement: https://codeforces.com/contest/2026/problem/C

#include <bits/stdc++.h>

using namespace std;

int T, n;
string str;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> str;
        list<int> cnt0, cnt1;
        for (int i = 0; i < n; i++) {
            if (str[i] == '1') {
                cnt1.push_back(i);
            } else {
                cnt0.push_back(i);
            }
        }
        long long ans = 1LL * (1 + n) * n / 2;
        for (int i = n - 1; i >= 0; i--) {
            if (cnt1.empty()) { break; }
            if (str[i] == '0') {
                if (!cnt0.empty() && cnt0.back() == i) { cnt0.pop_back(); }
                continue;
            }
            cnt1.pop_back();
            if (!cnt0.empty()) {
                cnt0.pop_back();
            } else if (!cnt1.empty()) {
                cnt1.pop_front();
            } else {
                break;
            }
            ans -= i + 1;
        }
        cout << ans << endl;
    }
    return 0;
}
