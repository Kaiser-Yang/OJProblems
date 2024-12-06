// problem statement: https://codeforces.com/contest/2050/problem/A

#include <bits/stdc++.h>

using namespace std;

int T, n, m;
vector<string> word;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        word.resize(n);
        for (int i = 0; i < n; i++) { cin >> word[i]; }
        int now = 0, cnt = 0;
        for (int i = 0; i < n; i++) {
            now += word[i].size();
            if (now > m) { break; }
            cnt++;
        }
        cout << cnt << endl;
    }
    return 0;
}
