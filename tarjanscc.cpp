/*
when find_scc is done, sccs
now keeps a vector of vectors where
each vector is one of the strongly connected components,
with the "head" (first found) at the end.
sccs is now the reverse topological order of the DAG
of the compressed graph.
O(n + m).
verified: https://judge.yosupo.jp/submission/88281
*/
struct SCC {
    int n, t;
    vi min_time, disc_time;
    vector <bool> in_stack;
    stack <int> stk;
    vector <vi> adj, sccs;

    SCC(int n_) : n(n_), t(1), adj(n + 1),
        min_time(n + 1), disc_time(n + 1), in_stack(n + 1) {}

    //process the scc with node as its root/head.
    void add_edge(int u, int v) { adj[u].pb(v); }
    void process_scc(int node) {
        int top;
        sccs.pb({});
        do {
            top = stk.top();
            stk.pop();
            in_stack[top] = false;
            sccs.back().pb(top);
        } while(top != node);

    }
    void tarjan_dfs(int node) {
        if(disc_time[node]) return;
        disc_time[node] = min_time[node] = t++;
        stk.push(node);
        in_stack[node] = true;
        for(auto u : adj[node]) {
            if(!disc_time[u]) {
                tarjan_dfs(u);
                min_time[node] = min(min_time[node], min_time[u]);
            }
            else if(in_stack[u]) {
                min_time[node] = min(min_time[node], disc_time[u]);
            }
        }
        if(min_time[node] == disc_time[node]) { //its the 'head' of a component
            process_scc(node);
        }
    }
    void find_sccs() {
        for(int i = 1; i <= n; i++) tarjan_dfs(i);
    }
};



