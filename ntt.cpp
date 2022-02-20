const int P = 998244353, G = 3; //119 * 2^{23} + 1.
//to-do: check other references for more mods and generators :)

int add(int x, int y) {
    x += y;
    if(x >= P) x -= P;
    return x;
}
int mul(int x, int y) {
    ll r = 1ll * x * 1ll * y;
    if(r >= P) r %= P;
    return int(r);
}
int binexp(int b, int e) {
    int ans = 1;
    while(e) {
        if(e % 2 == 1)
            ans = mul(ans, b);
        b = mul(b, b);
        e /= 2;
    }
    return ans;
}

void ntt(vector <int> &a, bool inv = false) {
    int n = a.size();
    int L = 31 - __builtin_clz(n);

    int w = binexp(G, (P - 1) / n);
    if(inv) w = binexp(w, P - 2);
    vi roots(n);

    roots[n / 2] = 1;
    for(int i = 1; i < n / 2; i++) {
        roots[i + n / 2] = mul(roots[i - 1 + n / 2], w);
    }
    for(int i = n / 2 - 1; i >= 1; i--) {
        roots[i] = roots[2 * i];
    }

    vi rev(n);
    for(int i = 0; i < n; i++) {
        rev[i] = rev[i / 2] / 2 + ((i & 1) << (L - 1));
    }
    for(int i = 0; i < n; i++)
        if(i < rev[i])
            swap(a[i], a[rev[i]]);

    for(int len = 1; len < n; len *= 2) {
        for(int i = 0; i < n; i += 2 * len) {
            for(int j = 0; j < len; j++) {
                int z = mul(a[i + j + len], roots[len + j]);
                a[i + j + len] = dec(a[i + j], z);
                a[i + j] = add(a[i + j], z);
            }
        }
    }

    int n_inv = binexp(n, P - 2);
    if(inv) {
        for(int i = 0; i < n; i++)
            a[i] = mul(a[i], n_inv);
    }
}
//(conv)
vi mult(vi a, vi b) {
    int L = 32 - __builtin_clz(sz(a) + sz(b) - 1);
    int N = 1 << L;
    while(a.size() < N) a.pb(0);
    while(b.size() < N) b.pb(0);
    ntt(a);
    ntt(b);
    vector <int> c(N);
    for(int i = 0; i < N; i++)
        c[i] = mul(a[i], b[i]);
    ntt(c, true);
    return c;
}


