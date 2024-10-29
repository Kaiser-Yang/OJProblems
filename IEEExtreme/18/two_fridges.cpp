// problem statement: https://csacademy.com/ieeextreme-practice/task/two-fridges

#include <bits/stdc++.h>

using namespace std;

const int N = 110;

struct {
    int a, b;
} fridge[N];

int n;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) { cin >> fridge[i].a >> fridge[i].b; }
    for (int t1 = -100; t1 <= 100; t1++) {
        for (int t2 = t1; t2 <= 100; t2++) {
            bool done = true;
            for (int i = 0; i < n; i++) {
                if ((fridge[i].a > t1 || fridge[i].b < t1) &&
                    (fridge[i].a > t2 || fridge[i].b < t2)) {
                    done = false;
                    break;
                }
            }
            if (done) {
                cout << t1 << " " << t2 << endl;
                return 0;
            }
        }
    }
    cout << "-1\n";
    return 0;
}
