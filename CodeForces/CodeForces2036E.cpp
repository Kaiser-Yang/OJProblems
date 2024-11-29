// problem statement: https://codeforces.com/contest/2036/problem/E

#include <bits/stdc++.h>

using namespace std;

int n, m, q, requirement_num;

struct Requirement {
    enum {
        LESS,
        GREATER,
    } type;
    int idx, value;
};

int main()
{
    ios::sync_with_stdio(false);
    cin >> m >> n >> q;
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            cin >> a[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            a[i][j] |= a[i][j - 1];
        }
    }
    while (q--) {
        cin >> requirement_num;
        vector<Requirement> requirement(requirement_num);
        string type_str;
        for (int i = 0; i < requirement_num; i++) {
            cin >> requirement[i].idx >> type_str >> requirement[i].value;
            if (type_str == ">") {
                requirement[i].type = Requirement::GREATER;
            } else {
                requirement[i].type = Requirement::LESS;
            }
        }
        int left = 1, right = m;
        for (auto && req: requirement) {
            if (left > right) {
                break;
            }
            if (req.type == Requirement::LESS) {
                auto iter = lower_bound(a[req.idx].begin() + left, a[req.idx].begin() + right + 1, req.value);
                iter--;
                right = min(right, (int)(iter - a[req.idx].begin()));
            } else {
                auto iter = upper_bound(a[req.idx].begin() + left, a[req.idx].begin() + right + 1, req.value);
                if (iter == a[req.idx].begin() + right + 1) {
                    right = 0;
                    break;
                } else {
                    left = max(left, (int)(iter - a[req.idx].begin()));
                }
            }
        }
        if (left > right) {
            cout << "-1\n";
        } else {
            cout << left << "\n";
        }
    }
    return 0;
}
