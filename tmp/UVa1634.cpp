#include <bits/stdc++.h>

using namespace std;

int T, n, ans;
vector<pair<int, int>> p;
vector<vector<int>> d;

// dot2Vec
template<typename T>
pair<double, double> dot2Vec(const pair<T, T> &vec1, const pair<T, T> &vec2)
{
    return make_pair(vec2.first - vec1.first, vec2.second - vec1.second);
}

// cross product
template<typename T>
double crossProduct(const pair<T, T> &vec1, const pair<T, T> &vec2)
{
    return 1.0 * vec1.first * vec2.second - 1.0 * vec1.second * vec2.first;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n;
        p.resize(n);
        for (int i = 0; i < n; i++) { cin >> p[i].first >> p[i].second; }
        ans = 0;
        for (int i = 0; i < n; i++) {
            vector<pair<int, int>> np;
            np.push_back({p[i].first, p[i].second});
            for (int j = 0; j < n; j++) {
                if (p[j].second > p[i].second || (p[j].second == p[i].second && p[j].first > p[i].first)) {
                    np.push_back({p[j].first, p[j].second});
                }
            }
            sort(np.begin(), np.end(), [i] (const pair<int, int>& lhs, const pair<int, int> &rhs) {
                pair<int, int> &&vec1 = dot2Vec(p[i], lhs);
                pair<int, int> &&vec2 = dot2Vec(p[i], rhs);
                double thelta1 = atan2(vec1.second, vec1.first);
                double thelta2 = atan2(vec2.second, vec2.first);
                if (thelta1 != thelta2) {
                    return thelta1 < thelta2;
                }
                return vec1.first < vec2.first;
            });
            d.clear();
            d.resize(np.size());
            for (int j = 0; j < np.size(); j++) { d[j].resize(np.size(), 0); }
            for (int j = 1; j < np.size(); j++) {
                int k = j - 1;
                while (k > 0 && crossProduct(dot2Vec(np[0], np[k]), dot2Vec(np[0], np[j])) == 0) { k--; }
                bool ok = (k == j -1);
                while (k > 0) {
                    int l = k - 1;
                    while (l > 0 && crossProduct(dot2Vec(np[l], np[k]), dot2Vec(np[k], np[j])) < 0) { l--; }
                    int area = abs(crossProduct(dot2Vec(np[0], np[j]), dot2Vec(np[0], np[k])));
                    area += d[k][l];
                    ans = max(ans, area);
                    if (ok) { d[j][k] = area; }
                    k = l;
                }
                if (ok) {
                    for (int k = 1; k < j; k++) { d[j][k] = max(d[j][k], d[j][k - 1]); }
                }
            }
        }
        cout << fixed << setprecision(1) << ans * 0.5 << endl;
    }
    return 0;
}