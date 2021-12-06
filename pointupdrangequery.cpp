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

const int N = 1e5+3;

//Point update, range query

template <class node_t, class base_t>
struct SegmentTree {
    int n_;
    vector <node_t> st;
    SegmentTree(vector <base_t> &a) {
        n_ = sz(a);
        st.resize(4 * n_);
        build(0, 0, n_ - 1, a);
    }
    void build(int u, int l, int r, vector <base_t> &a) {
        if(l == r) {
            st[u] = node_t(a[l]);
            return;
        }
        int md = (l + r) / 2;
        build(2 * u + 1, l, md, a);
        build(2 * u + 2, md + 1, r, a);
        st[u] = node_t(st[2 * u + 1], st[2 * u + 2]);
    }
    void point_upd(int p, base_t v) { point_upd(p, v, 0, 0, n_ - 1); }
    void point_upd(int p, base_t v, int u, int l, int r) {
        if(l == r) {
            st[u] = node_t(v);
            return;
        }
        int md = (l + r)/2;
        if(p <= md)
            point_upd(p, v, 2 * u + 1, l, md);
        else
            point_upd(p, v, 2 * u + 2, md + 1, r);
        st[u] = node_t(st[2 * u + 1], st[2 * u + 2]);
    }
    node_t query(int s, int e) {
        if(s > e) return node_t();
        return query(s, e, 0, 0, n_ - 1);
    }
    node_t query(int s, int e, int u, int l, int r) {
        if(e < l || r < s) return node_t(); //needs some null thing
        if(s <= l && r <= e) return st[u];
        int md = (l + r) / 2;
        return query(s, e, 2 * u + 1, l, md) + query(s, e, 2 * u + 2, md + 1, r);
    }
    //need to generalize this to some monotone bool func. just does https://cses.fi/problemset/task/1143 for now
    int first_index(int v, int s, int e) { return first_index(s, e, 0, 0, n_ - 1, v); }
    int first_index(int s, int e, int u, int l, int r, int v) {
        if(e < l || r < s) return -1;
        int md = (l + r) / 2;
        if(s <= l && r <= e) {
            if(st[u].val < v) return -1;
            if(l == r) return l;
            if(st[2 * u + 1].val >= v)
                return first_index(s, e, 2 * u + 1, l, md, v);
             return first_index(s, e, 2 * u + 2, md + 1, r, v);
        }
        int left_attempt = first_index(s, e, 2 * u + 1, l, md, v);
        if(left_attempt != -1) return left_attempt;
        return first_index(s, e, 2 * u + 1, md + 1, r, v);
    }

};

struct Node {
    ll val;
    Node(ll x = 0) {
        val = x;
    }
    Node(Node a, Node b) {
        val = a.val + b.val;
    }
    Node operator + (Node other) {
        return Node(val + other.val);
    }
};


int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    vi a(n);
    for(auto &x : a)
        scanf("%d", &x);
    SegmentTree<Node, int> ST(a);

    while(q--) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        if(a == 1) {
            ST.point_upd(b - 1, c);
        }
        else {
            printf("%lld\n", ST.query(b - 1, c - 1));
        }
    }
    return 0;
}
