// problem statement: https://codeforces.com/contest/1063/problem/C

#include <bits/stdc++.h>

using namespace std;

int n;
string s;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    cout << "0 1\n";
    cout.flush();
    cin >> s;
    bool black = s == "black";
    int l = 1, r = 1e9;
    for (int i = 1; i < n; i++) {
        int mid = (l + r) / 2;
        cout << mid << " 1\n";
        cout.flush();
        cin >> s;
        if (s == "black" && black || s == "white" && !black) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << l << " 0 " << r << " 2\n";
    return 0;
}
