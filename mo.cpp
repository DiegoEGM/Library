#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
complexity is O((N + Q) sqrt(N))
*/

const int N = 1e5 + 3;
int n, q, ans;

/*if root = sqrt(n) takes too much, consider making it
const root = sqrt(maxn) e.g 316 for 10^5 */
/* its also better n/sqrt(q),
see this comment https://codeforces.com/blog/entry/61203?#comment-451304 */
int root;

struct query {
    int l, r, i;
    query() {}
    query(int l_, int r_, int i_) : l(l_), r(r_), i(i_) {}
};

/* to not make many divisions, consider also
storing a value query.block = query.l / root and
chechking those.
another speed up is using a.r > b.r if the block is
odd and a.r < b.r if its even.
*/
bool cmp(query &a, query &b) {
    if(a.l / root == b.l / root)
        return a.r < b.r;
    return a.l < b.l;
}

int a[N];

void add(int i) {

}

void del(int i) {

}

int answer[N];
query queries[N];

void read() {
    cin >> n >> q;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for(int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        queries[i] = query(l, r, i);
    }
}

void solve() {
    root = sqrt(n);

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

int main()
{
    #ifndef LOCAL
    ios_base::sync_with_stdio(false);
    cin.tie(0)
    #endif

    read();
    solve();


    return 0;
}

/*
Extra notes:
https://codeforces.com/blog/entry/43230 mo on trees:
should i make this another template, or just modify this file when needed?
do preorder traversal with in times and out times.
do things like a[in[node]] = a[out[node]] = node.
then queries for paths u-> v are:
if u is ancestor of v then its a mo query in [in[u], in[v]]
otherwise ifu comes before v in traversal, its [out[u], in[v]] U [in(lca(u,v)), in[lca(u,v)]
that is, a mo query [out[u], in[v]] BUT we need to consider the extra contribution
of the lca. also another modifier its that we only consider a node that shows up exactly once.

*/

