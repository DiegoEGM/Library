//needs lca. this just builds the structure, but with help of lca you can also
//keep weigths etc. complexity is O(|s| log n) (binlift) or O(|s| log s) (sparse t.)
//because you at least need to sort s.
struct virtual_tree_maker {
    int n;
    vi rev; //rev[node] = idx of nodes after retagging, -1 if not in tree.
    vi prev_s; //to unmark previous nodes (maybe not needed?)
    virtual_tree_maker(int n_) : n(n_), rev(n + 1, -1) {}
    vi relevant_nodes(LCA &G, vi &s) {
        for(int u : prev_s) rev[u] = -1;
        prev_s.clear();
        sort(all(s), [&](int u, int v) { return G.in[u] < G.in[v]; } );
        vector <vi> adj(sz(s));
        vi rel = s;
        for(int i = 0; i + 1 < sz(s); i++) {
            rel.pb(G.lca(s[i], s[i + 1]));
        }
        sort(all(rel), [&](int u, int v) { return G.in[u] < G.in[v]; } );
        rel.resize(unique(all(rel)) - begin(rel));
        for(int i = 0; i < sz(rel); i++)
            rev[rel[i]] = i;
        prev_s = rel;
        return rel;
    }
    vector <vi> virtual_tree(LCA &G, vi &rel) {
        vector <vi> adj(sz(rel));
        for(int i = 0; i + 1 < sz(rel); i++) {
            adj[rev[G.lca(rel[i], rel[i + 1])]].pb(i + 1);
        }
        return adj;
    }
};
