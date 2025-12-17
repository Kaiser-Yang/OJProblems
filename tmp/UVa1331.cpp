#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-6;

template<typename T>
pair<double, double> dot2Vec(const pair<T, T> &vec1, const pair<T, T> &vec2)
{
    return make_pair(vec2.first - vec1.first, vec2.second - vec1.second);
}

template<typename T>
double dotProduct(const pair<T, T> &vec1, const pair<T, T> &vec2)
{
    return 1.0 * vec1.first * vec2.first + 1.0 * vec1.second * vec2.second;
}

template<typename T>
double crossProduct(const pair<T, T> &vec1, const pair<T, T> &vec2)
{
    return 1.0 * vec1.first * vec2.second - 1.0 * vec1.second * vec2.first;
}

int cmp(double a, double b)
{
    if (fabs(a - b) <= eps) { return 0; }
    if (a - b > 0) { return 1; }
    return -1;
}

template<typename T>
bool dotInPolygon(const pair<T, T> &dot, const vector<pair<T, T>> &polygon)
{
    bool flag = false;
    int n = polygon.size();
    pair<T, T> p1, p2;
    for (int i = 0, j = n - 1; i < n; j=i++) {
        p1 = polygon[i];
        p2 = polygon[j];
        if (cmp(crossProduct(dot2Vec(dot, p1), dot2Vec(dot, p2)), 0) == 0 &&
            cmp(dotProduct(dot2Vec(p1, dot), dot2Vec(dot, p2)), 0) >= 0) { return true; }
        if (((cmp(p1.second, dot.second) > 0) != (cmp(p2.second, dot.second) > 0)) &&
            cmp(dot.first - p1.first, 1.0 * (dot.second - p1.second) * (p1.first - p2.first) / (p1.second - p2.second)) < 0) {
            flag = !flag;
        }
    }
    return flag;
}

bool ok(int a, int b, int c, vector<pair<double, double>> &p)
{
    int n = p.size();
    for (int i = 0; i < n; i++) {
        if (i == a || i == b || i == c) { continue; }
        if (dotInPolygon(p[i], {p[a], p[b], p[c]})) { return false; };
    }
    return true;
}

double getArea(const pair<double, double> &p1, const pair<double, double> &p2, const pair<double, double> &p3)
{
    return fabs(crossProduct(dot2Vec(p1, p2), dot2Vec(p1, p3))) / 2;
}

int main()
{
    ios::sync_with_stdio(false);
    int T, n;
    vector<pair<double, double>> p;
    vector<vector<double>> dp;
    cin >> T;
    while (T--) {
        cin >> n;
        p.resize(n);
        for (int i = 0; i < n; i++) { cin >> p[i].first >> p[i].second; }
        dp.clear();
        dp.resize(n);
        for (int i = 0; i < n; i++) { dp[i].resize(n);}
        for (int i = n - 3; i >= 0; i--) {
            for (int j = i + 2; j < n; j++) {
                dp[i][j] = numeric_limits<double>::max();
                for (int k = i + 1; k < j; k++) {
                    if (ok(i, j, k, p)) {
                        dp[i][j] = min(dp[i][j], max(dp[i][k], max(dp[k][j], getArea(p[i], p[j], p[k]))));
                    }
                }
            }
        }
        cout << fixed << setprecision(1) << dp[0][n - 1] << endl;
    }
    return 0;
}
