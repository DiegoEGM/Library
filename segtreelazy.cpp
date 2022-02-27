template <class node_t, class lazy_t, class base_t>
struct SegmentTree {
    int n_;
    vector <node_t> st;
    vector <lazy_t> lzy;
    SegmentTree(vector <base_t> &a) {
        n_ = sz(a);
        st.resize(4 * n_);
        lzy.resize(4 * n_);
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
    void push(int u, int l, int r) {
        if(lzy[u].is_null())
            return;
        st[u] = st[u] + lzy[u];
        if(l != r) {
            lzy[2 * u + 1] = lzy[2 * u + 1] + lzy[u];
            lzy[2 * u + 2] = lzy[2 * u + 2] + lzy[u];
        }
        lzy[u] = lazy_t();
    }
    void upd(int s, int e, lazy_t v) {
        if(s > e) return;
        upd(s, e, v, 0, 0, n_ - 1);
    }
    void upd(int s, int e, lazy_t v, int u, int l, int r) {
        push(u, l, r);
        if(e < l || r < s) return;
        if(s <= l && r <= e) {
            lzy[u] = lzy[u] + v;
            push(u, l, r);
            return;
        }
        int md = (l + r)/2;
        upd(s, e, v, 2 * u + 1, l, md);
        upd(s, e, v, 2 * u + 2, md + 1, r);
        st[u] = st[2 * u + 1] + st[2 * u + 2];
    }
    node_t query(int s, int e) {
        if(s > e) return node_t();
        return query(s, e, 0, 0, n_ - 1);
    }
    node_t query(int s, int e, int u, int l, int r) {
        push(u, l, r);
        if(e < l || r < s) return node_t();
        if(s <= l && r <= e) return st[u];
        int md = (l + r) / 2;
        return query(s, e, 2 * u + 1, l, md) + query(s, e, 2 * u + 2, md + 1, r);
    }
    template <class F>
    int first_index(int s, int e, F f) {
        if(s > e) return -1;
        return first_index<F>(s, e, 0, 0, n_ - 1, f);
    }
    template <class F>
    int first_index(int s, int e, int u, int l, int r, F f) {
        push(u, l, r);
        if(e < l || r < s) return -1;
        int md = (l + r) / 2;
        if(s <= l && r <= e) {
            if(!f(st[u]))  return -1;
            if(l == r) return l;
            push(2 * u + 1, l, md);
            push(2 * u + 2, md + 1, r);
            if(f(st[2 * u + 1])) {
                return first_index(s, e, 2 * u + 1, l, md, f);
            }
             return first_index(s, e, 2 * u + 2, md + 1, r, f);
        }
        int left_attempt = first_index(s, e, 2 * u + 1, l, md, f);
        if(left_attempt != -1) return left_attempt;
        return first_index(s, e, 2 * u + 2, md + 1, r, f);
    }
    template <class F>
    int last_index(int s, int e, F f) {
        if(s > e) return -1;
        return last_index<F>(s, e, 0, 0, n_ - 1, f);
    }
    template <class F>
    int last_index(int s, int e, int u, int l, int r, F f) {
        push(u, l, r);
        if(e < l || r < s) return -1;
        int md = (l + r) / 2;
        if(s <= l && r <= e) {
            if(!f(st[u])) return -1;
            if(l == r) return l;
            push(2 * u + 1, l, md);
            push(2 * u + 2, md + 1, r);
            if(f(st[2 * u + 2]))
                return last_index(s, e, 2 * u + 2, md + 1, r, f);
             return last_index(s, e, 2 * u + 1, l, md, f);
        }
        int right_attempt = last_index(s, e, 2 * u + 2, md + 1, r, f);
        if(right_attempt != -1) return right_attempt;
        return last_index(s, e, 2 * u + 1, l, md, f);
    }
};

struct Lazy {
    Lazy() {

    }

    Lazy operator + (Lazy other) { //combine lazys

    }
    bool is_null() { //no need to propagate

    }
};

struct Node {
    Node() {

    }
    Node operator + (Node other) { //merge

    }
    Node operator + (Lazy other) { //apply lazy

    }
};


