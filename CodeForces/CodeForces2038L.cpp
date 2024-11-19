// problem statement: https://codeforces.com/problemset/problem/2038/L

#include <bits/stdc++.h>

using namespace std;

int n, ans;

int main() {
    ios::sync_with_stdio(0);
    cin >> n;
    if (n % 2 == 1) {
        ans = n / 2 + 1 + n / 2;
        ans += (n - n / 2 + 3 - 1) / 3;
    } else {
        ans = n / 2 + n / 2;
        ans += (n - n / 2 + 3 - 1) / 3;
    }
    cout << ans << endl;
    return 0;
}
