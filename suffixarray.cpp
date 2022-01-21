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
using ld = long double;

//if memory limit low change to segment tree
template <typename T>
struct SparseTable {
    int n, L;
    vector <T> lg;
    T ID;
    vector <vector<T>> table;

    T comb(T x, T y) {
        return min(x, y);
    }

    SparseTable(vector <T> a, T ID_) {
        n = a.size();
        lg.resize(n + 1);
        ID = ID_;
        for(int i = 2; i <= n; i++)
            lg[i] = lg[i >> 1] + 1;
        L = lg[n] + 1;
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
};

template <class T = string>
struct SuffixArray {
    int n;
    vi p, c;
    vi lcp;

    SuffixArray(T s) {
        s.pb(*min_element(all(s)) - 1);
        n = sz(s);
        p.resize(n), c.resize(n);
        vi new_c(n), new_p(n), ptr(n);

        iota(all(p), 0);
        sort(all(p), [&](const int &i, const int &j) { return s[i] < s[j]; });

        c[p[0]] = 0;
        for(int i = 1; i < n; i++)
            c[p[i]] = c[p[i - 1]] + (s[p[i]] != s[p[i - 1]]);

        int k = 0;
        while((1 << k) < n) {
            if(c[p[n - 1]] == n - 1) break;
            for(int i = 0; i < n; i++)
                p[i] = (p[i] - (1 << k) + n) % n;
            fill(all(ptr), 0);
            for(int i = 0; i < n; i++) ptr[c[i] + 1]++;
            partial_sum(all(ptr), ptr.begin());
            for(int i = 0; i < n; i++) new_p[ptr[c[p[i]]]++] = p[i];
            p = new_p;

            new_c[p[0]] = 0;
            for(int i = 1; i < n; i++) {
                pii prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
                pii cur = {c[p[i]], c[(p[i] + (1 << k)) % n]};
                new_c[p[i]] = new_c[p[i - 1]] + (prev != cur);
            }
            c = new_c;
            k++;
        }
        buildLCP(s);
    }

    void buildLCP(T &s) {
        lcp.resize(n - 1);
        int k = 0;
        for(int i = 0; i + 1 < n; i++) {
            int pos_i = c[i];
            int j = p[pos_i - 1];
            while(s[i + k] == s[j + k]) k++;
            lcp[pos_i - 1] = k;
            if(k) k--;
        }
    }

    template <class RMQ>
    int LCP(int i, int j, RMQ &rmq) {
        if(i == j) return n - i - 1;
        int l = c[i];
        int r = c[j];
        if(l > r) swap(l, r);
        return rmq.query(l, r - 1);

    }

};

int main() {
    return 0;
}
