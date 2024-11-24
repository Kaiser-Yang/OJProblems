// problem statement: https://codeforces.com/contest/2041/problem/E

#include <bits/stdc++.h>

using namespace std;

int a, b;

int main() {
    ios::sync_with_stdio(0);
    cin >> a >> b;
    int a1 = (3 * a - b) / 2, a2 = b, a3 = 3 * a - a1 - a2;
    a1 -= 1000;
    a3 += 1000;
    cout << "3\n" << a1 << " " << a2 << " " << a3 << endl;
    return 0;
}
