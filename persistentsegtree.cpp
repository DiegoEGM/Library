/*
not as generic as the other codes but could be useful:
supports adding x at a position p on i-th tree and
keeping this as a new tree.
use like: trees[++ptr] = upd(trees[i], 1, n, p, x)
ignoring 'a' and 'build' this can work as an implicit
seg tree (i think :P)
*/
const int N = 2e5 + 3;

struct Node {
    Node *l, *r;
    ll sum;
    Node(ll x = 0) : sum(x), l(nullptr), r(nullptr) {}
};

using pnode = Node*;

pnode trees[N];
int n, q, ptr = 1;
int a[N];

inline ll gsum(pnode u) { return u ? u->sum : 0ll; }

pnode build(int l, int r) {
    if(l == r) return new Node(a[l]);
    pnode cur = new Node();
    int m = (l + r) / 2;
    cur->l = build(l, m);
    cur->r = build(m + 1, r);
    cur->sum = cur->l->sum + cur->r->sum;
    return cur;
}

ll query(const pnode u, int l, int r, int s, int e) {
    if(!u || s > r || e < l) return 0ll;
    if(s <= l && r <= e) return u->sum;
    int m = (l + r) / 2;
    return query(u->l, l, m, s, e) + query(u->r, m + 1, r, s, e);
}

pnode upd(const pnode u, int l, int r, int p, ll x) {
    if(l == r) return new Node(x);
    pnode cur = new Node();
    int m = (l + r) / 2;
    if(p <= m) {
        cur->l = upd(u->l, l, m, p, x);
        cur->r = u->r;
    }
    else {
        cur->l = u->l;
        cur->r = upd(u->r, m + 1, r, p, x);
    }
    cur->sum = gsum(cur->l) + gsum(cur->r);
    return cur;
}
