/*
    Your task is to assign n rooks on a n times n table, which are subject
to that any two rooks cannot attack each other and that the i-th rook must
be within a given rectangle which is depicted by four integer xl-i, yl-i,
xr-i and yr-i. If there is no solution, output "IMOPOSSIBLE", otherwise
output any solution which includes the place of each rook in order.
*/
#include <bits/stdc++.h>

using namespace std;

bool assign(vector<pair<int, int>> &interval, vector<int> &result) {
    vector<bool> assigned(interval.size(), false);
    for (int i = 1; i <= interval.size(); i++) {
        int index = -1, right = 0;
        for (int j = 0; j < interval.size(); j++) {
            if (assigned[j] || interval[j].first > i || interval[j].second < i) { continue; }
            if (index == -1 || right > interval[j].second) {
                index = j;
                right = interval[j].second;
            }
        }
        if (index == -1) { return false; }
        result[index] = i;
        assigned[index] = true;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    int n, a, b, c, d;
    vector<pair<int, int>> x, y;
    vector<int> px, py;
    while (cin >> n && n != 0) {
        x.resize(n);
        y.resize(n);
        px.resize(n);
        py.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> a >> b >> c >> d;
            x[i] = make_pair(a, c);
            y[i] = make_pair(b, d);
        }
        if (!assign(x, px) || !assign(y, py)) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            for (int i = 0; i < n; i++) { cout << px[i] << " " << py[i] << endl; }
        }
    }
    return 0;
}
