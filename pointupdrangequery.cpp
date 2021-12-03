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
    void point_upd(base_t v, int p) { point_upd(v, p, 0, 0, n_ - 1); }
    void point_upd(base_t v, int p, int u, int l, int r) {
        if(l == r) {
            st[u] = node_t(v);
            return;
        }
        int md = (l + r)/2;
        if(p <= md)
            point_upd(p, v, 2 * u + 1, l, (l + r)/2);
        else
            point_upd(p, v, 2 * u + 1, md + 1, r);
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

};

struct Node {
    int val;
    Node(int x = 0) {
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
    int n;
    scanf("%d", &n);
    vi arr(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    SegmentTree<Node, int> test(arr);
    printf("%d\n", test.query(0, n - 1).val);
    test.point_upd(3, 0);
    printf("%d\n", test.query(0, n - 1).val);
    return 0;
}
