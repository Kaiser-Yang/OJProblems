// problem statement: https://codeforces.com/contest/2036/problem/F

#include <bits/stdc++.h>

using namespace std;

int T;
long long l, r;
int i, k;

long long xor_0_n(long long n) {
    switch (n % 4) {
        case 0: return n;
        case 1: return 1;
        case 2: return n + 1;
        case 3: return 0;
    }
    return -1;
}

long long xor_l_r(long long l, long long r) {
    if (r < l) { return 0; }
    if (l == 0) { return xor_0_n(r); }
    return xor_0_n(r) ^ xor_0_n(l - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> l >> r >> i >> k;
        long long ans = xor_l_r(l, r) ^ (xor_l_r(max(l, (long long)k) >> i, r >> i) << i);
        long long cnt = (r >> i) - (max(l, (long long)k) >> i) + 1;
        if (max(l, (long long)k) == l && (l & ((1 << i) - 1)) > k) {
            ans ^= l >> i << i;
            cnt--;
        }
        if ((r & ((1 << i) - 1)) < k) {
            ans ^= r >> i << i;
            cnt--;
        }
        if (cnt > 0 && cnt % 2 == 1) { ans ^= k; }
        cout << ans << '\n';
    }
    return 0;
}
