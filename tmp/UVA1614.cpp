#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int n;
    vector<pair<int, int>> a;
    vector<bool> positive;
    while (cin >> n) {
        a.resize(n);
        positive.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i].first;
            a[i].second = i;
        }
        sort(a.begin(), a.end());
        long long sum = 0;
        for (int i = 0; i < n; i++) { sum += a[i].first; }
        if (sum % 2 == 1) {
            cout << "No" << endl;
            continue;
        }
        long long now = 0;
        for (int i = 0; i < n; i++) {
            now += a[i].first;
            positive[a[i].second] = true;
            if (now > sum / 2) {
                for (int j = i - 1; j >= 0; j--) {
                    if (now - sum / 2 >= a[j].first) {
                        positive[a[j].second] = false;
                        now -= a[j].first;
                    }
                }
                for (int j = i + 1; j < n; j++) { positive[a[j].second] = false; }
                break;
            }
        }
        cout << "Yes" << endl;
        for (int i = 0; i < n; i++) {
            if (positive[i]) {
                cout << "1";
            } else {
                cout << "-1";
            }
            cout << (i == n - 1 ? "\n" : " ");
        }
    }
    return 0;
}
