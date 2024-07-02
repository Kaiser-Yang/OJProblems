// problem statement:

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 22;

int n, k;
int number[MAXN];
bool chosen[MAXN];
set<int> primeNumber;

bool isPrimeNumber(int number) {
    if (number == 1) { return false; }
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) { return false; }
    }
    return true;
}

void count() {
    int cnt = 0, sum = 0, id = 0;
    for (int i = 0; i < n; i++) {
        cnt += chosen[i];
        sum += chosen[i] ? number[i] : 0;
        id |= static_cast<int>(chosen[i]) << i;
    }
    if (cnt == k && isPrimeNumber(sum)) { primeNumber.insert(id); }
}

void dfs(int depth) {
    if (depth == n) {
        count();
        return;
    }
    chosen[depth] = true;
    dfs(depth + 1);
    chosen[depth] = false;
    dfs(depth + 1);
}

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) { cin >> number[i]; }
    dfs(0);
    cout << primeNumber.size() << endl;
    return 0;
}