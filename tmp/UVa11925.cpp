#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int n;
    vector<int> a;
    while (cin >> n && n != 0) {
        a.resize(n);
        for (int i = 0; i < n; i++) { cin >> a[i]; }
        vector<int> ans;
        int pos = 0;
        while (true) {
            if (a[pos] > a[(pos + 1) % n] && a[pos] != n) {
                swap(a[pos], a[(pos + 1) % n]);
                ans.push_back(1);
            } else {
                bool done = true;
                for (int i = 0; i < n; i++) {
                    if (a[(pos + i) % n] != i + 1) {
                        done = false;
                        break;
                    }
                }
                if (done) { break; }
                pos = (pos - 1 + n) % n;
                ans.push_back(2);
            }
        }
        for (int i = ans.size(); i > 0; i--) { cout << ans[i - 1]; }
        cout << endl;
    }
    return 0;
}