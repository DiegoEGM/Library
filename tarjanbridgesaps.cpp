/*
O((n + m) log n) since we use a set for bridges and artic points.
bridges can just be a vector without problem (if no double edges).
artic points can be a vector if we also keep an 'already in set'
flag, to make it O(n + m).
*/
struct BridgeAndArticulation {
    int t, n;
    vi min_time, disc_time;
    vector <bool> in_stack;
    stack <int> stk;
    vector <vi> adj;
    set <pii> bridges;
    set <int> artic_points;
    BridgeAndArticulation(int n_) : n(n_), t(1) {
        adj.resize(n + 1);
        min_time.resize(n + 1, 0);
        disc_time.resize(n + 1, 0);
        in_stack.resize(n + 1, false);
        artic_points.clear();
        bridges.clear();
    }
    void add_edge(int u, int v) { adj[u].pb(v); adj[v].pb(u); }
    void tarjan_dfs(int node, int par) {
        if(disc_time[node]) return;
        int child_cnt = 0;
        disc_time[node] = min_time[node] = t++;
        stk.push(node);
        in_stack[node] = true;

        for(auto u : adj[node]) {
            //edge to parent isn't backedge
            //(consider changing that if it actually allows double edges)
            if(u == par) continue;
            if(!disc_time[u]) {
                tarjan_dfs(u, node);
                child_cnt++;
                min_time[node] = min(min_time[node], min_time[u]);
                if(min_time[u] >= disc_time[node] && par != -1) {
                    artic_points.insert(node);
                }
                if(min_time[u] > disc_time[node]) {
                    bridges.insert({min(node, u), max(node, u)});
                }
                else {
                    //can connect (node, u) with a dsu here, for a bridge tree.
                }
            }
            else if(in_stack[u]) {
                min_time[node] = min(min_time[node], disc_time[u]);
            }
        }
        if(par == -1 && child_cnt > 1)
            artic_points.insert(node);
    }
    void find_points_and_bridges() {
        for(int i = 1; i <= n; i++) tarjan_dfs(i, -1);
    }
};

