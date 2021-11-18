#include <bits/stdc++.h>
#define ft first
#define sd second
#define pb push_back
using namespace std;

using ll = long long;

const int MX = 101; //idk
const int MOD = 1e9 + 7;

int add(int x, int y) {
    return x + y >= MOD ? x + y - MOD : x + y;
}

int mul(int x, int y) {
    ll prod = (ll)x * (ll)y;
    return prod >= MOD ? prod % MOD : prod;
}

int dec(int x, int y) {
    return x < y ? MOD - y + x : x - y;
}

struct matrix {
    int m[MX][MX];
    int r, c;

    matrix() {
        memset(m, 0, sizeof m);
        r = c = 0;
    }
    matrix(int r_, int c_) {
        r = r_; c = c_;
        memset(m, 0, sizeof m);
    }

    matrix operator * (const matrix &b) {
        //N = #filas de A = #columnas e B
        assert(c == b.r);
        matrix prd = matrix(r, b.c);
        for(int i = 0; i < r; i++)
            for(int j = 0; j < b.c; j++)
                for(int k = 0; k < c; k++) {
                    prd.m[i][j] = add(prd.m[i][j] , mul(m[i][k], b.m[k][j]));
                }
        return prd;
    }

     matrix operator + (const matrix &b) {
        assert(b.c == c && b.r == r);
        matrix res(r, c);
        for(int i = 0; i < r; i++)
            for(int j = 0; j < c; j++)
                res.m[i][j] = add(m[i][j], b.m[i][j]);
        return res;
    }

    matrix operator - (const matrix &b) {
        assert(b.c == c && b.r == r);
        matrix res(r, c);
        for(int i = 0; i < r; i++)
            for(int j = 0; j < c; j++)
                res.m[i][j] = dec(m[i][j], b.m[i][j]);
        return res;
    }
};

matrix binexp(matrix a, int p) {
    assert(a.r == a.c && p >= 0);

    matrix ret = matrix(a.r, a.c);
    for(int i = 0; i < a.r; i++)
        ret.m[i][i] = 1;

    while(p) {
        if(p % 2 == 1)
            ret = (ret * a);
        a = (a * a);
        p /= 2;
    }
    return ret;
}

int main() {
    matrix M(2, 2);
    M.m[0][1] = M.m[1][0] = M.m[1][1] = 1;
    M = binexp(M, 9);
    printf("%d\n", M.m[1][0] + M.m[1][1]); //89: above is fibonacci
}
//https://github.com/bqi343/USACO/blob/master/Implementations/content/numerical/Matrix%20(11.3)/Matrix.h <- benq stuff
//https://codeforces.com/blog/entry/67776 cf tuto
//https://codeforces.com/blog/entry/21189 another cf tuto
