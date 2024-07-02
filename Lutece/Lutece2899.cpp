#include <bits/stdc++.h>

using namespace std;

int n, ans;
string s;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> s;
    s.pop_back();
    s.push_back('1');
    for (char ch : s) { ans += ch - '0'; }
    cout << "1 " << ans << endl;
    return 0;
}