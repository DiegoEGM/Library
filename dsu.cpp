struct dsu {
    int n;
    vi info;
    dsu(int n) : n(n), info(n + 1, -1) {}
    int tag(int u) {
        return info[u] < 0 ? u : info[u] = tag(info[u]);
    }
    bool join(int u, int v) {
        u = tag(u), v = tag(v);
        if(u == v) return false;
        if(info[u] < info[v]) swap(u, v);
        info[v] += info[u];
        info[u] = v;
        return true;
    }
};
