// problem statement: https://www.luogu.com.cn/problem/P2197

#include <bits/stdc++.h>

constexpr int MAXN = 1e4 + 10;

using namespace std;

int T, n;
unsigned long long a;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        unsigned long long nim_sum = 0;
        for (int i = 0; i < n; i++) { cin >> a; nim_sum ^= a; }
        cout << (nim_sum != 0 ? "Yes\n" : "No\n");
    }
    return 0;
}
