// problem statement: https://codeforces.com/contest/2041/problem/B

#include <bits/stdc++.h>

using namespace std;

int T;
int a, b;

int main() {
    ios::sync_with_stdio(0);
    cin >> T;
    while (T--) {
        cin >> a >> b;
        cout << (int)((-1 + sqrt(1 + 8 * (long long)(a + b))) / 2) << endl;
    }
    return 0;
}
