// problem statement: https://codeforces.com/contest/2040/problem/C

#include <bits/stdc++.h>

using namespace std;

int T, n;
long long k;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> k;
        if (n - 1 <= 40 && 1LL << (n - 1) < k) {
            cout << -1 << "\n";
        } else {
            vector<int> ans(n);
            int head = 0, tail = n - 1;
            for (int i = 1; i <= n; i++) {
                if (n - i - 1 > 40 || n - i - 1 <= 40 && 1LL << (n - i - 1) >= k)  {
                    ans[head++] = i;
                } else {
                    ans[tail--] = i;
                    k -= 1LL << (n - i - 1);
                }
            }
            for (int i = 0; i < n; i++) {
                cout << ans[i] << " \n"[i == n - 1];
            }
        }
    }
    return 0;
}
