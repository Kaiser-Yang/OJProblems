// problem statement: https://codeforces.com/contest/2034/problem/E

#include <bits/stdc++.h>

using namespace std;

int T, n, k;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> k;
        if (k == 1) {
            if (n == 1) {
                cout << "YES\n";
                cout << "1\n";
            } else {
                cout << "NO\n";
            }
            continue;
        }
        long long total = 1;
        for (int i = 1; i <= n; i++) {
            total *= i;
            if (total >= k + 3) { break; }
        }
        if (total < k) {
            cout << "NO\n";
            continue;
        } else if (k % 2 == 1 && n % 2 == 0) {
            cout << "NO\n";
            continue;
        } else if (k % 2 == 1 && total < k + 3) {
            cout << "NO\n";
            continue;
        }
        vector<vector<int>> ans;
        vector<int> now(n), nex(n);
        iota(now.begin(), now.end(), 1);
        if (k % 2 == 0) {
            do {
                for (int i = 0; i < n; i++) { nex[i] = n - now[i] + 1; }
                ans.push_back(now);
                ans.push_back(nex);
            } while (next_permutation(now.begin(), now.end()) && ans.size() < k);
        } else {
            ans.resize(3);
            for (int i = 0; i < n; i++) { ans[0].push_back(i + 1); }
            for (int i = 0; i < n; i++) {
                ans[1].push_back((n + 1) / 2 + i);
                if (ans[1][i] > n) { ans[1][i] -= n; }
            }
            for (int i = 0; i < n; i++) {
                ans[2].push_back((1 + n) * 3 / 2 - ans[0][i] - ans[1][i]);
            }
            do {
                for (int i = 0; i < n; i++) { nex[i] = n - now[i] + 1; }
                bool skip = false;
                for (int i = 0; i < 3; i++) {
                    if (now == ans[i] || nex == ans[i]) { skip = true; }
                }
                if (skip) { continue; }
                ans.push_back(now);
                ans.push_back(nex);
            } while (next_permutation(now.begin(), now.end()) && ans.size() < k);
        }
        cout << "YES\n";
        for (int i = 0; i < ans.size(); i++) {
            for (int j = 0; j < ans[i].size(); j++) { cout << ans[i][j] << " \n"[j == n - 1]; }
        }
    }
    return 0;
}
