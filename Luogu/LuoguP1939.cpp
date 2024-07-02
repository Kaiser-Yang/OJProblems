// problem statement: https://www.luogu.com.cn/problem/P1939

#include <bits/stdc++.h>

constexpr long long MOD = 1e9 + 7;

using namespace std;

struct matrix {
    size_t row, column;
    matrix(size_t row, size_t column) : row(row), column(column), data(row, vector<long long>(column)) {}
    matrix(const initializer_list<initializer_list<long long>> &init) : row(init.size()), column(init.begin()->size()) {
        data.resize(row);
        size_t i = 0;
        for (const auto &row_data : init) {
            data[i].resize(column);
            size_t j = 0;
            for (const auto &val : row_data) {
                data[i][j++] = val;
            }
            i++;
        }
    }
    long long & get(size_t i, size_t j) {
        return data[i][j];
    }
    const long long & get(size_t i, size_t j) const {
        return data[i][j];
    }
    matrix operator * (const matrix &b) {
        matrix c(row, b.column);
        for (size_t i = 0; i < row; i++) {
            for (size_t j = 0; j < b.column; j++) {
                for (size_t k = 0; k < column; k++) {
                    c.get(i, j) = (c.get(i, j) + get(i, k) * b.get(k, j) % MOD) % MOD;
                }
            }
        }
        return c;
    }
    matrix quick_pow(size_t n) const {
        matrix res(row, column);
        for (size_t i = 0; i < row; i++) {
            res.get(i, i) = 1;
        }
        matrix a = *this;
        while (n) {
            if (n & 1) {
                res = res * a;
            }
            a = a * a;
            n >>= 1;
        }
        return res;
    }
    vector<vector<long long>> data;
};

int t, x;

const matrix init {
    {1, 0, 1},
    {1, 0, 0},
    {0, 1, 0}
};

int main() {
    ios::sync_with_stdio(false);
    cin >> t;
    while (t--) {
        cin >> x;
        if (x <= 3) { cout << 1 << '\n'; continue; }
        cout << (init.quick_pow(x - 3) * matrix({{1}, {1}, {1}})).get(0, 0) << '\n';
    }
    return 0;
}
