template <class T>
T bexp(T a, ll p) {
    T x = T(1), y = a;
    while(p) {
        if(p % 2 == 1)
            x *= y;
        y *= y;
        p /= 2;
    }
    return x;
}

template <int MOD = mod>
struct ModInt {
    int val;

    ModInt(ll v = 0) {
        v %= MOD;
        if(v < 0) v += MOD;
        val = v;
    }

    ModInt inv() { return bexp<ModInt>(*this, MOD - 2); }

    ModInt operator + (ModInt o) { return ModInt(val + o.val); }
    ModInt operator - (ModInt o) { return ModInt(val - o.val); }
    ModInt operator * (ModInt o) { return ModInt(int((1ll * val * 1ll * o.val) % MOD)); }
    ModInt operator / (ModInt o) { return *this * o.inv(); }

    ModInt& operator += (ModInt o) { return *this = *this + o; }
    ModInt& operator -= (ModInt o) { return *this = *this - o; }
    ModInt& operator *= (ModInt o) { return *this = *this * o; }
    ModInt& operator /= (ModInt o) { return *this = *this / o; }

};

using mint = ModInt<>;

mint fact[N], invfact[N];
void init_fact(int n) {
    fact[0] = mint(1);
    for(int i = 1; i <= n; i++)
        fact[i] = fact[i - 1] * mint(i);

    invfact[n] = fact[n].inv();
    for(int i = n - 1; i >= 0; i--)
        invfact[i] = mint(i + 1) * invfact[i + 1];
}

mint nck(int n, int k) {
    if(k > n || n < 0 || k < 0) return mint(0);
    return fact[n] * invfact[n - k] * invfact[k];
}
//returns f(x) assuming sample = {f(1)...f(n)} and f is <= n - 1 degree polynomial
mint interpolate(vector<mint> &sample, mint x) {
    int n = sz(sample);
    init_fact(n); //comment out if previously generated
    mint fac = fact[n - 1];
    vector<mint> pref(n), suf(n);
    pref[0] = mint(1);
    for(int i = 2; i <= n; i++) {
        pref[i - 1] = pref[i - 2] * (x - (i - 1));
    }
    suf[n - 1] = mint(1);
    for(int i = n - 2; i >= 0; i--)
        suf[i] = suf[i + 1] * (x - (i + 2));
    mint ans = 0;
    for(int i = 1; i <= n; i++) {
        mint term = invfact[i - 1] * invfact[n - i];
        if((n - i) % 2 == 1)
            term = term * mint(-1);
        term *= pref[i - 1] * suf[i - 1] * sample[i - 1];
        ans += term;
    }
    return ans;
}


