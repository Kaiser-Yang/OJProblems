// problem statement: https://csacademy.com/ieeextreme-practice/task/corporation

#include <bits/stdc++.h>

#include <cstdio>

using namespace std;

constexpr int MAXN = 2e5 + 10;
constexpr int SQRT_MAXN = 1e3 + 10;

int n, q;
int block_size, block_cnt;
long long salary[MAXN], happiness[MAXN], sum_salary[SQRT_MAXN], sum_happiness[SQRT_MAXN],
    lazy_salary[SQRT_MAXN], lazy_happiness[SQRT_MAXN];
bool all_same[SQRT_MAXN];

enum OP_TYPE { SET, INCREASE_OR_DECREASE, QUEYR_AVG_SALARY, QUERY_AVG_HAPPINESS };

inline int block_start(int i) { return i * block_size; }

inline int block_end(int i) { return min(n, (i + 1) * block_size); }

void build_block(int id) {
    int l = block_start(id), r = block_end(id);
    sum_salary[id] = 0;
    sum_happiness[id] = 0;
    lazy_salary[id] = 0;
    lazy_happiness[id] = 0;
    all_same[id] = true;
    for (int i = l; i < r; i++) {
        sum_salary[id] += salary[i];
        sum_happiness[id] += happiness[i];
        if (i > l && salary[i] != salary[i - 1]) { all_same[id] = false; }
    }
}

void init_block() {
    block_size = sqrt(n);
    block_cnt = (n + block_size - 1) / block_size;
    for (int i = 0; i < block_cnt; i++) { build_block(i); }
}

void push(int id) {
    int start = block_start(id), end = block_end(id);
    for (int i = start; i < end; i++) { happiness[i] += lazy_happiness[id]; }
    lazy_happiness[id] = 0;
    if (all_same[id]) {
        for (int i = start; i < end; i++) { salary[i] = sum_salary[id] / (end - start); }
        lazy_salary[id] = 0;
    } else {
        for (int i = start; i < end; i++) { salary[i] += lazy_salary[id]; }
        lazy_salary[id] = 0;
    }
}

long long query(int l, int r, OP_TYPE op) {
    long long sum = 0;
    int block_l = l / block_size, block_r = r / block_size;
    if (block_l == block_r) {
        push(block_l);
        for (int i = l; i <= r; i++) {
            sum += (op == QUERY_AVG_HAPPINESS ? happiness[i] : salary[i]);
        }
    } else {
        push(block_l);
        for (int i = l; i < block_end(block_l); i++) {
            sum += (op == QUERY_AVG_HAPPINESS ? happiness[i] : salary[i]);
        }
        for (int i = block_l + 1; i < block_r; i++) {
            sum += (op == QUERY_AVG_HAPPINESS ? sum_happiness[i] : sum_salary[i]);
        }
        push(block_r);
        for (int i = block_start(block_r); i <= r; i++) {
            sum += (op == QUERY_AVG_HAPPINESS ? happiness[i] : salary[i]);
        }
    }
    return sum;
}

void update(int l, int r, long long c, OP_TYPE op) {
    int block_l = l / block_size, block_r = r / block_size;
    if (op == SET) {
        if (block_l == block_r) {
            push(block_l);
            for (int i = l; i <= r; i++) {
                if (c > salary[i]) {
                    happiness[i]++;
                } else if (c < salary[i]) {
                    happiness[i]--;
                }
                salary[i] = c;
            }
            build_block(block_l);
        } else {
            push(block_l);
            for (int i = l; i < block_end(block_l); i++) {
                if (c > salary[i]) {
                    happiness[i]++;
                } else if (c < salary[i]) {
                    happiness[i]--;
                }
                salary[i] = c;
            }
            build_block(block_l);
            for (int i = block_l + 1; i < block_r; i++) {
                int start = block_start(i), end = block_end(i);
                if (all_same[i]) {
                    if (c > sum_salary[i] / (end - start)) {
                        lazy_happiness[i]++;
                        sum_happiness[i] += end - start;
                    } else if (c < sum_salary[i] / (end - start)) {
                        lazy_happiness[i]--;
                        sum_happiness[i] -= end - start;
                    }
                    lazy_salary[i] = 0;
                    sum_salary[i] = c * (end - start);
                } else {
                    push(i);
                    for (int j = start; j < end; j++) {
                        if (c > salary[j]) {
                            happiness[j]++;
                        } else if (c < salary[j]) {
                            happiness[j]--;
                        }
                        salary[j] = c;
                    }
                    build_block(i);
                }
            }
            push(block_r);
            for (int i = block_start(block_r); i <= r; i++) {
                if (c > salary[i]) {
                    happiness[i]++;
                } else if (c < salary[i]) {
                    happiness[i]--;
                }
                salary[i] = c;
            }
            build_block(block_r);
        }
    } else {
        if (block_l == block_r) {
            push(block_l);
            for (int i = l; i <= r; i++) {
                if (c > 0) {
                    happiness[i]++;
                } else if (c < 0) {
                    happiness[i]--;
                }
                salary[i] += c;
            }
            build_block(block_l);
        } else {
            push(block_l);
            for (int i = l; i < block_end(block_l); i++) {
                if (c > 0) {
                    happiness[i]++;
                } else if (c < 0) {
                    happiness[i]--;
                }
                salary[i] += c;
            }
            build_block(block_l);
            for (int i = block_l + 1; i < block_r; i++) {
                int start = block_start(i), end = block_end(i);
                if (c > 0) {
                    lazy_happiness[i]++;
                    sum_happiness[i] += end - start;
                } else if (c < 0) {
                    lazy_happiness[i]--;
                    sum_happiness[i] -= end - start;
                }
                sum_salary[i] += c * (end - start);
                lazy_salary[i] += c;
            }
            push(block_r);
            for (int i = block_start(block_r); i <= r; i++) {
                if (c > 0) {
                    happiness[i]++;
                } else if (c < 0) {
                    happiness[i]--;
                }
                salary[i] += c;
            }
            build_block(block_r);
        }
    }
}

long long gcd(long long a, long long b) { return b == 0 ? a : gcd(b, a % b); }

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
    if (val == 0) {
        putchar('0');
        return;
    }
    if (val < 0) {
        putchar('-');
        val = -val;
    }
    char buf[20];
    int p = 0;
    while (val) {
        buf[p++] = val % 10 + '0';
        val /= 10;
    }
    for (int i = p - 1; i >= 0; i--) { putchar(buf[i]); }
}

int main() {
    read(n), read(q);
    for (int i = 0; i < n; i++) { read(salary[i]); }
    init_block();
    int op, l, r;
    long long c;
    while (q--) {
        read(op);
        if (op == SET || op == INCREASE_OR_DECREASE) {
            read(l), read(r), read(c);
            l--;
            r--;
            update(l, r, c, (OP_TYPE)op);
        } else {
            read(l), read(r);
            l--;
            r--;
            long long sum = query(l, r, (OP_TYPE)op);
            long long len = r - l + 1;
            long long g = gcd(abs(sum), len);
            sum /= g;
            len /= g;
            write(sum);
            putchar('/');
            write(len);
            putchar('\n');
        }
    }
    return 0;
}
