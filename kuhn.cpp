#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5+3;

/*
complexity O(nm) = O(#components left side * #edges)
source:
https://cp-algorithms.com/graph/kuhn_maximum_bipartite_matching.html
consider the heuristic of taking a naive matching first.
modifications for when the partition isnt clear should be somewhat easy to make
*/

struct Kuhn {
    int sz1, sz2;
    vector <int> *adj;
    vector <int> match;
    vector <bool> used;

    Kuhn(vector <int> *adj_, int n_, int m_) {
        sz1 = n_, sz2 = m_, adj = adj_;
        match.resize(m_ + 1, -1), used.resize(n_ + 1, false);
    }

    bool try_kuhn(int node) {
        if(used[node])
            return false;
        used[node] = true;
        for(int u : adj[node]) {
            if(match[u] == -1 || try_kuhn(match[u])) {
                match[u] = node;
                return true;
            }
        }
        return false;
    }

};

int n, k, m; //#comps 1st part, #comps 2nd part, #edges
//note adj must only contain from the 1st part to the 2nd one
vector <int> adj[N];

int main() {
    #ifndef LOCAL
        ios_base::sync_with_stdio(false); cin.tie(0);
    #endif // LOCAL
    ////trying
    cin >> n >> k >> m;
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        assert(a >= 1 && a <= n && b >= 1 && b <= k);
        adj[a].push_back(b);
    }

    Kuhn G(adj, n, k);
    for(int i = 1; i <= n; i++) {
        G.used.assign(n + 1, false);
        G.try_kuhn(i);
    }

    cout << "A maximum matching is:\n";
    for(int i = 1; i <= k; i++)
        if(G.match[i] != -1)
            cout << G.match[i] << " " << i << "\n";

    return 0;
}
