// problem statement: https://www.luogu.com.cn/problem/P1379

#include <bits/stdc++.h>

using namespace std;

using State = string;

State start, end = "123804765";
unordered_map<State, int> dist;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

struct Comparor {
    bool operator()(const pair<State, int> &a, const pair<State, int> &b) {
        return a.second > b.second;
    }
};

int h(const string &now) {
    int res = 0;
    for (size_t i = 0; i < now.length(); i++) {
        if (now[i] != ::end[i]) { res++; }
    }
    return res;
}

void AStar() {
    priority_queue<pair<State, int>, vector<pair<State, int>>, Comparor> q;
    q.push({start, 0});
    dist[start] = 0;
    while (!q.empty()) {
        auto item = q.top();
        q.pop();
        if (item.first == ::end) {
            cout << dist[item.first] << endl;
            return;
        }
        int pos = item.first.find('0');
        for (int i = 0; i < 4; i++) {
            int x = pos / 3 + dx[i];
            int y = pos % 3 + dy[i];
            if (x < 0 || x >= 3 || y < 0 || y >= 3) continue;
            State next = item.first;
            swap(next[pos], next[x * 3 + y]);
            if (!dist.count(next) || dist[next] > dist[item.first] + 1) {
                dist[next] = dist[item.first] + 1;
                q.push({next, dist[next] + h(next)});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> start;
    AStar();
    return 0;
}
