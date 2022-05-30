template <class T = int>
struct Dinic {
    //u -> v with capacity cap.
    //u is not used in algorithm, but its useful for restoring cuts etc.
    struct Edge {
        int u, v;
        T cap;
        Edge(int u_, int v_, T c_) : u(u_), v(v_), cap(c_) {}
    };
    int n, s, t; //s = source, t = sink.
    vi pt, dist; //first edge to consider. distance in level graph.
    vector <Edge> edges; //even indices are original edges, odd are their reverse.
    vector <vi> adj; //adjacency is kept as indices of edges in 'edges' array.
    Dinic(int n_, int s_, int t_)  : n(n_), s(s_), t(t_),
                        pt(n + 1), dist(n + 1), adj(n + 1) {}
    void add_edge(int u, int v, T cap) {
        edges.pb(Edge(u, v, cap));
        edges.pb(Edge(v, u, T(0)));
        adj[u].pb(sz(edges) - 2);
        adj[v].pb(sz(edges) - 1);
    }
    bool bfs() { //preparing the level graph
        fill(all(dist), n);
        queue <int> q;
        dist[s] = 0;
        q.push(s);
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(auto e : adj[u]) {
                if(edges[e].cap == T(0)) continue;
                int v = edges[e].v;
                if(dist[v] == n) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return dist[t] != n;
    }
    T dfs(int u, T flow) {
        if(u == t) return flow;
        for(; pt[u] < sz(adj[u]); pt[u]++) {
            int i = adj[u][pt[u]];
            int v = edges[i].v;
            T c = edges[i].cap;
            if(!c || dist[v] != dist[u] + 1) continue;
            T can_push = dfs(v, min(flow, c));
            //dont explicity mantain the amount of flow pushed; pushing is equiv.
            //to decreasing capacity, but increasing it in the reversed edge.
            if(can_push > 0) {
                edges[i].cap -= can_push;
                edges[i ^ 1].cap += can_push;
                return can_push;
            }
        }
        return T(0);
    }
    T max_flow() {
        T ans(0);
        while(bfs()) { //(while augmenting path exists)
            fill(all(pt), 0); //need to consider all edges again
            while(true) { //(while i can still find a path for the 'blocking flow')
                T flow = dfs(s, T(1e9)); //infinity
                if(flow > 0) ans += flow;
                else break;
            }
        }
        return ans;
    }
};

