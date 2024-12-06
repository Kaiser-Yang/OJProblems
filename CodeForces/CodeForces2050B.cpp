// problem statement: https://codeforces.com/contest/2050/problem/B

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
        long long sum = accumulate(a.begin(), a.end(), 0LL);
        if (sum % n == 0) {
            long long sum1 = 0, sum2 = 0;
            for (int i = 0; i < n; i += 2) { sum1 += a[i]; }
            sum2 = sum - sum1;
            if (sum / n == sum1 / ((n + 1) / 2) && sum / n == sum2 / (n - (n + 1) / 2)) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
