// problem statement: https://codeforces.com/problemset/problem/2038/J

#include <bits/stdc++.h>

using namespace std;

int n;
string event;
int number;

int main() {
    ios::sync_with_stdio(0);
    cin >> n;
    int now = 0;
    for (int i = 0; i < n; i++) {
        cin >> event >> number;
        if (event == "P") {
            now += number;
        } else {
            if (now < number) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
            now = max(now - number, 0);
        }
    }
    return 0;
}
