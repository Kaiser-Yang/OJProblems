// problem statement: https://www.luogu.com.cn/problem/P3865

#include <bits/stdc++.h>

constexpr int MAXN= 1e5 + 10;

using namespace std;

int m, l, r;

int read() {
    int x = 0, f = 1;
    char ch = 0;
    do {
        ch = getchar();
        if (ch == '-') { f = -1; }
    } while (ch < '0' || ch > '9');
    do {
        x = x * 10 + ch - '0';
        ch = getchar();
    } while (ch >= '0' && ch <= '9');
    return x * f;
}

template <size_t MAXN, size_t LOG_MAXN>
struct sparse_table {

    void init() {
        for (int i = 1; i <= n; i++) {
            max_value[i][0] = a[i];
        }
        for (int j = 1; j < LOG_MAXN; j++) {
            for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                max_value[i][j] = max(max_value[i][j - 1], max_value[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query_max(int l, int r) {
        int k = log2(r - l + 1);
        return max(max_value[l][k], max_value[r - (1 << k) + 1][k]);
    }

    int n;
    int a[MAXN];
    int max_value[MAXN][LOG_MAXN];
};

sparse_table<MAXN, 20> st;

int main() {
    st.n = read(), m = read();
    for (int i = 1; i <= st.n; i++) { st.a[i] = read(); }
    st.init();
    for (int i = 0; i < m; i++) {
        l = read(), r = read();
        cout << st.query_max(l, r) << '\n';
    }
    return 0;
}
