struct SCC {
    int n;
    vi order;
    vector <bool> vis;
    vector <vi> adj, radj, sccs;

    SCC(int n_) : n(n_), vis(n + 1), adj(n + 1), radj(n + 1) {}

    void add_edge(int u, int v) { adj[u].pb(v); radj[v].pb(u); }

    void dfs_prep(int u) {
        vis[u] = true;
        for(auto v : radj[u])
            if(!vis[v])
                dfs_prep(v);
        order.pb(u);
    }

    void dfs(int u) {
        vis[u] = true;
        for(auto v : adj[u])
            if(!vis[v])
                dfs(v);
        sccs.back().pb(u);
    }

    void find_sccs() {
        for(int i = 1; i <= n; i++)
            if(!vis[i])
                dfs_prep(i);
        fill(all(vis), false);
        reverse(all(order));
        for(auto u : order)
            if(!vis[u]) {
                sccs.pb({});
                dfs(u);
            }
    }
};

