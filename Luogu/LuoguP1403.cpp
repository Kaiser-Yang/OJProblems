// problem statement:

#include <bits/stdc++.h>

using namespace std;

int n;
long long ans;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) { ans += n / i; }
    cout << ans << endl;
    return 0;
}
