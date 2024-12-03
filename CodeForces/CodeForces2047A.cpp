// problem statement: https://codeforces.com/contest/2047/problem/A

#include <bits/stdc++.h>

using namespace std;

int T, n;
vector<int> a;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; i++) { cin >> a[i]; }
        long long sum = 0;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            sum += a[i];
            long long s_root = sqrt(sum);
            if (s_root * s_root == sum && s_root % 2 == 1) { ans++; }
        }
        cout << ans << endl;
    }
    return 0;
}
