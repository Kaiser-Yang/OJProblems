#include <bits/stdc++.h>

using namespace std;

void change(vector<pair<int, int>> &ans, vector<int> &a, vector<int> &pos, int i) {
    int left = i;
    int right = pos[i];
    swap(pos[a[left]], pos[a[right]]);
    swap(a[left], a[right]);
    ans.push_back(make_pair(left, right));
    ans.push_back(make_pair((left + right) / 2, (left + right) / 2 + 1));
    ans.push_back(make_pair(left, right));
}

int main() {
    ios::sync_with_stdio(false);
    int T, n;
    vector<int> a;
    vector<int> pos;
    cin >> T;
    while (T--) {
        cin >> n;
        a.resize(n + 1);
        pos.clear();
        pos.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            pos[a[i]] = i;
        }
        vector<pair<int, int>> ans;
        for (int i = 1; i <= n; i++) {
            if (pos[i] == i) { continue; }
            if (abs(pos[i] - i + 1) % 2 == 0) {
                change(ans, a, pos, i);
            } else {
                int left = pos[i] - 1;
                int right = pos[i];
                swap(pos[a[left]], pos[a[right]]);
                swap(a[left], a[right]);
                ans.push_back(make_pair(left, right));
                if (pos[i] == i) { continue; }
                change(ans, a, pos, i);
            }
        }
        cout << ans.size() << endl;
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i].first << " " << ans[i].second << endl;
        }
    }
    return 0;
}
