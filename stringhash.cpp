#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define inf INT_MAX
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int) (x).size())
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

//double hashing with fixed mods and random bases

const int N = 1e5+3;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l, int r) { return uniform_int_distribution(l, r)(rng); }

int B[2];
const int M[2] = {1000000007, 998244353};
int pot[2][N];

struct StringHash {
    vi ht[2];
    int n_;

    StringHash(char *s, int nn_) { //string s, s.size()
        ht[0].resize(nn_); ht[1].resize(nn_); n_ = nn_;

        for(int i = 0; i < 2; i++) {
            ht[i][0] = s[0];
            for(int j = 1; j < n_; j++) {
                ht[i][j] = int((1ll * B[i] * 1ll * ht[i][j - 1]) % M[i]) + s[j];
                if(ht[i][j] >= M[i]) ht[i][j] -= M[i];
            }
        }
    }
    array <int, 2> range_hash(int l, int r) {
        if(l > r || l < 0 || r >= n_) {
            printf("tried to access %d %d\n", l, r);
            assert(false);
        }
        array <int, 2> ret = {ht[0][r], ht[1][r]};
        if(l) for(int i = 0; i < 2; i++) {
            ret[i] -= int((1ll * ht[i][l - 1] * 1ll * pot[i][r - l + 1]) % M[i]);
            if(ret[i] < 0) ret[i] += M[i];
        }
        return ret;
    }

};

void get_powers(int n_) {
    //bases should be biffer than coefs
    B[0] = rnd('z' + 1, M[0] - 1);
    B[1] = rnd('z' + 1, M[1] - 1);
    for(int i = 0; i < 2; i++) {
        pot[i][0] = 1;
        for(int j = 1; j < n_; j++) {
            pot[i][j] = int((1ll * pot[i][j - 1] * 1ll * B[i]) % M[i]);
        }
    }
}

char s[N], t[N];
int n, m;

int main() {
    scanf("%s", s);
    scanf("%s", t);
    printf("[%s][%s]\n", s, t);
    n = strlen(s);
    m = strlen(t);
    get_powers(max(n, m));

    StringHash H1(s, n), H2(t, m);

    if(H1.range_hash(0, n - 1) == H2.range_hash(0, m - 1))
        printf("lul\n");

    return 0;
}
