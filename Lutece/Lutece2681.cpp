#include <bits/stdc++.h>

using namespace std;

int n, c;
vector<int> a;

long long gcd(long long a, long long b)
{
    return b == 0 ? a : gcd(b, a % b);
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> c;
    a.resize(n);
    bool flag = false;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] == 0) { flag = true; }
    }
    long long ans1 = 1LL * (n - flag) * c;
    long long ans2 = n * 2;
    long long g = gcd(ans1, ans2);
    cout << ans1 / g << "/" << ans2 / g << endl;
    return 0;
}