#include <bits/stdc++.h>

using namespace std;

int n, x, y;
vector<int> a;

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> x >> y;
    a.resize(n);
    for (int i = 0; i < n; i++) { cin >> a[i]; }
    int ans = std::numeric_limits<int>::max();
    for (int i = 0; i <= 5000; i++) {
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if (a[j] <= i * x) { continue; }
            cnt += (a[j] - i * x) / y;
            if ((a[j] - i * x) % y) { cnt++; }
        }
        ans = min(ans, i + cnt);
    }
    cout << ans << endl;
    return 0;
}