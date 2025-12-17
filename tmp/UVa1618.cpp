#include <bits/stdc++.h>

using namespace std;

bool check(vector<int> &a)
{
    int n = a.size();
    vector<vector<int>> maxVal(n), greaterA(n);
    for (int i = 0; i < n; i++) {
        maxVal[i].resize(n);
        if (i + 1 < n) {
            maxVal[i][i + 1] = 0;
        }
        for (int j = i + 2; j < n; j++) {
            maxVal[i][j] = max(maxVal[i][j - 1], a[j - 1]);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[j] > a[i]) {
                greaterA[i].push_back(a[j]);
            }
        }
        sort(greaterA[i].begin(), greaterA[i].end());
    }
    for (int p = 0; p < n; p++) {
        for (int r = p + 2; r < n; r++) {
            if (a[p] < a[r] || maxVal[p][r] < a[p]) {
                continue;
            }
            auto iter = upper_bound(greaterA[r].begin(), greaterA[r].end(), a[p]);
            if (iter != greaterA[r].end() && *iter < maxVal[p][r]) {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    int T, n;
    vector<int> a;
    cin >> T;
    while (T--) {
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; i++) { cin >> a[i]; }
        if (check(a)) {
            cout << "YES" << endl;
            continue;
        }
        for (int i = 0; i < n / 2; i++) { swap(a[i], a[n - i - 1]); }
        if (check(a)) {
            cout << "YES" << endl;
            continue;
        }
        cout << "NO" << endl;
    }
    return 0;
}
