// problem statement:

#include <bits/stdc++.h>

using namespace std;

using Dot = pair<int, int>;

struct Rectangle {
    bool arranged = false;
    int leftRange, rightRange, upRange, downRange;
};

int n, k, ans = std::numeric_limits<int>::max();
vector<Dot> dot;
vector<Rectangle> rect;

bool dotInRectangle(const Dot &dot, const Rectangle &rect) {
    return dot.first >= rect.leftRange && dot.first <= rect.rightRange &&
           dot.second >= rect.downRange && dot.second <= rect.upRange;
}

bool overLap(const Rectangle &rect1, const Rectangle &rect2) {
    return dotInRectangle(Dot{rect1.leftRange, rect1.upRange}, rect2) ||
           dotInRectangle(Dot{rect1.leftRange, rect1.downRange}, rect2) ||
           dotInRectangle(Dot{rect1.rightRange, rect1.upRange}, rect2) ||
           dotInRectangle(Dot{rect1.rightRange, rect1.downRange}, rect2);
}

int computeTotArea() {
    int res = 0;
    for (int i = 0; i < k; i++) {
        if (!rect[i].arranged) { continue; }
        for (int j = i + 1; j < k; j++) {
            if (!rect[j].arranged) { continue; }
            if (overLap(rect[i], rect[j])) { return -1; }
        }
        res += (rect[i].rightRange - rect[i].leftRange) * (rect[i].upRange - rect[i].downRange);
    }
    return res;
}

void dfs(int depth) {
    int nowAns = computeTotArea();
    if (nowAns < 0 || nowAns >= ans) { return; }  // < 0 means overlap
    if (depth == n) {
        ans = min(ans, nowAns);
        return;
    }
    for (int i = 0; i < k; i++) {
        Rectangle temp = rect[i];
        if (rect[i].arranged) {
            rect[i].leftRange = min(rect[i].leftRange, dot[depth].first);
            rect[i].rightRange = max(rect[i].rightRange, dot[depth].first);
            rect[i].upRange = max(rect[i].upRange, dot[depth].second);
            rect[i].downRange = min(rect[i].downRange, dot[depth].second);
        } else {
            rect[i].arranged = true;
            rect[i].leftRange = rect[i].rightRange = dot[depth].first;
            rect[i].upRange = rect[i].downRange = dot[depth].second;
        }
        dfs(depth + 1);
        rect[i] = temp;
    }
}

int main() {
    cin >> n >> k;
    dot.resize(n);
    rect.resize(k);
    for (int i = 0; i < n; i++) { cin >> dot[i].first >> dot[i].second; }
    dfs(0);
    cout << ans << endl;
    return 0;
}