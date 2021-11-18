#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+3;

/*
LCA with powers of 2 jumps (binary lifting)
dfs (building) : O(nlogn)
lca, dist, goup : all O(log n)
to change for a vector <pair<int,int>> adjacency
(weights) just change lines 18, 21, and smthing near 35
*/

struct LCA {
    int sz, L;
    vector <vector<int>> p;
    vector <int> *adj;
    vector <int> h;

    LCA(vector<int> *adj_list, int n) {
        adj = adj_list, sz = n;
        L = 0;
        while((1 << L) <= n)
            L++;
        p.assign(n + 1, vector<int>(L));
        h.resize(n + 1);
    }

    void dfs(int node, int par) {
        h[node] = h[par] + 1;
        p[node][0] = par;
        for(int i = 1; i < L; i++) {
            p[node][i] = p[p[node][i - 1]][i - 1];
        }
        for(auto u : adj[node]) {
            if(u != par) {
                dfs(u, node);
            }
        }
    }

    int goup(int node, int d) {
        for(int i = 0; i < L; i++)
            if((d >> i) & 1)
                node = p[node][i];
        return node;
    }

    int lca(int u, int v) {
        if(h[u] < h[v]) swap(u, v);
        u = goup(u, h[u] - h[v]);
        if(u == v) return u;
        for(int i = L - 1; i >= 0; i--) {
            if(p[u][i] != p[v][i]) {
                u = p[u][i];
                v = p[v][i];
            }
        }
        return p[u][0];
    }

    int dist(int u, int v) {
        return h[u] + h[v] - 2 * h[lca(u, v)];
    }

};

//-----------------------------------------------------------
int n, a, b, q;
vector <int> adj[N];

int main()
{

    cin >> n;
    for(int i = 1; i < n; i++) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    LCA G(adj, n);
    G.dfs(1, 1);
    cin >> q;
    while(q--) {
        cin >> a >> b;
        cout << G.lca(a, b) << '\n';
    }
    return 0;
}
/* test
8
1 2
2 3
2 4
2 5
5 6
5 7
7 8
5
3 5
6 8
1 4
3 4
2 8
should be 2 5 1 2 2
*/
