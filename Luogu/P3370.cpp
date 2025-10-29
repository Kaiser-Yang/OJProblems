// problem statement: https://www.luogu.com.cn/problem/P3370

#include <cassert>
#include <cstdint>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;

template <typename T = u64, T base = T(131), T mod = T(1e9 + 7)>
class hash {
public:
    hash(const std::string &s) { build(s); }

    // [0, pos)
    T get(int pos) const {
        assert(pos >= 0 && pos < prefix_hash.size());
        return prefix_hash[pos];
    }

    // [l, r)
    T get(int l, int r) const {
        assert(l >= 0 && r < prefix_hash.size() && l < r);
        return (prefix_hash[r] - prefix_hash[l] * power[r - l] % mod + mod) % mod;
    }

private:
    void build(const std::string &s) {
        auto n = s.size();
        prefix_hash.resize(n + 1, 0);
        power.resize(n + 1, 1);
        for (int i = 0; i < n; i++) {
            prefix_hash[i + 1] = (prefix_hash[i] * base + s[i]) % mod;
            power[i + 1] = (power[i] * base) % mod;
        }
    }

    std::vector<T> prefix_hash;
    std::vector<T> power;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::set<std::pair<u64, u64>> hash_set;
    for (int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;
        hash<> h1(s);
        hash<u64, 133, u64(1e9 + 9)> h2(s);
        hash_set.insert({h1.get(s.size()), h2.get(s.size())});
    }
    std::cout << hash_set.size() << "\n";
    return 0;
}
