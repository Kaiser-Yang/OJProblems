// problem statement: https://codeforces.com/contest/1186/problem/D

#include <bits/stdc++.h>

using namespace std;

int n;
long long sum;
vector<double> a;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) { cin >> a[i]; }
    for (int i = 0; i < n; i++) { sum -= int(a[i]); }
    for (int i = 0; i < n; i++) {
        if (a[i] == (int)a[i] || sum == 0) {
            cout << int(a[i]) << '\n';
        } else if (sum > 0) {
            if (a[i] < 0) {
                cout << int(a[i]) << '\n';
            } else {
                cout << int(a[i]) + 1 << '\n';
                sum--;
            }
        } else if (sum < 0) {
            if (a[i] > 0) {
                cout << int(a[i]) << '\n';
            } else {
                cout << int(a[i]) - 1 << '\n';
                sum++;
            }
        }
    }
    return 0;
}
