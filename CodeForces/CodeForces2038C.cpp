// problem statement: https://codeforces.com/problemset/problem/2038/C

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 5;

int T, n;
int a[MAXN];
map<int, int> cnt;

int main() {
    ios::sync_with_stdio(0);
    cin >> T;
    while (T--) {
        cin >> n;
        cnt.clear();
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            cnt[a[i]]++;
        }
        vector<int> number;
        for (auto it = cnt.begin(); it != cnt.end(); it++) {
            int tmp = it->second;
            while (tmp >= 2) {
                number.push_back(it->first);
                tmp -= 2;
            }
        }
        if (number.size() < 4) { cout << "NO\n"; }
        else {
            cout << "YES\n";
            cout << number[0] << ' ' << number[1] << ' ';
            cout << number[0] << ' ' << number.back() << ' ';
            cout << number[number.size() - 2] << ' ' << number[1] << ' ';
            cout << number[number.size() - 2] << ' ' << number.back() << '\n';
        }
    }
    return 0;
}
