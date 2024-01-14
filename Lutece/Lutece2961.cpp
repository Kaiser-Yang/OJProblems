#include <bits/stdc++.h>

using namespace std;

int n, k, lo, ans;
vector<bool> love, seasoned;

int main()
{
    cin >> n >> k;
    love.resize(2 * n);
    seasoned.resize(2 * n);
    for (int i = 0; i < n; i++) {
        cin >> lo;
        love[i] = love[i + n] = lo;
    }
    for (int i = 1; i <= n && k > 0; i++) {
        if (love[i] && love[i - 1] && love[i + 1]) {
            seasoned[i] = true;
            k--;
        }
    }
    for (int i = 1; i <= n && k > 0; i++) {
        if (seasoned[i]) { continue; }
        if ((love[i] && love[i + 1]) || (love[i] && love[i - 1]) || (love[i - 1] && love[i + 1])) {
            seasoned[i] = true;
            k--;
        }
    }
    for (int i = 1; i <= n && k > 0; i++) {
        if (seasoned[i]) { continue; }
        if (love[i] || love[i + 1] || love[i - 1]) {
            seasoned[i] = true;
            k--;
        }
    }
    for (int i = 1; i <= n && k > 0; i++) {
        if (seasoned[i]) { continue; }
        seasoned[i] = true;
        k--;
    }
    seasoned[0] = seasoned[n];
    seasoned[n + 1] = seasoned[1];
    for (int i = 1; i <= n; i++) {
        if (love[i]) { ans += 3; }
        else { ans += 3 - seasoned[i - 1] - seasoned[i] - seasoned[i + 1]; }
    }
    cout << ans << endl;
    return 0;
}