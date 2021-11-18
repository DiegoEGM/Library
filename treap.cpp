#include <bits/stdc++.h>
#define ft first
#define sd second
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;


/*
yet another treap. i suppose this one looks good?
not fully tested.
verification for the explicit type: https://www.spoj.com/problems/ORDERSET/
verification for flipping: (freddy y los hotcakes en omegaup)
verification for more stuff: ???
*/

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct node {
    //main things:
    int val, prio;
    node *l, *r;
    //for range queries
    int sz; ll sum;
    bool flip = false;
    node(int x) {
        prio = rng();
        sum = val = x;
        l = r = nullptr;
        sz = 1;
    }
};

using pnode = node*;

int getsz(pnode u) { return u ? u->sz : 0; }
ll getsum(pnode u) { return u ? u->sum : 0; }

void doflip(pnode u) { if(u) u->flip ^= true; }

void upd(pnode u) {
    if(!u) return;
    u->sz = 1 + getsz(u->l) + getsz(u->r);
    u->sum = u->val + getsum(u->l) + getsum(u->r);
}

void push(pnode u) {
    if(!u || !u->flip) return;
    u->flip = false;
    swap(u->l, u->r);
    doflip(u->l); doflip(u->r);
}

//split by size, first k nodes go to l, the rest go to r. works for both explicit and implicit
void splitsz(pnode t, pnode &l, pnode &r, int k) {
    push(t);
    if(!t)
        l = r = nullptr;
    else if(1 + getsz(t->l) <= k) {
        l = t;
        splitsz(t->r, t->r, r, k - 1 - getsz(t->l));
    }
    else {
        r = t;
        splitsz(t->l, l, t->l, k);
    }
    upd(l); upd(r);
}

//split by value (assumes treap is ordered: this is for explicit treap)
//values <= k go l, > k goes to right
void splitval(pnode t, pnode &l, pnode &r, int k) {
    push(t);
    if(!t)
        l = r = nullptr;
    else if(t->val <= k) {
        l = t;
        splitval(t->r, t->r, r, k);
    }
    else {
        r = t;
        splitval(t->l, l, t->l, k);
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

pnode head;

//insertion and deletion for an implicit treap (array like thing, no order)
void insert_at_position(int p, int x) { //put x as the pth node in the traversal
    pnode l, r;
    assert(p > 0);
    splitsz(head, l, r, p - 1);
    join(l, l, new node(x));
    join(head, l, r);
}

void delete_at_position(int p) { //erase pth value
    pnode l, r, m;
    splitsz(head, l, r, p);
    splitsz(l, l, m, p - 1);
    join(head, l, r);
}

//insertion and deletion for a treap that actually behaves like a binary search tree, ordered set
void insert_in_order(int x) {
    pnode l, r, m;
    splitval(head, l, r, x);
    splitval(l, l, m, x - 1);
    if(!m) {
        m = new node(x);
    }
    join(l, l, m);
    join(head, l, r);
    return;
}

void delete_in_order(int x) {
    pnode l, r, m;
    splitval(head, l, r, x);
    splitval(l, l, m, x - 1);
    join(head, l, r);
}
//////////
void flip_range(int l_, int r_) {
    pnode l, r, m;
    splitsz(head, l, r, r_);
    splitsz(l, l, m, l_ - 1);
    m->flip ^= true;
    join(l, l, m);
    join(head, l, r);
}

int main()
{

    return 0;
}
