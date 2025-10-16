// problem statement: http://poj.org/problem?id=1597

#include <iomanip>
#include <iostream>

template <typename T>
static T gcd(T a, T b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int STEP, MOD;
    while (std::cin >> STEP >> MOD) {
        std::cout << std::right << std::setw(10) << STEP << std::setw(10) << MOD << "    "
                  << std::left << std::setw(15)
                  << (gcd(STEP, MOD) == 1 ? "Good Choice" : "Bad Choice") << "\n\n";
    }
    return 0;
}
