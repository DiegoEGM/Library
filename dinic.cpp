template <class T = int>
struct Dinic {
    struct Edge {
        int u, v;
        T cap;
        Edge(int u_, int v_, T c_) : u(u_), v(v_), cap(c_) {}
    };
    bool scaling;
    int n, s, t;
    T lim;
    vi pt, dist;
    vector <Edge> edges;
    vector <vi> adj;
    Dinic(int n_, int s_, int t_, bool sc = false)  : n(n_), s(s_), t(t_),
                        pt(n + 1), dist(n + 1), adj(n + 1), scaling(sc) {}
    void add_edge(int u, int v, T cap) {
        edges.pb(Edge(u, v, cap));
        edges.pb(Edge(v, u, T(0)));
        adj[u].pb(sz(edges) - 2);
        adj[v].pb(sz(edges) - 1);
    }
    bool bfs() {
        fill(all(dist), n);
        queue <int> q;
        dist[s] = 0;
        q.push(s);
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(auto e : adj[u]) {
                if(edges[e].cap == T(0)) continue;
                if(scaling && edges[e].cap < lim) continue;
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
        for(lim = scaling ? (1 << 30) : 1; lim; lim /= 2) { //change to bigger inf?
            while(bfs()) {
                fill(all(pt), 0);
                while(true) {
                    T flow = dfs(s, T(1e9)); //change to bigger inf?
                    if(flow > 0) ans += flow;
                    else break;
                }
            }

        }
        return ans;
    }
};
