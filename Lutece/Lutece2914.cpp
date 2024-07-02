#include <bits/stdc++.h>

using namespace std;

const long long mod = 276276276;

long long n, ans = 1;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    long long x = 1;
    for (int i = 1; i <= n; i++) {
        ans = (ans * x) % mod;
        if (i == 1) { continue; }
        x = (x << 1) % mod;
    }
    cout << ans << endl;
    return 0;
}