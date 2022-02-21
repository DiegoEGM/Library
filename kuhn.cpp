/*
complexity = O(nm) = O(n_left * #edges)
speed up heuristic to consider: first try a greedy matching
to recover, just check from 1 to n_right if G.match[i] != -1, then its
G.match[i] -> i.
Dinic is faster, but this could come in handy, its shorter :p
*/
struct Kuhn {
    int n_left, n_right;
    vector <vi> adj;
    vi match;
    vector <bool> used;
    Kuhn(int n1, int n2) : n_left(n1), n_right(n2) {
        match.resize(n_right + 1, -1);
        used.resize(n_left + 1, false);
        adj.resize(n_left + 1);
    }
    //u in left, v in right
    void add_edge(int u, int v) { adj[u].pb(v); }
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
    void do_matching() {
        for(int i = 1; i <= n_left; i++) {
            used.assign(n_left + 1, false);
            try_kuhn(i);
        }
    }
};
