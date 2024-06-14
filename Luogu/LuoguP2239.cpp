// problem statement: https://www.luogu.com.cn/problem/P2239

#include <bits/stdc++.h>

using namespace std;

int n, x, y, ans;

using Node = pair<int, int>;

bool dotInEdge(const Node &a, const Node &lineBegin, const Node &lineEnd)
{
    return a.first >= lineBegin.first && a.first <= lineEnd.first &&
           a.second >= lineBegin.second && a.second <= lineEnd.second;
}

bool dotInRectangleEdge(const Node &a, const Node &leftTop, const Node &rightBottom)
{
    return dotInEdge(a, leftTop, {leftTop.first, rightBottom.second}) || 
           dotInEdge(a, {rightBottom.first, leftTop.second}, rightBottom) || 
           dotInEdge(a, leftTop, {rightBottom.first, leftTop.second}) || 
           dotInEdge(a, {leftTop.first, rightBottom.second}, rightBottom);
}

int main()
{
	ios::sync_with_stdio(false);
    cin >> n >> x >> y;
    
    for (int i = 1; i <= n; i++) {
        if (!dotInRectangleEdge({x, y}, {i, i}, {n - i + 1, n - i + 1})) { 
            ans += 4 * n - 8 * i + 4;
            continue;
        }
        // cout << ans << " " << i << endl;
        if (x > i) {
            ans += n - 2 * (i - 1);
            if (y < n - i + 1) { 
                ans += (n - 2 * (i - 1)) - 1;
                if (x < n - i + 1) {
                    ans += (n - 2 * (i - 1)) - 1;
                    ans += (n - i + 1) - x;
                } else {
                    ans += (n - i + 1) - y;
                }
            }
            else {
                ans += x - i;
            }
        } else { 
            ans += y - i + 1;
        }
        break;
    }
    cout << ans << endl;
	return 0;
}
