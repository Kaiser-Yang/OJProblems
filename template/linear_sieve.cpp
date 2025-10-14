#include <cassert>
#include <vector>

class linear_sieve {
public:
    // return the mobius function of [1, n)
    static std::vector<int> mobius(int n) { return get(n, true); }

    // reurn the primes in [2, n)
    static std::vector<int> primes(int n) { return get(n, false); }

    static int mobius_of(int x) {
        assert(x >= 1);
        int res = 1;
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) {
                x /= i;
                if (x % i == 0) { return 0; }
                res = -res;
            }
        }
        if (x > 1) { res = -res; }
        return res;
    }

private:
    static std::vector<int> get(int n, bool mobius) {
        std::vector<int> res(n, 1);
        std::vector<int> primes;
        std::vector<bool> is_composite(n, false);
        for (int i = 2; i < n; i++) {
            if (!is_composite[i]) {
                primes.push_back(i);
                res[i] = -1;
            }
            for (int p : primes) {
                if ((long long)p * i >= n) { break; }
                is_composite[p * i] = true;
                if (i % p == 0) {
                    res[p * i] = 0;
                    break;
                }
                res[p * i] = -res[i];
            }
        }
        return mobius ? res : primes;
    }
};
