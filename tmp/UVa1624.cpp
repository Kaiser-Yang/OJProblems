#include <bits/stdc++.h>

using namespace std;

void deleteNode(int i, vector<int> &pre, vector<int> &nex, vector<int> &ud) {
    nex[pre[i]] = nex[i];
    pre[nex[i]] = pre[i];
    ud[i] = 0;
}

int main() {
    ios::sync_with_stdio(false);
    int T, L, P, a, b;
    vector<int> pre, nex, ud;
    vector<int> link;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> L >> P;
        pre.resize(L);
        nex.resize(L);
        ud.clear();
        ud.resize(L);
        link.clear();
        link.resize(L);
        for (int i = 0; i < L; i++) {
            pre[i] = i - 1;
            nex[i] = i + 1;
        }
        pre[0] = L - 1;
        nex[L - 1] = 0;
        for (int i = 0; i < P; i++) {
            cin >> a >> b;  // a is above b
            link[a] = b;
            link[b] = a;
            ud[a] = 1;
            ud[b] = -1;
        }

        for (int i = 0; i < L; i++) {
            if (ud[i] == 0) { deleteNode(i, pre, nex, ud); }
        }

        int i = 0;
        while (P != 0) {
            bool ok = false;
            while (ud[i] == 0) { i++; }
            for (int u = nex[i]; u != i; u = nex[u]) {
                int v = nex[u];
                if (ud[u] == ud[v] && (nex[link[u]] == link[v] || nex[link[v]] == link[u])) {
                    deleteNode(u, pre, nex, ud);
                    deleteNode(v, pre, nex, ud);
                    deleteNode(link[u], pre, nex, ud);
                    deleteNode(link[v], pre, nex, ud);
                    P -= 2;
                    ok = true;
                    break;
                } else if (link[u] == v || link[v] == u) {
                    deleteNode(u, pre, nex, ud);
                    deleteNode(v, pre, nex, ud);
                    P -= 1;
                    ok = true;
                    break;
                }
            }
            if (!ok) { break; }
        }
        cout << "Case #" << t << ": ";
        if (P != 0) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    }
    return 0;
}
