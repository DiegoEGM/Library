/*
O(log n) lca with O(n log n) construction.
Minimal changes (vector<vi> vs vector<vector<pii>>) are needed
when you need max/sum/etc of a path
*/
struct LCA {
    int n, l;
    vector <vi> p, adj;
    vi h;
    LCA(int n_) : n(n_) {
        l = 0;
        while((1 << l) <= n) l++;
        p.assign(n + 1, vi(l));
        adj.resize(n + 1);
        h.resize(n + 1);
    }
    void add_edge(int u, int v) { adj[u].pb(v); adj[v].pb(u); }
    void dfs(int node, int par) {
        h[node] = h[par] + 1;
        p[node][0] = par;
        for(int i = 1; i < l; i++) {
            p[node][i] = p[p[node][i - 1]][i - 1];
        }
        for(auto u : adj[node]) {
            if(u != par) {
                dfs(u, node);
            }
        }
    }
    int go_up(int node, int d) {
        for(int i = 0; i < l; i++)
            if((d >> i) & 1)
                node = p[node][i];
        return node;
    }
    int lca(int u, int v) {
        if(h[u] < h[v]) swap(u, v);
        u = go_up(u, h[u] - h[v]);
        if(u == v) return u;
        for(int i = l - 1; i >= 0; i--) {
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

