#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int mod = 1e9 + 7;
const int N = 3e5 + 3;

ll binexp(ll b, ll e) {
    ll x = 1ll;
    ll y = b % mod;
    while(e) {
        if(e % 2 == 1)
            x = (x * y) % mod;
        y = (y * y) % mod;
        e /= 2;
    }
    return x;
}

ll n;
ll fact[N], invfact[N];

void init(int n_) {
    fact[0] = 1ll;
    for(int i = 1; i <= n_; i++)
        fact[i] = (fact[i - 1] * 1ll * i) % mod;

    invfact[n_] = binexp(fact[n_], mod - 2);

    for(int i = n_ - 1; i >= 0; i--)
        invfact[i] = (invfact[i + 1] * 1ll * (i + 1)) % mod;
    return;
}

ll nchoosek(ll r, ll s) {
    if(s < 0 || s > r)
        return 0;
    return ((fact[r] * invfact[s]) % mod * invfact[r - s]) % mod;
}

int main()
{

    ll n;
    scanf("%lld",&n);
    init(n);
    return 0;

}
