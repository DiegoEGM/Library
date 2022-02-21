struct query {
    int l, r, i;
    query() {}
    query(int l_, int r_, int i_) : l(l_), r(r_), i(i_) {}
} queries[N];

int answer[N];

int n, q, ans;

void add(int i) {

}

void del(int i) {

}

void solve() {
    int root = sqrt(n);
    auto cmp = [&](const query &a, query &b) -> bool {
        if(a.l / root == b.l / root) return a.r < b.r;
        return a.l < b.l;
    };
    sort(queries, queries + q, cmp);
    int mol = queries[0].l, mor = queries[0].l - 1;

    for(int i = 0; i < q; i++) {
        int l = queries[i].l, r = queries[i].r;

        while(mol < l) del(mol++);
        while(mol > l) add(--mol);
        while(mor < r) add(++mor);
        while(mor > r) del(mor--);

        answer[queries[i].i] = ans;
    }

    for(int i = 0; i < q; i++) {
        cout << answer[i] << "\n";
    }
}
/*
Bonus: Mo on trees. (should i template that?)
do preorder traversal with in times and out times.
do things like a[in[node]] = a[out[node]] = node.
then queries for paths u-> v are:
if u is ancestor of v then its a mo query in [in[u], in[v]]
otherwise if u comes before v in traversal, its [out[u], in[v]] U [in(lca(u,v)), in[lca(u,v)]]
that is, a mo query [out[u], in[v]] BUT we need to consider the extra contribution
of the lca. also another modifier its that we only consider a node that shows up exactly once.
(so, also remove from ans if it comes twice)
*/

