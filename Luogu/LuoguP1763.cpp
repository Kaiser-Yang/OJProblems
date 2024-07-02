// problem statement: https://www.luogu.com.cn/problem/P1763

#include <bits/stdc++.h>

using namespace std;

size_t a, b, maxB;
vector<size_t> ans, now;

size_t gcd(size_t a, size_t b) { return b == 0 ? a : gcd(b, a % b); }

bool better() {
    if (ans.empty() || now.size() < ans.size()) { return true; }
    if (now.size() == ans.size() && now.back() < ans.back()) { return true; }
    return false;
}

bool dfs(size_t nowDepth, size_t a, size_t b, size_t maxDepth) {
    if (nowDepth > maxDepth) { return false; }
    size_t g = gcd(a, b);
    a /= g;
    b /= g;
    if (nowDepth == maxDepth) {
        if (a == 0 && better()) { ans = now; }
        return a == 0;
    }
    bool done = false;
    if (nowDepth == maxDepth - 2) {
        const size_t l = 4 * b / (a * a) + 1, r = min(2 * maxB / a, maxB * (maxB - 1) / b);
        for (size_t k = l; k <= r; k++) {
            size_t delta     = a * a * k * k - 4 * b * k;
            size_t sqrtDelta = sqrt(delta);
            if (sqrtDelta * sqrtDelta != delta || (a * k - sqrtDelta) % 2 == 1) { continue; }
            if ((a * k - sqrtDelta) / 2 > maxB || (a * k + sqrtDelta) / 2 > maxB) { continue; }
            now.push_back((a * k - sqrtDelta) / 2);
            now.push_back((a * k + sqrtDelta) / 2);
            if (better()) { ans = now; }
            now.pop_back();
            now.pop_back();
            done = true;
        }
        return done;
    }
    size_t nextDenominator = max(now.size() == 0 ? 1 : now.back() + 1, (b + a - 1) / a);
    while (true) {
        if ((maxDepth - nowDepth) < (a * nextDenominator + b - 1) / b || nextDenominator > 1e7) {
            break;
        }
        now.push_back(nextDenominator);
        if (dfs(nowDepth + 1, a * nextDenominator - b, b * nextDenominator, maxDepth)) {
            done = true;
        }
        now.pop_back();
        nextDenominator++;
    }
    return done;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> a >> b;
    for (size_t maxDepth = 1;; maxDepth++) {
        for (size_t maxB = 1e5; maxB <= 1e7; maxB *= 10) {
            ::maxB = maxB;
            if (dfs(0, a, b, maxDepth)) {
                for (size_t i = 0; i < ans.size(); i++) {
                    cout << ans[i] << (i == ans.size() - 1 ? '\n' : ' ');
                }
                return 0;
            }
        }
    }
    return 0;
}
