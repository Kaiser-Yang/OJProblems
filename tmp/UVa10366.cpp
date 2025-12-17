#include <bits/stdc++.h>

using namespace std;

int solve(vector<int> &h, int left) {
    left = abs(left);
    int n = h.size();
    int res = h[0] * 2;
    int maxHeight = h[0];
    int leftVolumn = 0;
    int i;
    for (i = 1; i <= left / 2; i++) {
        if (h[i] >= maxHeight) {
            maxHeight = h[i];
            leftVolumn = res;
            res += h[i] * 2;
        } else {
            res += maxHeight * 2;
        }
    }
    while (i < n && h[i] < maxHeight) {
        res += maxHeight * 2;
        i++;
    }
    if (i == n) {
        // if you want to remove this if-check,
        // you need to convert the res from 32-bit integer to 64-bit integer lest overflow
        return numeric_limits<int>::max();
    }
    if (h[i] == maxHeight) {
        int rightMostVolumn = 0;
        i++;
        while (i < n) {
            rightMostVolumn += maxHeight * 2;
            if (h[i] > maxHeight) { break; }
            i++;
        }
        res += leftVolumn;
        if (leftVolumn > rightMostVolumn) { res -= leftVolumn - rightMostVolumn; }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    int left, right;
    vector<int> h;
    while (cin >> left >> right && left != 0 && right != 0) {
        int n = (right - left) / 2 + 1;
        h.resize(n);
        for (int i = 0; i < n; i++) { cin >> h[i]; }
        int ans = solve(h, left);
        for (int i = 0; i < n / 2; i++) { swap(h[i], h[n - i - 1]); }
        ans = min(ans, solve(h, right));
        cout << ans << endl;
    }
    return 0;
}
