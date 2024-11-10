// problem statement:
// https://csacademy.com/ieeextreme-practice/task/this-is-not-an-optimization-problem

#include <bits/stdc++.h>

using namespace std;

// This template is copied from https://www.luogu.com.cn/article/jtrfn4yb
int mod = 1e9 + 99999;
namespace Math {
inline int pw(int base, int p, const int mod) {
    static int res;
    for (res = 1; p; p >>= 1, base = static_cast<long long>(base) * base % mod)
        if (p & 1) res = static_cast<long long>(res) * base % mod;
    return res;
}
inline int inv(int x, const int mod) { return pw(x, mod - 2, mod); }
}  // namespace Math

const int mod1 = 998244353, mod2 = 1004535809, mod3 = 469762049, G = 3;
const long long mod_1_2 = static_cast<long long>(mod1) * mod2;
const int inv_1 = Math::inv(mod1, mod2), inv_2 = Math::inv(mod_1_2 % mod3, mod3);
struct Int {
    int A, B, C;
    explicit inline Int() {}
    explicit inline Int(int __num) : A(__num), B(__num), C(__num) {}
    explicit inline Int(int __A, int __B, int __C) : A(__A), B(__B), C(__C) {}
    static inline Int reduce(const Int &x) {
        return Int(x.A + (x.A >> 31 & mod1), x.B + (x.B >> 31 & mod2), x.C + (x.C >> 31 & mod3));
    }
    inline friend Int operator+(const Int &lhs, const Int &rhs) {
        return reduce(Int(lhs.A + rhs.A - mod1, lhs.B + rhs.B - mod2, lhs.C + rhs.C - mod3));
    }
    inline friend Int operator-(const Int &lhs, const Int &rhs) {
        return reduce(Int(lhs.A - rhs.A, lhs.B - rhs.B, lhs.C - rhs.C));
    }
    inline friend Int operator*(const Int &lhs, const Int &rhs) {
        return Int(static_cast<long long>(lhs.A) * rhs.A % mod1,
                   static_cast<long long>(lhs.B) * rhs.B % mod2,
                   static_cast<long long>(lhs.C) * rhs.C % mod3);
    }
    inline int get() {
        long long x = static_cast<long long>(B - A + mod2) % mod2 * inv_1 % mod2 * mod1 + A;
        return (static_cast<long long>(C - x % mod3 + mod3) % mod3 * inv_2 % mod3 *
                    (mod_1_2 % mod) % mod +
                x) %
               mod;
    }
};

#define maxn 400010

namespace Poly {
#define N (maxn << 1)
int lim, s, rev[N];
Int Wn[N | 1];
inline void init(int n) {
    s = -1, lim = 1;
    while (lim < n) lim <<= 1, ++s;
    for (int i = 1; i < lim; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
    const Int t(Math::pw(G, (mod1 - 1) / lim, mod1),
                Math::pw(G, (mod2 - 1) / lim, mod2),
                Math::pw(G, (mod3 - 1) / lim, mod3));
    *Wn = Int(1);
    for (Int *i = Wn; i != Wn + lim; ++i) *(i + 1) = *i * t;
}
inline void NTT(Int *A, const int op = 1) {
    if (lim > N) { exit(-1); }
    for (int i = 1; i < lim; ++i)
        if (i < rev[i]) swap(A[i], A[rev[i]]);
    for (int mid = 1; mid < lim; mid <<= 1) {
        const int t = lim / mid >> 1;
        for (int i = 0; i < lim; i += mid << 1) {
            for (int j = 0; j < mid; ++j) {
                const Int W = op ? Wn[t * j] : Wn[lim - t * j];
                const Int X = A[i + j], Y = A[i + j + mid] * W;
                A[i + j] = X + Y, A[i + j + mid] = X - Y;
            }
        }
    }
    if (!op) {
        const Int ilim(Math::inv(lim, mod1), Math::inv(lim, mod2), Math::inv(lim, mod3));
        for (Int *i = A; i != A + lim; ++i) *i = (*i) * ilim;
    }
}
#undef N
}  // namespace Poly

constexpr int MAXN = 2e5 + 10;

int n;
int w[MAXN], b[MAXN], sz[MAXN];
vector<int> g[MAXN];

void dfs(int u, int par) {
    sz[u] = 1;
    for (int v : g[u]) {
        if (v == par) { continue; }
        dfs(v, u);
        b[n - sz[v]] = (b[n - sz[v]] - w[v] + mod) % mod;
        sz[u] += sz[v];
    }
    b[sz[u]] = (b[sz[u]] - w[par] + mod) % mod;
}

Int A[MAXN << 2], B[MAXN << 2];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) { cin >> w[i]; }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++) { b[n] = (b[n] + w[i]) % mod; }
    int fac = 1;
    for (int i = 0; i <= n; i++) {
        if (i != 0) { fac = (1LL * fac * i) % mod; }
        B[n - i] = Int(1LL * b[i] * fac % mod);
        A[i] = Int(Math::inv(fac, mod));
    }
    Poly::init(n + n + 2);
    Poly::NTT(A), Poly::NTT(B);
    for (int i = 0; i < Poly::lim; ++i) A[i] = A[i] * B[i];
    Poly::NTT(A, 0);
    fac = 1;
    for (int i = 1; i <= n; ++i) {
        fac = 1LL * fac * i % mod;
        cout << 1LL * A[n - i].get() * Math::inv(fac, mod) % mod << endl;
    }
    return 0;
}
