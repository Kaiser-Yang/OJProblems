#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int n, t = 1;
    vector<double> a, b, c;
    vector<int> id, score;
    while (cin >> n && n != 0) {
        a.resize(n);
        b.resize(n);
        c.resize(n);
        id.resize(n);
        score.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i] >> b[i] >> c[i];
            a[i] = round(a[i] * 100);
            b[i] = round(b[i] * 100);
            c[i] = round(c[i] * 100);
        }
        bool ok = true;
        for (int i = 0; i < n; i++) {
            cin >> id[i];
            id[i]--;
        }
        score[0] = a[id[0]] + b[id[0]] + c[id[0]];
        for (int i = 1; i < n; i++) {
            score[i] = a[id[i]] + b[id[i]] + c[id[i]];
            vector<int> num;
            num.push_back(0);
            num.push_back(a[id[i]]);
            num.push_back(b[id[i]]);
            num.push_back(c[id[i]]);
            num.push_back(a[id[i]] + b[id[i]]);
            num.push_back(a[id[i]] + c[id[i]]);
            num.push_back(b[id[i]] + c[id[i]]);
            num.push_back(a[id[i]] + b[id[i]] + c[id[i]]);
            sort(num.begin(), num.end());
            if (id[i] > id[i - 1]) {
                for (int j = 0; j < num.size(); j++) {
                    if (score[i] - num[j] <= score[i - 1]) {
                        score[i] -= num[j];
                        break;
                    }
                }
            } else {
                ok = false;
                for (int j = 0; j < num.size(); j++) {
                    if (score[i] - num[j] < score[i - 1]) {
                        score[i] -= num[j];
                        ok = true;
                        break;
                    }
                }
                if (!ok) { break; }
            }
        }
        cout << "Case " << t << ": ";
        t++;
        if (!ok) {
            cout << "No solution" << endl;
            continue;
        }
        cout << fixed << setprecision(2) << (double)score[n - 1] / 100 << endl;
    }
    return 0;
}
