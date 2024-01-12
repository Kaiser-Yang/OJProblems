#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 26;
constexpr int MAXM = 610;

int n, m;
string relation;
int inDegree[MAXN];
queue<char> ans;

vector<int> g[MAXN];

void addEdge(int u, int v)
{
    g[u].push_back(v);
}

void toposort(int iter)
{
    vector<int> inDegree(n + 1);
    std::copy(::inDegree, ::inDegree + n, inDegree.begin());
    while (!ans.empty()) { ans.pop(); }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }
    bool determined = true;
    while (!q.empty()) {
        int u = q.front();
        ans.push(u + 'A');
        q.pop();
        if (!q.empty()) { determined = false; }
        for (int v : g[u]) {
            if (--inDegree[v] == 0) {
                q.push(v);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (inDegree[i]) {
            cout << "Inconsistency found after " << iter << " relations.\n";
            exit(0);
        }
    }
    if (determined) {
        cout << "Sorted sequence determined after " << iter << " relations: ";
        while (!ans.empty()) {
            cout << ans.front();
            ans.pop();
        }
        cout << ".\n";
        exit(0);
    }
}

int main()
{
	ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> relation;
        inDegree[relation[2] - 'A']++;
        addEdge(relation[0] - 'A', relation[2] - 'A');
        toposort(i);
    }
    cout << "Sorted sequence cannot be determined.\n";
	return 0;
}
