// problem statement:

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXK     = 20;
constexpr int MAXN_BIT = 31;

int k;
string n, a[MAXK], b[MAXK], number[MAXN_BIT];
map<char, bool> convertible;

void dfs(char ch) {
    if (convertible.count(ch) == 1) { return; }
    convertible[ch] = true;
    for (int i = 0; i < k; i++) {
        if (a[i][0] == ch) { dfs(b[i][0]); }
    }
}

string multiply(string &a, string &b) {
    string res;
    if (b == "10") {
        res = a;
        res.push_back('0');
    } else {
        reverse(a.begin(), a.end());
        res.resize(a.length() + 1, '0');
        for (int i = 0; i < a.length(); i++) {
            res[i + 1] += ((a[i] - '0') * (b[0] - '0') + (res[i] - '0')) / 10;
            res[i] = ((a[i] - '0') * (b[0] - '0') + res[i] - '0') % 10 + '0';
        }
        while (res.length() > 1 && res.back() == '0') { res.pop_back(); }
        reverse(a.begin(), a.end());
        reverse(res.begin(), res.end());
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 0; i < k; i++) { cin >> a[i] >> b[i]; }
    dfs(n[0]);
    if (n.length() > 1) { convertible.erase('0'); }
    number[0] = to_string(convertible.size());
    for (int i = 1; i < n.length(); i++) {
        convertible.clear();
        dfs(n[i]);
        number[i] = to_string(convertible.size());
    }
    string ans = "1";
    for (int i = 0; i < n.length(); i++) { ans = multiply(ans, number[i]); }
    cout << ans << endl;
    return 0;
}
