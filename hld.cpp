struct HLD {
    int n, t;
    vi heavy, p, subtree_sz, h, tour, in, head;
    vector <vi> adj;

    HLD(int n_) : n(n_), t(0), heavy(n + 1), p(n + 1), subtree_sz(n + 1),
        h(n + 1), tour(n + 1), in(n + 1), head(n + 1), adj(n + 1) {}

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    void dfs_prep(int u, int par) {
        subtree_sz[u] = 1;
        heavy[u] = -1;
        h[u] = h[par] + 1;
        p[u] = par;
        for(auto v : adj[u]) {
            if(v == par) continue;
            dfs_prep(v, u);
            subtree_sz[u] += subtree_sz[v];
            if(heavy[u] == -1 || subtree_sz[v] > subtree_sz[heavy[u]])
                heavy[u] = v;
        }
    }
    void dfs_hld(int u, int par) {
        in[u] = t;
        tour[t++] = u;
        head[u] = u != heavy[par] ? u : head[par];
        if(heavy[u] == -1) return;
        dfs_hld(heavy[u], u);
        for(auto v : adj[u]) {
            if(v == par || v == heavy[u]) continue;
            dfs_hld(v, u);
        }
    }

    int lca(int u, int v) {
        ll ret = 0;
        while(head[u] != head[v]) {
            if(h[head[u]] < h[head[v]]) swap(u, v);
            u = p[head[u]];
        }
        if(h[u] > h[v]) swap(u, v);
        return u;
    }

    void init() {
        dfs_prep(1, 1);
        dfs_hld(1, 1);
    }
};

