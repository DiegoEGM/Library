struct TWOSAT {
    int n;
    SCC G; //needs either tarjanscc.cpp or kosarajuscc.cpp
    vector <bool> assignment;
    TWOSAT(int n_) : n(n_), G(SCC(2 * n)), assignment(n + 1) {}

    void add_or(int u, bool tu, int v, bool tv) {
        u = 2 * u - tu;
        v = 2 * v - tv;
        int neg_u = 1 + ((u - 1)^1);
        int neg_v = 1 + ((v - 1)^1);
        G.add_edge(neg_u, v);
        G.add_edge(neg_v, u);
    }

    bool solve() {
        G.find_sccs();
        vi compo(2 * n + 1);
        for(int i = 0; i < sz(G.sccs); i++) {
            for(auto u : G.sccs[i]) {
                compo[u] = i;
            }
        }
        for(int u = 1; u <= n; u++) {
            if(compo[2 * u - 1] == compo[2 * u]) return false;
            //assuming reverse topological ordering in G.sccs!
            assignment[u] = compo[2 * u] > compo[2 * u - 1];
        }
        return true;
    }
};

