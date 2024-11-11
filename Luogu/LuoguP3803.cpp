// problem statement: https://www.luogu.com.cn/problem/P3803

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e6 + 10;
constexpr int MAXM = 1e6 + 10;

complex<double> a[(MAXN + MAXM) << 1], b[(MAXN + MAXM) << 1];

namespace fft {
// the number of points should be 2^k
int actual_number_of_points;
vector<int> pos;

void init(int number_of_points) {
    actual_number_of_points = 1;
    while (actual_number_of_points < number_of_points) { actual_number_of_points <<= 1; }
    pos.clear();
    pos.reserve(actual_number_of_points);
    pos.push_back(0);
    for (int w = 1, d = actual_number_of_points >> 1; w <= actual_number_of_points;
         w <<= 1, d >>= 1) {
        for (int j = 0; j < w; j++) { pos.push_back(pos[j] | d); }
    }
}

// a is the coefficient of the polynomial
// after fft a will be the value of the polynomial at the point w^0, w^1, w^2, ..., w^(n-1)
void fft(complex<double> *a) {
    for (int i = 1; i < actual_number_of_points; i++) {
        if (i < pos[i]) { swap(a[i], a[pos[i]]); }
    }
    for (int len = 2; len <= actual_number_of_points; len <<= 1) {
        int m = len >> 1;
        complex<double> wn(cos(2 * M_PI / len), sin(2 * M_PI / len));
        for (int i = 0; i < actual_number_of_points; i += len) {
            complex<double> w(1, 0);
            for (int j = 0; j < m; j++) {
                complex<double> x = a[i + j], y = w * a[i + j + m];
                a[i + j] = x + y;
                a[i + j + m] = x - y;
                w *= wn;
            }
        }
    }
}

// a is the value of the polynomial at the point w^0, w^1, w^2, ..., w^(n-1)
// after ifft a will be the coefficient of the polynomial
void ifft(complex<double> *a) {
    fft(a);
    reverse(a + 1, a + actual_number_of_points);
    for (int i = 0; i < actual_number_of_points; i++) { a[i] /= actual_number_of_points; }
}
}  // namespace fft

int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i <= n; i++) {
        int x;
        cin >> x;
        a[i] = x;
    }
    for (int i = 0; i <= m; i++) {
        int x;
        cin >> x;
        b[i] = x;
    }
    fft::init(n + m + 1);
    fft::fft(a);
    fft::fft(b);
    // note that after fft, there should be fft::actual_number_of_points points
    // rather than n + m + 1 points
    for (int i = 0; i <= fft::actual_number_of_points; i++) { a[i] *= b[i]; }
    fft::ifft(a);
    for (int i = 0; i <= n + m; i++) { cout << (int)(a[i].real() + 0.5) << " "; }
    return 0;
}
