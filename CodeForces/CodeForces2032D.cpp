// problem statement: https://codeforces.com/contest/2032/problem/D

#include <bits/stdc++.h>

using namespace std;

int T, n;

bool path_contain_root(int a, int b) {
    cout << "? " << a << " " << b << '\n';
    cout.flush();
    int res;
    cin >> res;
    return res == 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        vector<int> p(n, -1);
        p[1] = 0;
        int now = 2;
        while (true) {
            if (!path_contain_root(now, 1)) { break; }
            p[now] = 0;
            now++;
        }
        p[now] = 1;
        int tentacle_cnt = now - 1;
        set<int> tentacle;
        for (int i = 2; i <= tentacle_cnt; i++) { tentacle.insert(i); }
        tentacle.insert(now++);
        while (now < n) {
            if (path_contain_root(now, *tentacle.begin())) {
                tentacle.erase(tentacle.begin());
            } else {
                p[now] = *tentacle.begin();
                tentacle.erase(tentacle.begin());
                tentacle.insert(now++);
            }
        }
        cout << "!";
        for (int i = 1; i < n; i++) { cout << " " << p[i]; }
        cout << '\n';
    }
    return 0;
}
