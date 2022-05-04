//get_potentials still needs testing. rest seems fine
//complexity = O(potentials + |F|dijsktra) = O(nm + F(m log m))

//MinCostFlow
template <class T = int>
struct MCF {
    int n, s, t;
    T bound; //how much flow do i want? do inf to just solve MCMF

    struct Edge {
        int u, v;
        T cap, cost;
        Edge(int u_, int v_, T c, T w) : u(u_), v(v_), cap(c), cost(w) {}
    };

    vector <Edge> edges;
    vector <vi> adj;
    vector <T> pot, dist;

    MCF(int n_, int s_, int t_,  T b = numeric_limits<T>::max()) : n(n_), s(s_), t(t_),
        bound(b), adj(n + 1), pot(n + 1), dist(n + 1) {}

    void add_edge(int u, int v, T c, T w) {
        edges.pb(Edge(u, v, c, w));
        edges.pb(Edge(v, u, 0, -w));
        adj[u].pb(sz(edges) - 2);
        adj[v].pb(sz(edges) - 1);
    }

    pair <T, T> mincost_flow() {
        T flow = 0;
        T cost = 0;
        get_potentials();
        vector <bool> vis(n + 1);
        vi comes_from(n + 1);

        while(bound) {
            //get augmenting path
            fill(all(vis), false);
            fill(all(dist), numeric_limits<T>::max());
            priority_queue <pair<T, int>, vector<pair<T, int>>, greater<>> pq;
            pq.push({0, s});
            while(!pq.empty()) {
                auto [d, u] = pq.top();
                pq.pop();
                if(vis[u]) continue;
                vis[u] = true;
                dist[u] = d;
                for(int i : adj[u]) {
                    int v = edges[i].v;
                    T c = edges[i].cap;
                    T w = edges[i].cost + pot[u] - pot[v];
                    if(c > 0 && !vis[v] && dist[u] + w < dist[v]) {
                        dist[v] = dist[u] + w;
                        comes_from[v] = i;
                        pq.push({dist[v], v});
                    }
                }
            }
            if(!vis[t]) break;
            T path_cost = 0;
            T path_flow = bound;
            for(int v = t; v != s; v = edges[comes_from[v]].u) {
                path_flow = min(path_flow, edges[comes_from[v]].cap);
                path_cost += edges[comes_from[v]].cost;
            }
            assert(path_flow > 0);
            path_cost *= path_flow;
            bound -= path_flow;
            for(int v = t; v != s; v = edges[comes_from[v]].u) {
                int i = comes_from[v];
                edges[i].cap -= path_flow;
                edges[i ^ 1].cap += path_flow;
            }
            flow += path_flow;
            cost += path_cost;
            for(int i = 1; i <= n; i++) {
                dist[i] = min(dist[i] + pot[i] - pot[s], 0);
            }
            pot = dist;
        }
        return {flow, cost};
    }

    //should find a problem where this is needed
    void get_potentials() {
        bool all_non_negative = true;
        for(int i = 0; i < sz(edges); i += 2)
            all_non_negative &= edges[i].cost >= 0;
        if(all_non_negative) return;

        for(int i = 1; i <= n; i++) {
            for(auto e : edges) {
                if(e.cap == 0) continue;
                if(pot[e.u] + e.cost < pot[e.v]) {
                    pot[e.v] = pot[e.u] + e.cost;
                    assert(i != n);
                }
            }
        }
    }
};

