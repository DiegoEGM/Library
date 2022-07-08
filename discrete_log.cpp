//returns minimum x such that a^x = b mod m, assuming 0^0 = 1,
//and -1 if it doesnt exist.
//O(sqrt(m) log m) 
//tested: https://judge.yosupo.jp/submission/94862
ll discrete_log(ll a, ll b, ll m) {
    a %= m; b %= m;
    int shift = 0;
    ll g, coef = 1;
    while((g = gcd(a, m)) > 1) { //converting to coprime case
        if(b == coef) return shift;
        if(b % g != 0) return -1;
        b /= g;
        m /= g;
        (coef *= a / g) %= m;
        shift++;
    }
    ll SQ = sqrtl(m) + 1;
    vector <pair<ll, int>> small = {{b, 0}};
    ll a_pw = 1ll;
    for(int i = 1; i <= SQ; i++) {
        (a_pw *= a) %= m;
        small.pb({(a_pw * b) % m, -i});
    }
    sort(all(small));
    ll cur = coef;
    for(int i = 1; i <= SQ; i++) {
        (cur *= a_pw) %= m;
        int j = lower_bound(all(small), pair<ll, int>{cur, -inf}) - small.begin();
        if(j <= SQ && small[j].f == cur) {
            return (SQ * 1ll * i + small[j].s) + shift;
        }
    }
    return -1;
}
