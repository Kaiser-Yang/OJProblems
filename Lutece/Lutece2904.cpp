#include <bits/stdc++.h>

using namespace std;

int n, number;
bool win;
vector<bool> x(1e5 + 10, false);

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> number;
        x[number] = !x[number];
    }
    for (int i = 0; i < x.size(); i++) {
        if (x[i]) {
            win = true;
            break;
        }
    }
    cout << (win ? "YES" : "NO") << endl;
    return 0;
}