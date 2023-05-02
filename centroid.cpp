struct centroid_decomp {
    int n;
    vector <vi> adj, dis; //dis = d. in original tree to ancestors on cent. tree
    vi vis, sub, par;
    centroid_decomp(int n_) : n(n_), adj(n + 1), dis(n + 1), vis(n + 1),
        sub(n + 1), par(n + 1, -1) {}
    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }
    void dfs_pre(int u, int prv) {
        sub[u] = 1;
        for(int v : adj[u]) {
            if(!vis[v] && v != prv) {
                dfs_pre(v, u);
                sub[u] += sub[v];
            }
        }
    }
    int find_centroid(int u, int prv, int sub_sz) {
        for(int v : adj[u])
            if(!vis[v] && v != prv && sub[v] > sub_sz / 2)
                return find_centroid(v, u, sub_sz);
        return u;
    }
    void dfs_dis(int u, int prv, int h) {
        for(int v : adj[u]) {
            if(!vis[v] && v != prv) {
                dis[v].pb(h + 1);
                dfs_dis(v, u, h + 1);
            }
        }
    }
    int build(int u) {
        dfs_pre(u, -1);
        u = find_centroid(u, -1, sub[u]);
        vis[u] = 1;
        dfs_dis(u, -1, 0);
        for(int v : adj[u]) {
            if(!vis[v]) {
                int w = build(v);
                par[w] = u;
            }
        }
        return u;
    }
    void init() {
        build(1);
        for(int u = 1; u <= n; u++) reverse(all(dis[u]));
    }
};
