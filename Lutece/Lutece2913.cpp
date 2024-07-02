#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct Matrix {
    int m, n;
    vector<vector<T>> a;
    Matrix(int m, int n) : m(m), n(n) { a.resize(m, vector<T>(n)); }
    Matrix<T> operator-(const Matrix<T> &other) {
        auto res = *this;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) { res.a[i][j] -= other.a[i][j]; }
        }
        return res;
    }
};

template <typename T>
ostream &operator<<(ostream &os, const Matrix<T> &matrix) {
    for (int i = 0; i < matrix.m; i++, cout << endl) {
        for (int j = 0; j < matrix.n; j++) { cout << matrix.a[i][j] << " "; }
    }
    return os;
}

int m, n, k;

template <typename T>
void inputMatrix(int m, int n, Matrix<T> &res) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) { cin >> res.a[i][j]; }
    }
}

template <typename T>
long long different(Matrix<T> &a, Matrix<T> &b) {
    auto delta    = a - b;
    long long sum = 0;
    for (int i = 0; i < delta.m; i++) {
        long long now = 0;
        for (int j = 0; j < delta.n; j++) { now += delta.a[i][j]; }
        if (now != 0) { delta.a[i + k][0] += now; }
        sum += abs(now);
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> m >> n >> k;
    Matrix<long long> a(m, n), b(m, n), c(m, n);
    inputMatrix(m, n, a);
    inputMatrix(m, n, b);
    inputMatrix(m, n, c);
    if (different(a, b)) {
        if (different(a, c)) {
            cout << "1 " << different(a, b) << endl;
        } else {
            cout << "2 " << different(a, b) << endl;
        }
    } else {
        cout << "3 " << different(a, c) << endl;
    }
    return 0;
}