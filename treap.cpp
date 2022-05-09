mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct node {
    int val, prio;
    node *l, *r;

    //for range queries
    int subtree_sz;
    ll sum;
    bool flip = false;

    node(int x) {
        prio = rng();
        sum = val = x;
        l = r = nullptr;
        subtree_sz = 1;
    }
};

using pnode = node*;
pnode head;

int get_sz(pnode u) { return u ? u->subtree_sz : 0; }
ll get_sum(pnode u) { return u ? u->sum : 0; }

void do_flip(pnode u) { if(u) u->flip ^= true; }

void upd(pnode u) {
    if(!u) return;
    u->subtree_sz = 1 + get_sz(u->l) + get_sz(u->r);
    u->sum = u->val + get_sum(u->l) + get_sum(u->r);
}

//lazy propagation.
//can be modified to support more than just flipping.
void push(pnode u) {
    if(!u || !u->flip) return;
    u->flip = false;
    swap(u->l, u->r);
    do_flip(u->l); do_flip(u->r);
}

//split by size, first k nodes go to l, the rest go to r.
//works for both explicit and implicit
void split_sz(pnode t, pnode &l, pnode &r, int k) {
    push(t);
    if(!t)
        l = r = nullptr;
    else if(1 + get_sz(t->l) <= k) {
        l = t;
        split_sz(t->r, t->r, r, k - 1 - get_sz(t->l));
    }
    else {
        r = t;
        split_sz(t->l, l, t->l, k);
    }
    upd(l); upd(r);
}


void join(pnode &t, pnode l, pnode r) {
    push(l); push(r);
    if(!l || !r)
        t = l ? l : r;
    else if(l->prio > r->prio) {
        t = l; join(t->r, l->r, r);
    }
    else {
        t = r; join(t->l, l, r->l);
    }
    upd(t);
}

void trav(pnode t) {
    if(!t) return;
    push(t);
    trav(t->l);
    cout << t->val << " ";
    trav(t->r);
}
//-----IMPLICIT TREAP OPERATIONS-----

//put x as p-th node in the treap's in-order traversal (basically in p-th position of array).
//p is 1-indexed.
void insert_at_position(int p, int x) {
    assert(p > 0);
    pnode l, r;
    split_sz(head, l, r, p - 1);
    join(l, l, new node(x));
    join(head, l, r);
}

//erase p-th value in traversal. 1-indexed.
void delete_at_position(int p) {
    assert(p > 0);
    pnode l, r, m;
    split_sz(head, l, r, p);
    split_sz(l, l, m, p - 1);
    join(head, l, r);
}

//1-index. flips [l_, r_] on implicit treap.
void flip_range(int l_, int r_) {
    pnode l, r, m;
    split_sz(head, l, r, r_);
    split_sz(l, l, m, l_ - 1);
    m->flip ^= true;
    join(l, l, m);
    join(head, l, r);
}

//-----EXPLICIT TREAP OPERATIONS-----

//values <= k go to l, and values > k go to r.
void split_val(pnode t, pnode &l, pnode &r, int k) {
    push(t);
    if(!t)
        l = r = nullptr;
    else if(t->val <= k) {
        l = t;
        split_val(t->r, t->r, r, k);
    }
    else {
        r = t;
        split_val(t->l, l, t->l, k);
    }
    upd(l); upd(r);
}

void insert_in_order(int x) {
    pnode l, r, m;
    split_val(head, l, r, x);
    split_val(l, l, m, x - 1);
    if(!m) {
        m = new node(x);
    }
    else {
        //do something if x is already in,
        //e.g. increase frequency.
    }
    join(l, l, m);
    join(head, l, r);
    return;
}

void delete_in_order(int x) {
    pnode l, r, m;
    split_val(head, l, r, x);
    split_val(l, l, m, x - 1);
    join(head, l, r);
}

