// problem statement: https://csacademy.com/ieeextreme-practice/task/queries

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;
constexpr int BLOCK_SIZE = 600;

int n, q;
int p[MAXN], inv_p[MAXN];

inline int block_start(int id) { return id * BLOCK_SIZE + 1; }
inline int block_end(int id) { return min((id + 1) * BLOCK_SIZE, n) + 1; }
inline int block_id(int x) { return (x - 1) / BLOCK_SIZE; }

struct {
    long long value[MAXN], sum[MAXN / BLOCK_SIZE + 10], lazy[MAXN / BLOCK_SIZE + 10];

    void update(int l, int r, long long c) {
        int block_l = block_id(l), block_r = block_id(r);
        if (block_l == block_r) {
            for (int i = l; i <= r; i++) { value[i] += c; }
            sum[block_l] += (r - l + 1) * c;
        } else {
            for (int i = l; i < block_end(block_l); i++) { value[i] += c; }
            sum[block_l] += (block_end(block_l) - l) * c;
            for (int i = block_l + 1; i < block_r; i++) { lazy[i] += c; }
            for (int i = block_start(block_r); i <= r; i++) { value[i] += c; }
            sum[block_r] += (r - block_start(block_r) + 1) * c;
        }
    }

    long long query(int l, int r) {
        long long res = 0;
        int block_l = block_id(l), block_r = block_id(r);
        if (block_l == block_r) {
            for (int i = l; i <= r; i++) { res += value[i] + lazy[block_l]; }
        } else {
            for (int i = l; i < block_end(block_l); i++) { res += value[i] + lazy[block_l]; }
            for (int i = block_l + 1; i < block_r; i++) { res += sum[i] + lazy[i] * BLOCK_SIZE; }
            for (int i = block_start(block_r); i <= r; i++) { res += value[i] + lazy[block_r]; }
        }
        return res;
    }

    long long query(int p) { return value[p] + lazy[block_id(p)]; }
} ori, perm;

long long ori_sum[MAXN / BLOCK_SIZE + 10], perm_sum[MAXN / BLOCK_SIZE + 10];
int ori_cnt[MAXN / BLOCK_SIZE + 10][MAXN], perm_cnt[MAXN / BLOCK_SIZE + 10][MAXN];

enum { ORI_ADD, PERM_ADD, ORI_QUERY, PERM_QUERY };

template <typename T>
void read(T &val) {
    val = 0;
    T flag = 1;
    char c;
    do {
        c = getchar();
        if (c == '-') { flag = -1; }
    } while (!isdigit(c));
    do { val = val * 10 + c - '0'; } while (isdigit(c = getchar()));
    val *= flag;
}

template <typename T>
void write(T val) {
    if (val < 0) {
        putchar('-');
        val = -val;
    }
    char buf[20];
    int p = 0;
    do {
        buf[p++] = val % 10 + '0';
        val /= 10;
    } while (val);
    while (p--) { putchar(buf[p]); }
}

int main() {
    read(n), read(q);
    for (int i = 1; i <= n; i++) {
        read(p[i]);
        inv_p[p[i]] = i;
    }
    for (int i = 0; i <= block_id(n); i++) {
        int l = block_start(i), r = block_end(i);
        for (int j = l; j < r; j++) { perm_cnt[i][p[j]]++; }
        for (int j = 1; j <= n; j++) {
            perm_cnt[i][j] += perm_cnt[i][j - 1];
            if (l <= p[j] && p[j] < r) { ori_cnt[i][j]++; }
            ori_cnt[i][j] += ori_cnt[i][j - 1];
        }
    }
    int op, l, r;
    long long c;
    while (q--) {
        read(op);
        if (op == ORI_ADD || op == PERM_ADD) {
            read(l), read(r), read(c);
            if (op == ORI_ADD) {
                ori.update(l, r, c);
                for (int i = 0; i <= block_id(n); i++) {
                    perm_sum[i] += c * (perm_cnt[i][r] - perm_cnt[i][l - 1]);
                }
            } else {
                perm.update(l, r, c);
                for (int i = 0; i <= block_id(n); i++) {
                    ori_sum[i] += c * (ori_cnt[i][r] - ori_cnt[i][l - 1]);
                }
            }
        } else {
            read(l), read(r);
            long long ans = 0;
            int block_l = block_id(l), block_r = block_id(r);
            if (op == ORI_QUERY) {
                ans = ori.query(l, r);
                if (block_l == block_r) {
                    for (int i = l; i <= r; i++) { ans += perm.query(inv_p[i]); }
                } else {
                    for (int i = l; i < block_end(block_l); i++) { ans += perm.query(inv_p[i]); }
                    for (int i = block_l + 1; i < block_r; i++) { ans += ori_sum[i]; }
                    for (int i = block_start(block_r); i <= r; i++) { ans += perm.query(inv_p[i]); }
                }
            } else {
                ans = perm.query(l, r);
                if (block_l == block_r) {
                    for (int i = l; i <= r; i++) { ans += ori.query(p[i]); }
                } else {
                    for (int i = l; i < block_end(block_l); i++) { ans += ori.query(p[i]); }
                    for (int i = block_l + 1; i < block_r; i++) { ans += perm_sum[i]; }
                    for (int i = block_start(block_r); i <= r; i++) { ans += ori.query(p[i]); }
                }
            }
            write(ans);
            putchar('\n');
        }
    }
    return 0;
}
