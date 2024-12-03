// problem statement: https://codeforces.com/contest/2047/problem/D

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
        vector<int> min_a(n);
        for (int i = 0; i < n; i++) { cin >> a[i]; }
        min_a[n - 1] = a[n - 1];
        for (int i = n - 2; i >= 0; i--) { min_a[i] = min(a[i], min_a[i + 1]); }
        int now = numeric_limits<int>::max();
        for (int i = 0; i < n; i++) {
            if (a[i] > now) {
                a[i]++;
            } else if (a[i] != min_a[i]) {
                a[i]++;
                now = min(now, a[i]);
            }
        }
        sort(a.begin(), a.end());
        for (int i = 0; i < n; i++) { cout << a[i] << " \n"[i == n - 1]; }
    }
    return 0;
}
