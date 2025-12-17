#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<double> p;
vector<vector<vector<double>>> d;

// dot2Vec
template <typename T>
pair<double, double> dot2Vec(const pair<T, T> &vec1, const pair<T, T> &vec2) {
    return make_pair(vec2.first - vec1.first, vec2.second - vec1.second);
}

// cross product
template <typename T>
double crossProduct(const pair<T, T> &vec1, const pair<T, T> &vec2) {
    return 1.0 * vec1.first * vec2.second - 1.0 * vec1.second * vec2.first;
}

double area(int i, int j, int k) {
    if (i == j || j == k || i == k) { return 0; }
    static const double PI = acos(-1);
    pair<double, double> p1, p2, p3;
    double thelta = p[i] * 2 * PI;
    p1 = {cos(thelta), sin(thelta)};
    thelta = p[j] * 2 * PI;
    p2 = {cos(thelta), sin(thelta)};
    thelta = p[k] * 2 * PI;
    p3 = {cos(thelta), sin(thelta)};
    return fabs(crossProduct(dot2Vec(p1, p2), dot2Vec(p1, p3))) / 2;
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    ios::sync_with_stdio(false);
    while (cin >> n >> m && !(n == 0 && m == 0)) {
        p.resize(n);
        for (int i = 0; i < n; i++) { cin >> p[i]; }
        d.clear();
        d.resize(n);
        for (int i = 0; i < n; i++) {
            d[i].resize(n);
            for (int j = 0; j < n; j++) { d[i][j].resize(m + 1, 0); }
        }
        for (int i = 0; i < n; i++) {
            for (int k = 3; k <= m; k++) {
                for (int j = (i + k - 1) % n; j != i; j = (j + 1) % n) {
                    for (int l = (i + 1) % n; l != j; l = (l + 1) % n) {
                        d[i][j][k] = max(d[i][j][k], d[i][l][k - 1] + area(i, l, j));
                    }
                }
            }
        }
        double ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = (i + m - 1) % n; j != i; j = (j + 1) % n) { ans = max(ans, d[i][j][m]); }
        }
        cout << fixed << setprecision(6) << ans << endl;
    }
    return 0;
}
