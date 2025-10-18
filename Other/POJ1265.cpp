// problem statement: http://poj.org/problem?id=1265

#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <ios>
#include <iostream>
#include <vector>

template <typename T, typename R>
static R polygon_area(const std::vector<std::pair<T, T> > &points) {
    R area = 0;
    for (int i = 0; i < points.size(); i++) {
        int j = (i + 1) % points.size();
        area += (R)points[i].first * points[j].second;
        area -= (R)points[i].second * points[j].first;
    }
    return std::abs(area) / 2;
}

template <typename T>
static T gcd(T a, T b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout << std::fixed << std::setprecision(1);
    int T;
    std::cin >> T;
    for (int t = 1; t <= T; t++) {
        int n;
        std::cin >> n;
        std::vector<std::pair<int, int> > points(n);
        int x = 0, y = 0;
        for (int i = 0; i < n; i++) {
            std::cin >> points[i].first >> points[i].second;
            x += points[i].first;
            y += points[i].second;
            points[i].first = x;
            points[i].second = y;
        }
        double area = polygon_area<int, double>(points);
        int points_on_edge = 0;
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            int dx = std::abs(points[i].first - points[j].first);
            int dy = std::abs(points[i].second - points[j].second);
            points_on_edge += gcd(dx, dy);
        }
        // S = I + B/2 - 1
        // I = S - B/2 + 1
        int points_inside = round(area - points_on_edge / 2. + 1);
        std::cout << "Scenario #" << t << ":\n";
        std::cout << points_inside << ' ' << points_on_edge << ' ' << area << '\n';
        std::cout << '\n';
    }
    return 0;
}
