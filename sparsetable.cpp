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

template <class T, class C>
struct SparseTable {
    int n, L;
    C combine;
    vector <T> lg;
    vector <vector<T>> table;

    SparseTable(vector <T> a) {
        n = a.size();
        lg.resize(n + 1);
        for(int i = 2; i <= n; i++)
            lg[i] = lg[i >> 1] + 1;
        L = lg[n] + 1;
        table = vector<vector<T>> (n, vector<T>(L));
        for(int i = 0; i < n; i++)
            table[i][0] = a[i];
        for(int k = 1; k < L; k++)
            for(int i = 0; i + (1 << k) - 1 < n; i++)
                table[i][k] = combine(table[i][k - 1], table[i + (1 << (k - 1))][k - 1]);
    }

    T query(int l, int r) {
        int k = lg[r - l + 1];
        return combine(table[l][k], table[r - (1 << k) + 1][k]);
    }
};

template<typename T>
struct Minimizer {
    T operator()(T x, T y) const { return min(x, y); }
};

int main() {
    vector <int> lol = {1, 2, 3};
    SparseTable <int, Minimizer<int>> st(lol);

    return 0;
}

