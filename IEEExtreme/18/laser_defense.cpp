// problem statement: https://csacademy.com/ieeextreme-practice/task/laser-defense

#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int len, n, m;
vector<int> a_u;
string direction;
int coordinate;

int main() {
    cin >> len >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> direction >> coordinate;
        if (direction == "U") { a_u.push_back(coordinate); }
    }
    sort(a_u.begin(), a_u.end());
    long long ans = n + 1;
    for (int i = 0; i < m; i++) {
        cin >> direction >> coordinate;
        if (direction == "L") { ans += n + 1; }
        else {
            int x = upper_bound(a_u.begin(), a_u.end(), coordinate) - a_u.begin();
            ans += n + 1 - x;
        }
    }
    cout << ans << endl;
}
