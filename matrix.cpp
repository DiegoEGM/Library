//most often T = mint
//(see modint.cpp)
template <class T>
struct matrix {
    vector<vector<T>> m;
    int r, c;

    matrix(int r_, int c_) : r(r_), c(c_) {
        r = r_; c = c_;
        m = vector<vector<T>> (r, vector<T>(c, T(0)));
    }

    matrix operator * (const matrix &b) {
        assert(c == b.r);
        matrix prod = matrix(r, b.c);
        for(int i = 0; i < r; i++)
            for(int j = 0; j < b.c; j++)
                for(int k = 0; k < c; k++)
                    prod.m[i][j] = prod.m[i][j] + m[i][k] * b.m[k][j];
        return prod;
    }

     matrix operator + (const matrix &b) {
        assert(b.c == c && b.r == r);
        matrix res(r, c);
        for(int i = 0; i < r; i++)
            for(int j = 0; j < c; j++)
                res.m[i][j] = m[i][j] + b.m[i][j];
        return res;
    }

    matrix operator - (const matrix &b) {
        assert(b.c == c && b.r == r);
        matrix res(r, c);
        for(int i = 0; i < r; i++)
            for(int j = 0; j < c; j++)
                res.m[i][j] = m[i][j] - b.m[i][j];
        return res;
    }
};

template <class T>
matrix <T> identity(int n) {
    matrix <T> id(n, n);
    for(int i = 0; i < n; i++) id.m[i][i] = T(1);
    return id;
}

template <class T>
matrix <T> binexp(matrix <T> a, ll p) {
    assert(a.r == a.c && p >= 0);
    matrix ret = identity <T> (a.r);
    while(p) {
        if(p % 2 == 1)
            ret = ret * a;
        a = a * a;
        p /= 2;
    }
    return ret;
}
