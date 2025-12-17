#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    int T, n, length;
    vector<int> a;
    cin >> T;
    while (T--) {
        cin >> n >> length;
        a.resize(n);
        for (int i = 0; i < n; i++) { cin >> a[i]; }
        sort(a.begin(), a.end());
        int left = 0, right = n - 1;
        int ans = 0;
        while (left <= right) {
            if (a[left] + a[right] <= length) {
                left++;
                right--;
            } else {
                right--;
            }
            ans++;
        }
        cout << ans << endl;
        if (T != 0) { cout << endl; }
    }
    return 0;
}
