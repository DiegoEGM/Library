//Segment tree with range queries but only point updates
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
        st[u] = st[2 * u + 1] + st[2 * u + 2];
    }
    void point_upd(int p, base_t v) { point_upd(p, v, 0, 0, n_ - 1); }
    void point_upd(int p, base_t v, int u, int l, int r) {
        if(l == r) {
            st[u] = node_t(v); //change value query. can change for add, etc.
            return;
        }
        int md = (l + r)/2;
        if(p <= md)
            point_upd(p, v, 2 * u + 1, l, md);
        else
            point_upd(p, v, 2 * u + 2, md + 1, r);
        st[u] = st[2 * u + 1] + st[2 * u + 2];
    }
    node_t query(int s, int e) {
        if(s > e) return node_t();
        return query(s, e, 0, 0, n_ - 1);
    }
    node_t query(int s, int e, int u, int l, int r) {
        if(e < l || r < s) return node_t(); //neutral value for Node's +
        if(s <= l && r <= e) {
            return st[u];
        }
        int md = (l + r) / 2;
        return query(s, e, 2 * u + 1, l, md) + query(s, e, 2 * u + 2, md + 1, r);
    }
    //pass F as lambda
    template <class F>
    int first_index(int s, int e, F f) {
        if(s > e) return -1;
        return first_index<F>(s, e, 0, 0, n_ - 1, f);
    }
    template <class F>
    int first_index(int s, int e, int u, int l, int r, F f) {
        if(e < l || r < s) return -1;
        int md = (l + r) / 2;
        if(s <= l && r <= e) {
            if(!f(st[u])) return -1;
            if(l == r) return l;
            if(f(st[2 * u + 1]))
                return first_index(s, e, 2 * u + 1, l, md, f);
             return first_index(s, e, 2 * u + 2, md + 1, r, f);
        }
        int left_attempt = first_index(s, e, 2 * u + 1, l, md, f);
        if(left_attempt != -1) return left_attempt;
        return first_index(s, e, 2 * u + 2, md + 1, r, f);
    }
    //pass F as lambda
    template <class F>
    int last_index(int s, int e, F f) {
        if(s > e) return -1;
        return last_index<F>(s, e, 0, 0, n_ - 1, f);
    }
    template <class F>
    int last_index(int s, int e, int u, int l, int r, F f) {
        if(e < l || r < s) return -1;
        int md = (l + r) / 2;
        if(s <= l && r <= e) {
            if(!f(st[u])) return -1;
            if(l == r) return l;
            if(f(st[2 * u + 2]))
                return last_index(s, e, 2 * u + 2, md + 1, r, f);
             return last_index(s, e, 2 * u + 1, l, md, f);
        }
        int right_attempt = last_index(s, e, 2 * u + 2, md + 1, r, f);
        if(right_attempt != -1) return right_attempt;
        return last_index(s, e, 2 * u + 1, l, md, f);
    }
};

struct Node {

    Node() { //should take a 'base_t' element where base_t is the one you use on the segtree
    }

    Node operator + (Node other) {
    }
};
