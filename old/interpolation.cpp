#include <bits/stdc++.h>
#define f first
#define s second
#define pb emplace_back
#define inf INT_MAX
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int) (x).size())
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
const int mod = 1e9+7;

int add(int x, int y) {
    x += y;
    if(x >= mod) x -= mod;
    return x;
}

int dec(int x, int y) {
    x -= y;
    if(x < 0) x += mod;
    return x;
}

int mul(int x, int y) {
    ll re = 1ll * x * 1ll * y;
    if(re >= mod) re %= mod;
    return (int) re;
}

int binexp(int b, int e) {
    int x = 1, y = b;
    while(e) {
        if(e & 1)
            x = mul(x, y);
        y = mul(y, y);
        e /= 2;
    }
    return x;
}

//sz(sample) = n = degree + 1
int interpolate(vi &sample, int x, int n) {
    x %= mod;
    vi invfact(n);

    int fac = 1;
    for(int i = 2; i <= n - 1; i++) fac = mul(fac, i);

    invfact[n - 1] = binexp(fac, mod - 2);
    for(int i = n - 2; i >= 0; i--) {
        invfact[i] = mul(invfact[i + 1], i + 1);
    }

    vi pref(n), suf(n);
    pref[0] = 1;
    for(int i = 2; i <= n; i++) {
        pref[i - 1] = mul(pref[i - 2], dec(x, i - 1));
    }
    suf[n - 1] = 1;
    for(int i = n - 2; i >= 0; i--)
        suf[i] = mul(suf[i + 1], dec(x, i + 2));
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int term = mul(invfact[i - 1], invfact[n - i]);
        if((n - i) % 2 == 1)
            term = mod - term;
        term = mul(term, pref[i - 1]);
        term = mul(term, suf[i - 1]);
        term = mul(term, sample[i - 1]);
        ans = add(ans, term);
    }
    return ans;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int sum = 0;
    vi arr;
    for(int i = 1; i <= k + 2; i++) {
        sum = add(sum, binexp(i, k));
        arr.pb(sum);
    }
    printf("%d\n", interpolate(arr, n, k + 2));
    return 0;
}
//https://codeforces.com/contest/622/problem/F
