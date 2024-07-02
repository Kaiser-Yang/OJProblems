#include <bits/stdc++.h>

using namespace std;

int pos;
string card;
map<int, stack<string>> h;
map<string, int> hand;

bool dfs(int depth) {
    if (depth == 12) { return true; }
    int handSize = hand["A"] + hand["B"] + hand["C"] + hand["D"];
    if (handSize == 7) { return false; }
    for (auto &item : h) {
        if (item.second.empty()) { continue; }
        string temp = item.second.top();
        item.second.pop();
        int handTemp = hand[temp];
        hand[temp]++;
        if (hand[temp] == 3) { hand[temp] = 0; }
        if (dfs(depth + 1)) { return true; }
        item.second.push(temp);
        hand[temp] = handTemp;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    for (int i = 0; i < 12; i++) {
        cin >> pos >> card;
        h[pos].push(card);
    }
    if (h.size() >= 6 || dfs(0)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}