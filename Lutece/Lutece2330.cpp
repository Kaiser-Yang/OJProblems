#include <bits/stdc++.h>

using namespace std;

int n, ans;
vector<int> a, b, c;

int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    a.resize(n);
    b.resize(n);
    c.resize(n);
    for (int i = 0; i < n; i++) { cin >> a[i]; ans += a[i];}
    for (int i = 0; i < n; i++) { cin >> b[i]; }
    for (int i = 0; i < n; i++){ c[i] = b[i] - a[i]; }
    sort(c.begin(), c.end());
    for (int i = 0; i < n / 2; i++) { ans += c[i]; }
    cout << ans << endl;
    return 0;
}