// problem statement: https://www.luogu.com.cn/problem/P1080

#include <bits/stdc++.h>

constexpr int MAXN = 1e3 + 10;

using namespace std;

int n, kingLeft, kingRight;

struct BigNumber {
    int BASE  = 1e4;
    int WIDTH = 4;
    vector<int> num;

    BigNumber(int num = 0, int base = 1e4, int width = 4) : BASE(base), WIDTH(width) {
        do {
            this->num.push_back(num % BASE);
            num /= BASE;
        } while (num);
    }

    bool operator<(const BigNumber &other) {
        if (num.size() < other.num.size()) { return true; }
        for (int i = num.size() - 1; i >= 0; i--) {
            if (num[i] < other.num[i]) { return true; }
        }
        return false;
    }

    BigNumber operator*(const int other) {
        for (int i = 0; i < num.size(); i++) {
            num[i] *= other;
            if (i != 0) {
                num[i] += num[i - 1] / BASE;
                num[i - 1] %= BASE;
            }
        }
        if (num.back() >= BASE) {
            num.push_back(0);
            num.back() = num[num.size() - 2] / BASE;
            num[num.size() - 2] %= BASE;
        }
        return *this;
    }

    BigNumber operator/(const int other) {
        BigNumber res{*this};
        int now = 0;
        for (int i = num.size() - 1; i >= 0; i--) {
            now        = now * BASE + num[i];
            res.num[i] = now / other;
            now %= other;
        }
        while (!res.num.empty() && res.num.back() == 0) { res.num.pop_back(); }
        return res;
    }
};

ostream &operator<<(ostream &os, const BigNumber &bn) {
    for (auto it = bn.num.rbegin(); it != bn.num.rend(); it++) {
        if (it == bn.num.rbegin()) {
            os << *it;
        } else {
            os << setw(bn.WIDTH) << setfill('0') << *it;
        }
    }
    return os;
}

vector<pair<BigNumber, BigNumber>> minister;
pair<int, int> temp[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    cin >> kingLeft >> kingRight;
    for (int i = 0; i < n; i++) { cin >> temp[i].first >> temp[i].second; }
    sort(temp, temp + n, [](const auto &a, const auto &b) {
        return a.first * a.second < b.first * b.second;
    });
    for (int i = 0; i < n; i++) {
        minister.push_back({BigNumber(temp[i].first), BigNumber(temp[i].second)});
    }
    BigNumber ans{0};
    BigNumber now{kingLeft};
    for (int i = 0; i < n; i++) {
        BigNumber t{now / temp[i].second};
        if (ans < t) { ans = std::move(t); }
        now = now * temp[i].first;
    }
    cout << ans << endl;
    return 0;
}
