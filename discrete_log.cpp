//finds x such that a^x = b (modulo mod)
//returns -1 if it doesnt find any.
//to-do: make it so i can get minimum?
//if mod is known from the start, consider using mint template or smthing
//can a be 0? what is 0^0 defined as? might depend on the problem
ll discrete_log(ll a, ll b, ll mod) {
    ll SQ = sqrt(mod) + 1;
    vector <pair<ll, int>> big;
    vector <ll> ap = {1};
    ll a_pw = 1ll;
    for(int i = 1; i <= SQ; i++) {
        a_pw *= a; if(a_pw >= mod) a_pw %= mod;
        ap.pb(a_pw);
    }
    ll cur = 1ll;
    for(int i = 0; i <= SQ; i++) {
        big.pb({cur, i});
        cur *= a_pw; if(a_pw >= mod) a_pw %= mod;
    }
    sort(all(big));
    for(int i = 0; i <= SQ; i++) {
        cur = ap[i] * b; if(cur >= mod) cur %= mod;
        int j = lower_bound(all(big), pair<ll, int>{cur, 0}) - big.begin();
        if(j < SQ && big[j].f == cur) {
            return SQ * big[j].s - i;
        }
    }
    return -1;
}
