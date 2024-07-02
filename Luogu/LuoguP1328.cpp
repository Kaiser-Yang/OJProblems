// problem statement: https://www.luogu.com.cn/problem/P1328

#include <bits/stdc++.h>

using namespace std;

int n, na, nb, temp;
int ans1, ans2;

queue<int> a, b;

int state[5][5] = {{0, -1, 1, 1, -1},
                   {1, 0, -1, 1, -1},
                   {-1, 1, 0, -1, 1},
                   {-1, -1, 1, 0, 1},
                   {1, 1, -1, -1, 0}};

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> na >> nb;
    for (int i = 0; i < na; i++) {
        cin >> temp;
        a.push(temp);
    }
    for (int i = 0; i < nb; i++) {
        cin >> temp;
        b.push(temp);
    }
    while (n--) {
        int aState = a.front(), bState = b.front();
        a.pop();
        b.pop();
        if (state[aState][bState] == 1) {
            ans1++;
        } else if (state[aState][bState] == -1) {
            ans2++;
        }
        a.push(aState);
        b.push(bState);
    }
    cout << ans1 << " " << ans2 << "\n";
    return 0;
}
