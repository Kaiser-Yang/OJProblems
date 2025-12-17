#include <bits/stdc++.h>

using namespace std;

int dp(int i, int s0, int s1, int s2, int M, int N, int S, vector<vector<vector<int>>> &d, vector<int> &cost, vector<int> &course)
{
    if (i == M + N) {
        return (s2 == (1 << S) - 1 ? 0 : 50000 * 120);
    }
    int &ans = d[i][s1][s2];
    if (ans >= 0) {
        return ans;
    }
    ans = 50000 * 120;
    if (i >= M) {
        ans = dp(i + 1, s0, s1, s2, M, N, S, d, cost, course);
    }
    int m0 = course[i] & s0;
    int m1 = course[i] & s1;
    s0 ^= m0;
    s1 = (s1 ^ m1) | m0;
    s2 |= m1;
    ans = min(ans, dp(i + 1, s0, s1, s2, M, N, S, d, cost, course) + cost[i]);
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    int S, M, N, number;
    vector<int> cost, course;
    vector<vector<vector<int>>> d;
    string str;
    while (cin >> S >> M >> N && S != 0) {
        cost.clear();
        course.clear();
        cin.get();
        for (int i = 0; i < M; i++) {
            getline(cin, str);
            istringstream iss(str);
            iss >> number;
            cost.push_back(number);
            int status = 0;
            while (iss >> number) {
                number--;
                status |= 1 << number;
            }
            course.push_back(status);
        }
        for (int i = 0; i < N; i++) {
            getline(cin, str);
            istringstream iss(str);
            iss >> number;
            cost.push_back(number);
            int status = 0;
            while (iss >> number) {
                number--;
                status |= 1 << number;
            }
            course.push_back(status);
        }
        d.clear();
        d.resize(N + M);
        for (int i = 0; i < N + M; i++) {
            d[i].resize(1 << S);
            for (int s1 = 0; s1 < (1 << S); s1++) {
                d[i][s1].resize(1 << S, -1);
            }
        }
        cout << dp(0, (1 << S) - 1, 0, 0, M, N, S, d, cost, course) << endl;
    }
    return 0;
}