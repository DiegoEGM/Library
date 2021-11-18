#ifdef LOCAL
    #include "debug.h"
#else
    #define dbg(...) 0
#endif

#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define inf INT_MAX
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int) (x).size())
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const int N = 2e5 + 3;
const int mod = 1e9 + 7;

template <typename T>
struct SparseTable {
    int n, L;
    vector <T> lg;
    T ID;
    vector <vector<T>> table;

    T comb(T x, T y) {
        return x + y;
    }

    SparseTable(vector <T> a, T ID_) {
        n = a.size();
        lg.resize(n + 1);
        dbg(n);
        ID = ID_;
        for(int i = 2; i <= n; i++)
            lg[i] = lg[i >> 1] + 1;
        L = lg[n] + 1;
        dbg(L);
        table = vector<vector<T>> (n, vector<T>(L));
        for(int i = 0; i < n; i++)
            table[i][0] = a[i];
        for(int k = 1; k < L; k++)
            for(int i = 0; i + (1 << k) - 1 < n; i++)
                table[i][k] = comb(table[i][k - 1], table[i + (1 << (k - 1))][k - 1]);
    }

    T query(int l, int r) {
        int k = lg[r - l + 1];
        return comb(table[l][k], table[r - (1 << k) + 1][k]);
    }

    T query2(int l, int r) { //not idempodent
        int k = r - l + 1;
        T ret = ID;
        for(int i = 0; i < L; i++)
            if(k & (1 << i)) {
                ret = comb(ret, table[l][i]);
                l += (1 << i);
            }
        assert(l == r + 1);
        return ret;
    }

};

int main() {
    vector <int> a = {10, 5, 9, 6, 4, 7};
    SparseTable <int> X(a, 0);

    for(int i = 0; i < 6; i++)
        for(int j = i; j < 6; j++)
            dbg(i, j, X.query2(i, j));
    return 0;
}
