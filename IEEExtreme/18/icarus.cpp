// problem statement: https://csacademy.com/ieeextreme-practice/task/icarus

#include <bits/stdc++.h>

using namespace std;

string str;
int l_cnt, r_cnt, u_cnt, depth, high, low;
int n;

void cal_low_or_high(char ch) {
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == ch) {
            depth++;
            low = max(low, depth);
        } else if (str[i] == 'U') {
            depth--;
            high = min(high, depth);
        }
    }
}

int main() {
    cin >> str;
    n = str.size() * 2;
    for (auto &&ch : str) {
        if (ch == 'L') {
            l_cnt++;
        } else if (ch == 'R') {
            r_cnt++;
        } else {
            u_cnt++;
        }
    }
    if (l_cnt <= u_cnt) {
        cal_low_or_high('L');
        cout << n << " " << -high + 1 << " " << n << "\n";
        for (int i = 1; i <= n; i++) {
            cout << (i + 1 <= n ? i + 1 : 0) << " 0\n";
        }
    } else if (r_cnt <= u_cnt) {
        cal_low_or_high('R');
        cout << n << " " << -high + 1 << " " << n << "\n";
        for (int i = 1; i <= n; i++) {
            cout << "0 " << (i + 1 <= n ? i + 1 : 0) << "\n";
        }
    } else {
        cal_low_or_high('L');
        cout << n << " " << n - low << " " << 1 << endl;
        for (int i = 1; i <= n; i++) {
            cout << (i + 1 <= n ? i + 1 : 0) << " 0\n";
        }
    }
    return 0;
}
