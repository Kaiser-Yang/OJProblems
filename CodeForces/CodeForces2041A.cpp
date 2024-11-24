// problem statement: https://codeforces.com/problemset/problem/2041/A

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    int x;
    map<int, bool> mp;
    for (int i = 0; i < 4; i++) {
        cin >> x;
        mp[x] = true;
    }
    for (int i = 1; i <= 5; i++) {
        if (mp.count(i) == 0) {
            cout << i << endl;
            break;
        }
    }
    return 0;
}
