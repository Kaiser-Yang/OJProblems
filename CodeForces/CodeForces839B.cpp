// problem statement: https://codeforces.com/contest/839/problem/B

#include <bits/stdc++.h>

using namespace std;

int n, k, a, cnt;
vector<int> rest(4);

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        cin >> a;
        cnt += a / 4;
        rest[a % 4]++;
    }
    int num_two_seats = 2 * n, num_four_seats = n;
    if (cnt > num_four_seats) {
        cnt -= num_four_seats;
        num_four_seats = 0;
        num_two_seats -= cnt * 2;
        if (num_two_seats < 0) {
            cout << "NO\n";
            return 0;
        }
    } else {
        num_four_seats -= cnt;
    }
    if (rest[3] > num_four_seats) {
        rest[3] -= num_four_seats;
        num_four_seats = 0;
        num_two_seats -= rest[3] * 2;
        if (num_two_seats < 0) {
            cout << "NO\n";
            return 0;
        }
    } else {
        num_four_seats -= rest[3];
    }
    if (rest[2] > num_two_seats) {
        rest[2] -= num_two_seats;
        num_two_seats = 0;
        if (rest[2] > num_four_seats) {
            rest[2] -= num_four_seats;
            rest[1] += rest[2] * 2;
            num_two_seats += num_four_seats;
            num_four_seats = 0;
        } else {
            num_four_seats -= rest[2];
            num_two_seats += rest[2];
        }
    } else {
        num_two_seats -= rest[2];
    }
    if (rest[1] > num_two_seats + 2 * num_four_seats) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES" << "\n";
    return 0;
}
