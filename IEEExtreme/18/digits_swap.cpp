// problem statement: https://csacademy.com/ieeextreme-practice/task/digits-swap

#include <bits/stdc++.h>

using namespace std;

int n, k;
string number, max_number, ans;

void dfs(int depth, int k) {
    if (depth == n || k == 0) { return; }
    if (number[depth] != max_number[depth]) {
        for (int j = n - 1; j > depth; j--) {
            if (number[j] != max_number[depth]) { continue; }
            swap(number[depth], number[j]);
            ans = max(ans, number);
            dfs(depth + 1, k - 1);
            swap(number[depth], number[j]);
        }
    } else {
        dfs(depth + 1, k);
    }
}

int main() {
    cin >> number;
    cin >> k;
    n = number.size();
    max_number = number;
    sort(max_number.begin(), max_number.end(), greater<char>());
    ans = number;
    dfs(0, k);
    cout << ans << endl;
    return 0;
}
