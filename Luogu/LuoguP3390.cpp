// problem statement: https://www.luogu.com.cn/problem/P3390

#include <bits/stdc++.h>

constexpr int MOD = 1e9 + 7;

using namespace std;

int n;
size_t k;
using matrix = vector<vector<long long>>;
matrix a;

void operator*= (matrix &a, const matrix &b) {
    matrix res = matrix(a.size(), vector<long long>(b[0].size()));
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b[0].size(); j++) {
            for (int k = 0; k < a[0].size(); k++) {
                res[i][j] = (res[i][j] + a[i][k] * b[k][j] % MOD) % MOD;
            }
        }
    }
    a = std::move(res);
}

void quick_pow(matrix &a, size_t b) {
    matrix res = matrix(a.size(), vector<long long>(a.size()));
    for (int i = 0; i < a.size(); i++) { res[i][i] = 1; }
    while (b > 0) {
        if (b & 1) { res *= a; }
        a *= a;
        b >>= 1;
    }
    a = std::move(res);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    a.resize(n, vector<long long>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) { cin >> a[i][j]; }
    }
    quick_pow(a, k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) { cout << a[i][j] << (j == n - 1 ? '\n' : ' '); }
    }
    return 0;
}
