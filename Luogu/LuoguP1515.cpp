// problem statement: https://www.luogu.com.cn/problem/P1515

#include <bits/stdc++.h>

using namespace std;

int minDis, maxDis, n, pos;
vector<int> hotel{0,990,1010,1970,2030,2940,3060,3930,4060,4970,5030,5990,6010,7000}, dp;

int main()
{
	ios::sync_with_stdio(false);
    cin >> minDis >> maxDis >> n;
    for (int i = 0; i < n; i++) {
        cin >> pos;
        hotel.push_back(pos);
    }
    sort(hotel.begin(), hotel.end());
    int len = unique(hotel.begin(), hotel.end()) - hotel.begin();
    dp.resize(len, 0);
    dp[0] = 1;
    deque<int> dq;
    dq.push_back(0);
    for (int i = 1; i < len; i++) {
        while (!dq.empty() && hotel[i] - hotel[dq.front()] > maxDis) { dq.pop_front(); }
        if (dq.empty()) { break; }
        for (int j = 0; j < dq.size() && hotel[i] - hotel[dq[j]] >= minDis; j++) { dp[i] += dp[dq[j]]; }
        dq.push_back(i);
    }
    cout << dp[len - 1] << endl;
	return 0;
}
