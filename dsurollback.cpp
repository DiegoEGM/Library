struct dsu_rollback {
    int n, compos;
    vi h, rep;
    struct Change {
        int u, hu, v;
        Change(int u_, int hu_, int v_) : u(u_), hu(hu_), v(v_) {}
    };
    stack <Change> S;
    dsu_rollback(int n_ = 1) : n(n_), compos(n), h(n + 1), rep(n + 1) {
        iota(all(rep), 0);
    }
    int tag(int u) {
        if(u == rep[u]) return u;
        return tag(rep[u]);
    }
    bool join(int u, int v) {
        u = tag(u);
        v = tag(v);
        if(u == v) return false;
        if(h[v] > h[u])
            swap(u, v);
        S.push(Change(u, h[u], v));
        rep[v] = u;
        if(h[u] == h[v])
            h[u]++;
        compos--;
        return true;
    }
    int timer() { return int(sz(S)); }
    void rollback(int t) {
        while(sz(S) > t) {
            Change cur = S.top();
            S.pop();
            rep[cur.v] = cur.v;
            h[cur.u] = cur.hu;
            compos++;
        }
    }
};
