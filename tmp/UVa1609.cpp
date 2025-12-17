/*
    There are 2 to k teams which are in competition. And you are given the match table,
if match[i][j] == 1, the i-th team will win from the j-th team. At initial, the 1st team
can fight half or more than half teams, and if the 1st team can not beat k-th team, there
must be one team j subject to that the team i can beat and the team j can beat team k. You
need find out one match solution to make the 1-st team to get the champion.
*/
#include <bits/stdc++.h>

using namespace std;

void solve(vector<vector<bool>> &win, vector<bool> &out) {
    int n = out.size();
    vector<int> losed(n);
    bool done = true;
    for (int i = 1; i < n; i++) {
        if (!out[i]) {
            done = false;
            if (win[0][i]) {
                losed[i] = 1;
            } else {
                losed[i] = 0;
            }
        }
    }
    if (done) { return; }
    for (int i = 1; i < n; i++) {
        if (!out[i] && losed[i] == 1) {
            for (int j = 1; j < n; j++) {
                if (!out[j] && win[i][j] && losed[j] == 0) {
                    losed[i] = losed[j] = -1;
                    out[j] = true;
                    printf("%d %d\n", i + 1, j + 1);
                    break;
                }
            }
        }
    }
    for (int i = 1; i < n; i++) {
        if (!out[i] && losed[i] == 1) {
            losed[i] = -1;
            out[i] = true;
            printf("%d %d\n", 1, i + 1);
            break;
        }
    }
    for (int i = 1; i < n; i++) {
        if (!out[i] && losed[i] == 0) {
            for (int j = 1; j < n; j++) {
                if (i == j) { continue; }
                if (!out[j] && losed[j] == 0) {
                    losed[i] = losed[j] = -1;
                    if (win[i][j]) {
                        out[j] = true;
                    } else {
                        out[i] = true;
                    }
                    printf("%d %d\n", i + 1, j + 1);
                    break;
                }
            }
        }
    }
    for (int i = 1; i < n;) {
        if (out[i] || losed[i] == -1) {
            i++;
            continue;
        }
        int j = i + 1;
        while (out[j] || losed[j] == -1) { j++; }
        losed[i] = losed[j] = -1;
        if (win[i][j]) {
            out[j] = true;
        } else {
            out[i] = true;
        }
        printf("%d %d\n", i + 1, j + 1);
        i = j + 1;
    }
    losed.clear();
    solve(win, out);
}

int main() {
    int n;
    char s[n];
    vector<vector<bool>> win;
    while (scanf("%d", &n) != EOF) {
        win.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> s;
            win[i].resize(n);
            for (int j = 0; j < n; j++) { win[i][j] = s[j] - '0'; }
        }
        vector<bool> out(n, false);
        solve(win, out);
    }
    return 0;
}
