#include <bits/stdc++.h>
using namespace std;


template <class T>
struct Fenwick2D {
    vector <vector<T>> tree;
    int n_, m_;
    Fenwick2D(int n, int m) : n_(n), m_(m), tree(n + 1, vector<T>(m + 1)) {}
    T get(int i, int j) {
        if(i <= 0 || i > n_ || j <= 0 || j > m_) return T(0);
        T sum = T(0);
        for(; i; i -= (i & -i))
            for(int k = j; k; k -= (k & -k))
                sum += tree[i][k];
        return sum;
    }
    void upd(int i, int j, T val) {
        for(; i <= n_; i += (i & -i))
            for(int k = j; k <= m_; k += (k & -k))
                tree[i][k] += val;
    }
    T query(int a, int b, int c, int d) { //(a, b) is upper left, (c, d) is lower right
        return get(c, d) + get(a - 1, b - 1) - get(c, b - 1) - get(a - 1, d);
    }
};

int main() {
    return 0;
}
