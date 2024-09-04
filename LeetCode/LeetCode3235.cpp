// problem statement: https://leetcode.cn/problems/check-if-the-rectangle-corner-is-reachable/

#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
    class union_find_set {
    public:
        union_find_set(int n) : h(n) { iota(h.begin(), h.end(), 0); }
        int find(int x) { return x == h[x] ? x : h[x] = find(h[x]); }
        bool same(int i, int j) { return find(i) == find(j); }
        void merge(int i, int j) { h[find(i)] = find(j); }

    private:
        vector<int> h;
    };
    enum DIRECTION { UP, DOWN, LEFT, RIGHT };

public:
    bool canReachCorner(int rect_x, int rect_y, vector<vector<int>> &circles) {
        int n = circles.size();
        auto get_square_dis = [&](int x1, int y1, int x2, int y2) -> long long {
            return (long long)(x1 - x2) * (x1 - x2) + (long long)(y1 - y2) * (y1 - y2);
        };
        auto intersect_or_touch = [&](int i, int j) {
            if (i < n && j < n) {
                auto square_dis =
                    get_square_dis(circles[i][0], circles[i][1], circles[j][0], circles[j][1]);
                if (square_dis >
                    (long long)(circles[i][2] + circles[j][2]) * (circles[i][2] + circles[j][2])) {
                    return false;
                }
                return 1LL * circles[i][0] * circles[j][2] + 1LL * circles[j][0] * circles[i][2] <
                           1LL * (circles[i][2] + circles[j][2]) * rect_x &&
                       1LL * circles[i][1] * circles[j][2] + 1LL * circles[j][1] * circles[i][2] <
                           1LL * (circles[i][2] + circles[j][2]) * rect_y;
            }
            if (i >= n && j >= n) { return false; }
            if (i >= n) { swap(i, j); }
            j -= n;
            long long h = 0, l1 = 0, l2 = 0;
            int p1_x = 0, p1_y = 0, p2_x = 0, p2_y = 0, p_min = 0, p_max = 0;
            switch (j) {
                case UP:
                    h = abs(1LL * circles[i][1] - rect_y) * abs(1LL * circles[i][1] - rect_y);
                    p1_x = 0, p1_y = rect_y;
                    p2_x = rect_x, p2_y = rect_y;
                    p_min = min(p1_x, p2_x), p_max = max(p1_x, p2_x);
                    break;
                case DOWN:
                    h = abs(1LL * circles[i][1]) * abs(1LL * circles[i][1]);
                    p1_x = 0, p1_y = 0;
                    p2_x = rect_x, p2_y = 0;
                    p_min = min(p1_x, p2_x), p_max = max(p1_x, p2_x);
                    break;
                case LEFT:
                    h = abs(1LL * circles[i][0]) * abs(1LL * circles[i][0]);
                    p1_x = 0, p1_y = rect_y;
                    p2_x = 0, p2_y = 0;
                    p_min = min(p1_y, p2_y), p_max = max(p1_y, p2_y);
                    break;
                case RIGHT:
                    h = abs(1LL * circles[i][0] - rect_x) * abs(1LL * circles[i][0] - rect_x);
                    p1_x = rect_x, p1_y = rect_y;
                    p2_x = rect_x, p2_y = 0;
                    p_min = min(p1_y, p2_y), p_max = max(p1_y, p2_y);
                    break;
            }
            l1 = get_square_dis(circles[i][0], circles[i][1], p1_x, p1_y);
            l2 = get_square_dis(circles[i][0], circles[i][1], p2_x, p2_y);
            bool center_inside_rect = circles[i][0] >= 0 && circles[i][0] <= rect_x &&
                                      circles[i][1] >= 0 && circles[i][1] <= rect_y;
            if (circles[i][j / 2] >= p_min && circles[i][j / 2] <= p_max) {
                return center_inside_rect ? h <= 1LL * circles[i][2] * circles[i][2] :
                                            h < 1LL * circles[i][2] * circles[i][2];
            }
            return center_inside_rect ? min(l1, l2) <= 1LL * circles[i][2] * circles[i][2] :
                                        min(l1, l2) < 1LL * circles[i][2] * circles[i][2];
        };
        for (auto circle : circles) {
            if (get_square_dis(circle[0], circle[1], 0, 0) <= 1LL * circle[2] * circle[2] ||
                get_square_dis(circle[0], circle[1], rect_x, rect_y) <=
                    1LL * circle[2] * circle[2]) {
                return false;
            }
        }
        union_find_set ufs(n + 4);
        for (int i = 0; i < n + 4; i++) {
            for (int j = i + 1; j < n + 4; j++) {
                if (intersect_or_touch(i, j)) { ufs.merge(i, j); }
            }
        }
        return !ufs.same(n + UP, n + DOWN) && !ufs.same(n + LEFT, n + RIGHT) &&
               !ufs.same(n + UP, n + RIGHT) && !ufs.same(n + DOWN, n + LEFT);
    }
};
