//careful: only tested in https://codeforces.com/contest/704/problem/D
//needs dinic.cpp

template <class T>
struct MaxFlowLowerBounds {
    static constexpr T T_inf = numeric_limits<T>::max();
    Dinic <T> G, G_new;
    T sum_demands;
    vector <T> out, in, lb;
    int n, s, t, ss, tt;

    MaxFlowLowerBounds(vector <pair<pii, pair<T, T>>> &edges, int n_, int s_, int t_) {
        n = n_ + 2, s = s_, t = t_;
        ss = n - 1, tt = n;
        sum_demands = 0;
        G = Dinic <T> (n, ss, tt);
        out.resize(n-1), in.resize(n-1), lb.resize(sz(edges));

        for(int i = 0; i < sz(edges); i++) {
            G.add_edge(edges[i].f.f, edges[i].f.s, edges[i].s.s - edges[i].s.f);
            assert(i < sz(lb));
            lb[i] = edges[i].s.f;
            sum_demands += edges[i].s.f;
            in[edges[i].f.s] += edges[i].s.f;
            out[edges[i].f.f] += edges[i].s.f;
        }

        G.add_edge(t, s, T_inf);

        for(int i = 1; i <= n - 2; i++) {
            if(in[i]) {
                G.add_edge(ss, i, in[i]);
            }
            if(out[i]) {
                G.add_edge(i, tt, out[i]);
            }
        }
    }
    T max_flow() {
        T mf = G.max_flow();
        if(mf != sum_demands) {
            return -1; //no feasible flow
        }
        G_new = Dinic <T> (n - 2, s, t);
        T fixed_sent = 0;

        for(int i = 0; i < sz(G.edges); i += 2) {
            int u = G.edges[i].u;
            int v = G.edges[i].v;
            T flow = G.edges[i^1].cap;
            if(u == t && v == s) {
                fixed_sent = flow;
            }
            if(u == ss || v == tt || (u == t && v == s)) continue;
            T cap = G.edges[i].cap + G.edges[i^1].cap;
            T demand = lb[i / 2];
            flow += demand;
            cap += demand;
            G_new.add_edge(u, v, cap - flow);
            G_new.edges.back().cap = flow - demand;
        }
        mf = G_new.max_flow();
        return fixed_sent + mf;
    }
};

