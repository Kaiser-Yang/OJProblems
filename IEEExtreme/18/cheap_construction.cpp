// problem statement: https://csacademy.com/ieeextreme-practice/task/cheap-construction

#include <bits/stdc++.h>

using namespace std;

constexpr int P = 233;
constexpr int MOD1 = 1e9 + 7, MOD2 = 19260817;
constexpr int MAXN = 5e3 + 10;

string str;
int n;
int res[MAXN], val1[MAXN], val2[MAXN], pow1[MAXN], pow2[MAXN];
unordered_map<long long, vector<int>> pos;

void hash_whole_str() {
    val1[0] = str[0] - 'a' + 1, val2[0] = str[0] - 'a' + 1;
    for (int i = 1; i < n; i++) {
        val1[i] = (1LL * val1[i - 1] * P % MOD1 + str[i] - 'a' + 1) % MOD1;
        val2[i] = (1LL * val2[i - 1] * P % MOD2 + str[i] - 'a' + 1) % MOD2;
    }
    pow1[0] = 1, pow2[0] = 1;
    for (int i = 1; i <= n; i++) {
        pow1[i] = 1LL * pow1[i - 1] * P % MOD1;
        pow2[i] = 1LL * pow2[i - 1] * P % MOD2;
    }
}

long long hash_sub_str(int start, int len) {
    int end = start + len - 1;
    return (long long)(val1[end] - 1LL * val1[start - 1] * pow1[len] % MOD1 + MOD1) % MOD1 << 32 |
           (val2[end] - 1LL * val2[start - 1] * pow2[len] % MOD2 + MOD2) % MOD2;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> str;
    n = str.length();
    hash_whole_str();
    for (int len = 1; len <= n; len++) {
        for (int start = 0; start + len - 1 < n; start++) {
            pos[hash_sub_str(start, len)].push_back(start);
        }
        for (auto &&item : pos) {
            int cnt = item.second[0];
            int las = item.second[0] + len - 1;
            for (int i = 1; i < item.second.size(); i++) {
                if (las < item.second[i]) {
                    cnt += item.second[i] - las;
                }
                las = item.second[i] + len - 1;
            }
            cnt += n - las;
            if (res[cnt] == 0) { res[cnt] = len; }
        }
        pos.clear();
    }
    for (int i = 1; i <= n; i++) { cout << res[i] << (i == n ? "\n" : " "); }
    return 0;
}

