#include <bits/stdc++.h>

using namespace std;

vector<vector<long long>> a;

long long determint(vector<vector<long long>> &x) {
    if (x.size() == 1) { return x[0][0]; }
    long long flag = 1;
    long long res = 0;
    for (int i = 0; i < x.size(); i++) {
        vector<vector<long long>> temp;
        temp.resize(x.size() - 1);
        for (int k = 0; k < temp.size(); k++) {
            temp[k].resize(temp.size());
            for (int l = 0; l < temp[k].size(); l++) { temp[k][l] = x[1 + k][l >= i ? l + 1 : l]; }
        }
        res += flag * x[0][i] * determint(temp);
        flag = -flag;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    a.resize(3);
    for (int i = 0; i < 3; i++) {
        a[i].resize(3);
        for (int j = 0; j < 3; j++) { cin >> a[i][j]; }
    }
    cout << determint(a) << endl;
    return 0;
}