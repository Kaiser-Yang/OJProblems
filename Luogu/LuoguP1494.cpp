// problem statement:

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 5e4 + 10;
constexpr int MAXM = 5e4 + 10;

int N, M, u, v;
long long caseNumber;
int color[MAXN], cnt[MAXN], pos[MAXN];

struct Query {
    int l, r, id;
    long long numerator, denominator;
} query[MAXM];

template <class T>
T gcd(T a, T b) {
    return b == 0 ? a : gcd(b, a % b);
}

void add(int x) {
    caseNumber += 2LL * cnt[color[x]];
    cnt[color[x]]++;
}

void del(int x) {
    cnt[color[x]]--;
    caseNumber -= 2LL * cnt[color[x]];
}

int main() {
    ios::sync_with_stdio(false);
    cin >> N >> M;
    int sqrtN = sqrt(N);
    for (int i = 1; i <= N; i++) {
        cin >> color[i];
        pos[i] = i / sqrtN;
    }
    for (int i = 1; i <= M; i++) {
        cin >> u >> v;
        query[i].l = u;
        query[i].r = v;
        query[i].id = i;
    }
    sort(query + 1, query + 1 + M, [](const Query &lhs, const Query &rhs) {
        if (pos[lhs.l] == pos[rhs.l]) { return lhs.r < rhs.r; }
        return lhs.l < rhs.l;
    });
    int l = 1, r = 1;
    cnt[color[1]] = 1;
    for (int i = 1; i <= M; i++) {
        while (l < query[i].l) {
            del(l);
            l++;
        }
        while (l > query[i].l) {
            l--;
            add(l);
        }
        while (r < query[i].r) {
            r++;
            add(r);
        }
        while (r > query[i].r) {
            del(r);
            r--;
        }
        if (l == r) {
            query[i].numerator = 0;
            query[i].denominator = 1;
        } else {
            query[i].numerator = caseNumber;
            query[i].denominator = 1LL * (r - l + 1) * (r - l);
            long long g = gcd(query[i].numerator, query[i].denominator);
            query[i].numerator /= g;
            query[i].denominator /= g;
        }
        // cout << l << " " << r << " " << caseNumber << endl;
    }
    sort(query + 1, query + 1 + M, [](const Query &lhs, const Query &rhs) {
        return lhs.id < rhs.id;
    });
    for (int i = 1; i <= M; i++) {
        cout << query[i].numerator << "/" << query[i].denominator << endl;
    }
    return 0;
}
