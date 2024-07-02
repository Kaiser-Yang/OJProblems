// problem statement:

#include <bits/stdc++.h>

using namespace std;

int k, lastJ = -1;
string ans = "1";
string n;

string multiply(string &a, char ch) {
    string res;
    res.resize(a.length() + 1, '0');
    reverse(a.begin(), a.end());
    for (int i = 0; i < a.length(); i++) {
        res[i + 1] += (res[i] - '0' + (a[i] - '0') * (ch - '0')) / 10;
        res[i] = (res[i] - '0' + (a[i] - '0') * (ch - '0')) % 10 + '0';
    }
    reverse(a.begin(), a.end());
    while (res.length() > 1 && res.back() == '0') { res.pop_back(); }
    reverse(res.begin(), res.end());
    return res;
}

string add(string &a, string &b) {
    string res;
    bool swapped = false;
    if (a.length() > b.length()) {
        swap(a, b);
        swapped = true;
    }
    res.resize(b.length() + 1, '0');
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    for (int i = 0; i < a.length(); i++) {
        res[i + 1] += (res[i] - '0' + a[i] - '0' + b[i] - '0') / 10;
        res[i] = (res[i] - '0' + a[i] - '0' + b[i] - '0') % 10 + '0';
    }
    for (int i = a.length(); i < b.length(); i++) {
        res[i + 1] += (res[i] - '0' + b[i] - '0') / 10;
        res[i] = (res[i] - '0' + b[i] - '0') % 10 + '0';
    }
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    while (res.length() > 1 && res.back() == '0') { res.pop_back(); }
    reverse(res.begin(), res.end());
    if (swapped) { swap(a, b); }
    return res;
}

string multiply(string &a, string &b) {
    string res = "0";
    for (int i = 0; i < a.length(); i++) {
        if (res != "0") { res.push_back('0'); }
        string temp = multiply(b, a[i]);
        res         = add(res, temp);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    n            = n.substr(max<int>(0, (int)n.length() - k), k);
    string tempN = n;
    for (int i = 1; i <= k; i++) {
        string temp = n.substr(max<int>(0, (int)n.length() - i), i), first;
        for (int j = 0; j < abs(min<int>((int)temp.length() - i, 0)); j++) { first.push_back('0'); }
        first += temp;
        for (int j = 1; j <= 10; j++) {
            temp = multiply(temp, tempN);
            temp = temp.substr(max<int>(0, (int)temp.length() - i), i);
            if (temp == first) {
                ans   = multiply(ans, j + '0');
                lastJ = j;
                break;
            }
            if (j == 10) {
                cout << "-1" << endl;
                return 0;
            }
        }
        string tt = tempN;
        for (int j = 1; j < lastJ; j++) {
            tempN = multiply(tempN, tt);
            tempN = tempN.substr(max<int>(0, (int)tempN.length() - k), k);
        }
    }
    cout << ans << endl;
    return 0;
}
