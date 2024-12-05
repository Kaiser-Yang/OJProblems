// problem statement: https://codeforces.com/contest/1186/problem/A

#include <bits/stdc++.h>

using namespace std;

int n, m, k;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    cout << (m >= n && k >= n ? "YES" : "NO") << endl;
    return 0;
}
