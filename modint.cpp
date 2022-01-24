#include <bits/stdc++.h>
#define pb push_back
#define inf INT_MAX
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int) (x).size())
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pl = pair<ll, ll>;
using vi = vector<int>;

const int N = 2e5 + 3;
const int mod = 1e9 + 7;

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
    ModInt(int v = 0) {
        val = v;
        if(val >= mod) val -= mod;
        if(val < 0) val += mod;
       // assert(val >= 0 && val < mod);
    }

    ModInt inv() { return bexp<ModInt>(*this, mod - 2); }

    ModInt operator + (ModInt o) { return ModInt(val + o.val); }
    ModInt operator - (ModInt o) { return ModInt(val - o.val); }
    ModInt operator * (ModInt o) { return ModInt(int((1ll * val * 1ll * o.val) % mod)); }
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
    if(k > n || n < 0) return mint(0);
    return fact[n] * invfact[n - k] * invfact[k];
}


mint interpolate(vector<mint> &sample, mint x) {
    int n = sz(sample);
    init_fact(n); //if its not generated before
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

int main() {
    return 0;
}

