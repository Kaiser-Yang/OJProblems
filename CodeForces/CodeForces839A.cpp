// problem statement: https://codeforces.com/contest/839/problem/A

#include <bits/stdc++.h>

using namespace std;

int n, k;
vector<int> a;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    a.resize(n);
    for (int i = 0; i < n; i++) { cin >> a[i]; }
    int sum = 0, given = 0, ans = -1;
    for  (int i = 0; i < n; i++) {
        sum += a[i];
        given += min(8, sum);
        sum -= min(8, sum);
        if (given >= k) {
            ans = i + 1;
            break;
        }
    }
    cout << ans << endl;
    return 0;
}
