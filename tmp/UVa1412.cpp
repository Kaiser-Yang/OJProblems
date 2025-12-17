#include <bits/stdc++.h>

using namespace std;

void dfs(int stock,
         vector<int> &lot,
         int totLot,
         int N,
         map<vector<int>, int> &id,
         vector<vector<int>> &state,
         vector<int> &k,
         int K) {
    if (stock == N) {
        id[lot] = state.size();
        state.push_back(lot);
        return;
    }
    for (int i = 0; i <= k[stock] && totLot + i <= K; i++) {
        lot[stock] = i;
        dfs(stock + 1, lot, totLot + i, N, id, state, k, K);
    }
}

void print(int day,
           int s,
           vector<vector<double>> &dp,
           vector<vector<int>> &pre,
           vector<vector<int>> &opt,
           vector<string> &name) {
    if (day == 0) { return; }
    print(day - 1, pre[day][s], dp, pre, opt, name);
    if (opt[day][s] == 0) {
        cout << "HOLD\n";
    } else if (opt[day][s] > 0) {
        cout << "BUY " << name[opt[day][s] - 1] << endl;
    } else {
        cout << "SELL " << name[-opt[day][s] - 1] << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    double C;
    int M, N, K;
    vector<string> name;
    vector<int> s, k;
    vector<vector<double>> price;
    vector<vector<int>> state;
    map<vector<int>, int> id;
    vector<vector<int>> buyNext, sellNext;
    vector<vector<double>> dp;
    vector<vector<int>> pre, opt;
    bool first = true;
    while (cin >> C >> M >> N >> K) {
        if (!first) { cout << endl; }
        first = false;
        name.clear();
        s.clear();
        k.clear();
        price.resize(N);
        for (int i = 0; i < N; i++) {
            string str;
            int ss, kk;
            cin >> str >> ss >> kk;
            name.push_back(str);
            s.push_back(ss);
            k.push_back(kk);
            price[i].resize(M);
            for (int j = 0; j < M; j++) {
                cin >> price[i][j];
                price[i][j] *= s[i];
            }
        }
        vector<int> lot(N);
        state.clear();
        id.clear();
        dfs(0, lot, 0, N, id, state, k, K);
        buyNext.resize(state.size());
        sellNext.resize(state.size());
        for (int s = 0; s < state.size(); s++) {
            int totLot = 0;
            for (int i = 0; i < N; i++) { totLot += state[s][i]; }
            buyNext[s].resize(N);
            sellNext[s].resize(N);
            for (int i = 0; i < N; i++) {
                buyNext[s][i] = sellNext[s][i] = -1;
                if (state[s][i] < k[i] && totLot < K) {
                    vector<int> newState = state[s];
                    newState[i]++;
                    buyNext[s][i] = id[newState];
                }
                if (state[s][i] > 0) {
                    vector<int> newState = state[s];
                    newState[i]--;
                    sellNext[s][i] = id[newState];
                }
            }
        }
        dp.clear();
        dp.resize(M + 1);
        pre.resize(M + 1);
        opt.resize(M + 1);
        for (int i = 0; i <= M; i++) {
            dp[i].resize(state.size(), -1);
            pre[i].resize(state.size());
            opt[i].resize(state.size());
        }
        dp[0][0] = C;
        for (int i = 0; i < M; i++) {
            for (int s = 0; s < state.size(); s++) {
                if (dp[i][s] == -1) { continue; }
                if (dp[i + 1][s] < dp[i][s]) {
                    dp[i + 1][s] = dp[i][s];
                    pre[i + 1][s] = s;
                    opt[i + 1][s] = 0;
                }
                for (int j = 0; j < N; j++) {
                    if (buyNext[s][j] >= 0 && dp[i][s] >= price[j][i] - 1e-3 &&
                        dp[i + 1][buyNext[s][j]] < dp[i][s] - price[j][i]) {
                        dp[i + 1][buyNext[s][j]] = dp[i][s] - price[j][i];
                        pre[i + 1][buyNext[s][j]] = s;
                        opt[i + 1][buyNext[s][j]] = j + 1;
                    }
                    if (sellNext[s][j] >= 0 && dp[i + 1][sellNext[s][j]] < dp[i][s] + price[j][i]) {
                        dp[i + 1][sellNext[s][j]] = dp[i][s] + price[j][i];
                        pre[i + 1][sellNext[s][j]] = s;
                        opt[i + 1][sellNext[s][j]] = -(j + 1);
                    }
                }
            }
        }
        cout << fixed << setprecision(2) << dp[M][0] << endl;
        print(M, 0, dp, pre, opt, name);
    }
    return 0;
}
