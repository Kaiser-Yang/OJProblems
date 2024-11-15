// problem statement:

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 4e5 + 10;

using Dot = pair<int, int>;
int n;
Dot dot[MAXN], res[MAXN];

long long getDisSquare(Dot a, Dot b) {
    return 1LL * (a.first - b.first) * (a.first - b.first) +
           1LL * (a.second - b.second) * (a.second - b.second);
}

long long closestDistance(int l, int r) {
    if (r - l + 1 == 2) {
        if (dot[l].second > dot[r].second) { swap(dot[l], dot[r]); }
        return getDisSquare(dot[l], dot[r]);
    } else if (r - l + 1 == 3) {
        sort(dot + l, dot + r + 1, [](const Dot &a, const Dot &b) { return a.second < b.second; });
        return min(getDisSquare(dot[l], dot[l + 1]),
                   min(getDisSquare(dot[l], dot[r]), getDisSquare(dot[l + 1], dot[r])));
    } else {
        int mid = (l + r) >> 1;
        int tempMidFirst = dot[mid].first;
        long long dis = min(closestDistance(l, mid), closestDistance(mid + 1, r));
        int i = l, j = mid + 1, k = l;
        while (i <= mid || j <= r) {
            if (j > r || (i <= mid && dot[i].second < dot[j].second)) {
                res[k++] = dot[i++];
            } else {
                res[k++] = dot[j++];
            }
        }
        for (int i = l; i <= r; i++) { dot[i] = res[i]; }
        vector<Dot> res;
        long long tempDis = sqrt(dis) + 1;
        for (int i = l; i <= r; i++) {
            if (abs(dot[i].first - tempMidFirst) < tempDis) { res.push_back(dot[i]); }
        }
        for (int i = 0; i < res.size(); i++) {
            for (int j = i + 1; j < res.size(); j++) {
                if (res[j].second - res[i].second >= tempDis) { break; }
                dis = min(dis, getDisSquare(res[i], res[j]));
                tempDis = sqrt(dis) + 1;
            }
        }
        return dis;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) { cin >> dot[i].first >> dot[i].second; }
    sort(dot + 1, dot + 1 + n);
    cout << closestDistance(1, n) << endl;
    return 0;
}
