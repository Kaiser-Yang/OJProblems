#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int T, n;
    long long d;
    vector<long long> h;
    vector<vector<long long>> dp;
    cin >> T;
    while (T--) {
        cin >> n >> d;
        h.resize(n);
        for (int i = 0; i < n; i++) { cin >> h[i]; }
        if (abs(h[0] - h[n - 1]) > (n - 1) * d) {
            cout << "impossible\n";
            continue;
        }
        vector<long long> x;
        for (int i = 0; i < n; i++) {
            for (int j = -n + 1; j <= n - 1; j++) { x.push_back(h[i] + j * d); }
        }
        sort(x.begin(), x.end());
        int len = unique(x.begin(), x.end()) - x.begin();
        dp.clear();
        dp.resize(n);
        for (int i = 0; i < n; i++) { dp[i].resize(len, numeric_limits<long long>::max()); }
        deque<int> dq;
        for (int j = 0; j < len; j++) {
            if (x[j] == h[0]) {
                dp[0][j] = 0;
                break;
            }
        }
        for (int i = 1; i < n; i++) {
            int left = 0, right = left;
            for (int j = 0; j < len; j++) {
                while (left < len && x[left] < x[j] - d) {
                    while (!dq.empty() && dq.front() <= left) { dq.pop_front(); }
                    left++;
                }
                if (right < left) { right = left; }
                while (right < len && x[right] <= x[j] + d) {
                    while (!dq.empty() && dp[i - 1][dq.back()] >= dp[i - 1][right]) {
                        dq.pop_back();
                    }
                    if (dp[i - 1][right] != numeric_limits<long long>::max()) {
                        dq.push_back(right);
                    }
                    right++;
                }
                if (dq.empty()) { continue; }
                dp[i][j] = dp[i - 1][dq.front()] + abs(h[i] - x[j]);
            }
        }
        for (int j = 0; j < len; j++) {
            if (x[j] == h[n - 1]) {
                cout << dp[n - 1][j] << endl;
                break;
            }
        }
    }
    return 0;
}
