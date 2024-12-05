// problem statement: https://codeforces.com/contest/1186/problem/C

#include <bits/stdc++.h>

using namespace std;

string a, b;
vector<int> cnt;

int main()
{
    ios::sync_with_stdio(false);
    cin >> a >> b;
    cnt.resize(a.size());
    for (int i = 0; i < a.size(); i++) {
        if (i == 0) {
            cnt[i] = (a[i] == '0');
        } else {
            cnt[i] = cnt[i - 1] + (a[i] == '0');
        }
    }
    int ans = 0, c = 0;
    for (int i = 0; i < b.size(); i++) {
        if (b[i] =='0') { c++; }
    }
    for (int l = 0; l + b.size() <= a.size(); l++) {
        int r = l + b.size() - 1;
        int cur = cnt[r] - (l == 0 ? 0 : cnt[l - 1]);
        if (cur % 2 == c % 2) { ans++; }
    }
    cout << ans << endl;
    return 0;
}
