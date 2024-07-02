// problem statement: 

#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 3e5 + 10;

int n;
int number[MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) { cin >> number[i]; }
    int i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        if (number[(i + k) % n] == number[(j + k) % n]) {
            k++;
        } else {
            if (number[(i + k) % n] > number[(j + k) % n]) { i = i + k + 1; }
            else { j = j + k + 1; }
            k = 0;
            if (i == j) { j++; }
        }
    }
    i = min(i, j);
    for (int k = 0; k < n; k++) { cout << number[(i + k) % n] << " "; }
    cout << endl;
    return 0;
}
