// problem statement: https://codeforces.com/contest/1063/problem/A

#include <bits/stdc++.h>

using namespace std;

int n;
string s;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> s;
    sort(s.begin(), s.end());
    cout << s << endl;
    return 0;
}
