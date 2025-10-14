// problem statement: https://www.luogu.com.cn/problem/P10505

#include <algorithm>
#include <iostream>
#include <vector>

using i64 = int64_t;

int main() {
    int n, k;
    while (std::cin >> n >> k) {
        if (n == 0 && k == 0) { break; }
        k = n - k;
        std::vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) { std::cin >> a[i]; }
        for (int i = 0; i < n; i++) { std::cin >> b[i]; }
        double left = 0, right = 1, ans = 0.;
        auto check = [&](double x) {
            std::vector<double> score(n);
            for (int i = 0; i < n; i++) { score[i] = a[i] - x * b[i]; }
            std::nth_element(
                score.begin(), score.begin() + k - 1, score.end(), std::greater<double>());
            double sum = 0;
            for (int i = 0; i < k; i++) { sum += score[i]; }
            if (sum >= 0) {
                return true;
            } else {
                return false;
            }
        };
        while (right - left > 1e-6) {
            double mid = (left + right) / 2;
            if (check(mid)) {
                ans = mid;
                left = mid;
            } else {
                right = mid;
            }
        }
        if (ans * 100 - int(ans * 100) >= 0.5) {
            std::cout << int(ans * 100 + 1) << '\n';
        } else {
            std::cout << int(ans * 100) << '\n';
        }
    }
    return 0;
}
