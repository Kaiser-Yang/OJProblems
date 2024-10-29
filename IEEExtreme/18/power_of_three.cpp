// problem statement: https://csacademy.com/ieeextreme-practice/task/power-of-three

#include <bits/stdc++.h>

using namespace std;

vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19};
// res[i] is the result of number % primes[i]
vector<int> res;
string number;
int x;

int quick_pow(int a, int b, int mod) {
    int res = 1;
    while (b) {
        if (b & 1) { res = 1LL * res * a % mod; }
        a = 1LL * a * a % mod;
        b >>= 1;
    }
    return res;
}

int str_mod(string s, int mod) {
    int res = 0;
    for (int i = 0; i < s.length(); i++) { res = (res * 10 + s[i] - '0') % mod; }
    return res;
}

bool check() {
    for (int i = 0; i < primes.size(); i++) {
        if (quick_pow(3, x, primes[i]) != res[i]) { return false; }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> number;
    int len = number.length();
    x = (len - 1) * (log(10.0) / log(3.0));
    for (int i = 0; i < primes.size(); i++) { res.push_back(str_mod(number, primes[i])); }
    for (int i = 0; i < 4; i++) {
        if (check()) {
            cout << x << endl;
            return 0;
        }
        x++;
    }
    cout << "-1\n";
    return 0;
}
