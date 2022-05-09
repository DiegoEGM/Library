template <class T>
struct Fenwick2D {
    int n, m;
    vector <vector<T>> tree;
    Fenwick2D(int n_, int m_) : n(n_), m(m_), tree(n + 1, vector<T>(m + 1)) {}
    T get(int i, int j) {
        if(i <= 0 || i > n || j <= 0 || j > m) return T(0);
        T sum = T(0);
        for(; i; i -= (i & -i))
            for(int k = j; k; k -= (k & -k))
                sum += tree[i][k];
        return sum;
    }
    void upd(int i, int j, T val) {
        for(; i <= n; i += (i & -i))
            for(int k = j; k <= m; k += (k & -k))
                tree[i][k] += val;
    }
    T query(int a, int b, int c, int d) { //(a, b) is upper left, (c, d) is lower right
        return get(c, d) + get(a - 1, b - 1) - get(c, b - 1) - get(a - 1, d);
    }
};
