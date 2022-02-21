template <class T, class C>
struct SparseTable {
    int n, l;
    C combine;
    vector <T> lg;
    vector <vector<T>> table;

    SparseTable(vector <T> a) {
        n = a.size();
        lg.resize(n + 1);
        for(int i = 2; i <= n; i++)
            lg[i] = lg[i >> 1] + 1;
        l = lg[n] + 1;
        table = vector<vector<T>> (n, vector<T>(l));
        for(int i = 0; i < n; i++)
            table[i][0] = a[i];
        for(int k = 1; k < l; k++)
            for(int i = 0; i + (1 << k) - 1 < n; i++)
                table[i][k] = combine(table[i][k - 1], table[i + (1 << (k - 1))][k - 1]);
    }

    T query(int l, int r) {
        int k = lg[r - l + 1];
        return combine(table[l][k], table[r - (1 << k) + 1][k]);
    }
};

template<class T>
struct Minimizer {
    T operator()(T x, T y) const { return min(x, y); }
};

template <class T>
using RMQ = SparseTable<T, Minimizer<T>>;
