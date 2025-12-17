// UVa 1612's data is wrong, use this url: https://vjudge.net/problem/Gym-100134J
#include <bits/stdc++.h>

using namespace std;

void output(string &ans, int p, int a, int b)
{
    for (int i = 1; i < a; i++) {
        ans += to_string(p + i);
        ans += " ";
    }
    p = p + a - 1;
    if (b == 0) {
        ans += to_string(p + 1);
    } else {
        for (int i = 1; i <= (b + 1) / 2; i++) {
            ans += to_string(p + 2 * i);
            ans += " ";
        }
        if (b % 2 == 0) { p += b + 1;}
        else { p += b; }
        ans += to_string(p);
        ans += " ";
        for (int i = 1; i <= b / 2; i++) {
            ans += to_string(p - 2 * i);
            ans += " ";
        }
    }
}

int main()
{
    freopen("jumping.in", "r", stdin);
    freopen("jumping.out", "w", stdout);
    ios::sync_with_stdio(false);
    int T, a, b, c;
    cin >> T;
    while (T--) {
        cin >> a >> b >> c;
        string ans = "";
        int p = 0;
        for (int i = 0; i <= c / 3; i++) {
            ans += to_string(p + i * 3);
            ans += " ";
        }
        p += c / 3 * 3;
        if (c % 3 == 1) {
            ans += to_string(p + 3);
            ans += " ";
            p += 3;
            b--;
            p -= 2;
        } else if (c % 3 == 2) {
            ans += to_string(p + 3);
            ans += " ";
            p += 3;
            a--;
            p -= 1;
        } else {
            a--;
            p += 1;
        }
        for (int i = 0; i <= c / 3; i++) {
            ans += to_string(p - i * 3);
            ans += " ";
        }
        p -= c / 3 * 3;
        if (c % 3 == 1) {
            a--;
            p += 1;
        } else if (c % 3 == 2) {
            a--;
            p -= 1;
        } else {
            a--;
            p += 1;
        }
        for (int i = 0; i <= c / 3; i++) {
            ans += to_string(p + i * 3);
            ans += " ";
        }
        p += c / 3 * 3;
        if (c % 3 == 1) {
            b--;
            p += 2;
            ans += to_string(p);
            ans += " ";
        } else if (c % 3 == 2) {
            p += 3;
            ans += to_string(p);
            ans += " ";
        }
        output(ans, p, a, b);
        while (ans.back() == ' ') { ans.pop_back(); }
        cout << ans << endl;
    }
    return 0;
}
