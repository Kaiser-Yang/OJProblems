// problem statement: https://www.luogu.com.cn/problem/U69096

#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> a;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) { cin >> a[i]; }
    for (int i = n - 1; i > 0; i--) { a[i] -= a[i - 1]; }
    for (int i = 0; i < n; i++) { cout << a[i] << (i == n - 1 ? "\n" : " "); }
    return 0;
}
