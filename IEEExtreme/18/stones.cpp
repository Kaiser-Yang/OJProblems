// problem satement: https://csacademy.com/ieeextreme-practice/task/stones/

#include <bits/stdc++.h>

using namespace std;

int R1, B1, R2, B2;
double dp[41][41][41][41];
bool computed[41][41][41][41];

// hider:  R1, B1
// seeker: R2, B2
// returns the probability of the hider winning
double dfs(int R1, int B1, int R2, int B2) {
    if (R1 == 0 || B1 == 0) { return 0; }
    if (R2 == 0 || B2 == 0) { return 1; }
    if (computed[R1][B1][R2][B2]) { return dp[R1][B1][R2][B2]; }
    double rr = 1 - dfs(R2, B2, R1 - 1, B1);  // hide red and guess red
    double rb = 1 - dfs(R2, B2 - 1, R1, B1);  // hide red and guess blue
    double br = 1 - dfs(R2 - 1, B2, R1, B1);  // hide blue and guess red
    double bb = 1 - dfs(R2, B2, R1, B1 - 1);  // hide blue and guess blue
    double p = 0;                             // the probability of hiding red one
    if (rr - rb - br + bb == 0) {
        p = 1;
    } else {
        p = (bb - br) / (rr - rb - br + bb);
    }
    double q = 0;  // the probability of guessing red one
    if (rr - rb - br + bb == 0) {
        q = 1;
    } else {
        q = (bb - rb) / (rr - rb - br + bb);
    }
    computed[R1][B1][R2][B2] = true;
    return dp[R1][B1][R2][B2] =
               p * q * rr + p * (1 - q) * rb + (1 - p) * q * br + (1 - p) * (1 - q) * bb;
}
int main() {
    cin >> R1 >> B1 >> R2 >> B2;
    cout << fixed << setprecision(9) << dfs(R1, B1, R2, B2) << endl;
    return 0;
}
