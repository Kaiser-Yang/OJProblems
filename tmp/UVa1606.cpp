/*
    You are given n dots on the plane, and they are either black or white.
You can use one staight line to seperate those dots into parts, you need
calculate the maximum sum of the number of one part black dots and the
number of the other part white dots.
*/
#include <bits/stdc++.h>

using namespace std;

struct TwoDVector {
    int first, second;
    double angle;
};

TwoDVector dot2Vector(TwoDVector &dot1, TwoDVector &dot2) {
    return {dot2.first - dot1.first, dot2.second - dot1.second};
}

int crossProduct(TwoDVector &lhs, TwoDVector &rhs)
{
    return lhs.first * rhs.second - lhs.second * rhs.first;
}

int scanArea(int index, vector<TwoDVector> &dot, vector<int> &color, vector<TwoDVector> &newDot)
{
    TwoDVector origin = dot[index];
    int n = 0;
    for (int i = 0; i < dot.size(); i++) {
        if (i == index) { continue; }
        newDot[n++] = dot2Vector(origin, dot[i]);
        if (color[i] != 0) {
            newDot[n - 1].first *= -1;
            newDot[n - 1].second *= -1;
        }
        newDot[n - 1].angle = atan2(newDot[n - 1].second, newDot[n - 1].first);
    }
    sort(newDot.begin(), newDot.end(), [](TwoDVector &lhs, TwoDVector &rhs) -> bool {
        return lhs.angle < rhs.angle;
    });
    int left = 0, right = 0;
    int nowAns = 2, ans = 1;
    while (left < n) {
        if ((right + 1) % n == left) {
            right = left;
            nowAns++;
        }
        while ((right + 1) % n != left && crossProduct(newDot[left], newDot[(right + 1) % n]) >= 0) {
            right = (right + 1) % n;
            nowAns++;
        }
        ans = max(ans, nowAns);
        left++;
        nowAns--;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int n, ans;
    vector<int> color;
    vector<TwoDVector> dot, newDot;
    while (cin >> n && n != 0) {
        ans = 0;
        dot.resize(n);
        color.resize(n);
        newDot.resize(n - 1);
        for (int i = 0; i < n; i++) {
            cin >> dot[i].first >> dot[i].second >> color[i];
        }
        for (int i = 0; i < n; i++) {
            ans = max(ans, scanArea(i, dot, color, newDot));
        }
        cout << ans << endl;
    }
    return 0;
}