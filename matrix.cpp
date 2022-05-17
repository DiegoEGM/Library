//most often T = mint
//(see modint.cpp)
template <class T>
struct matrix {
    int r, c;
    vector<vector<T>> m;

    matrix(int r_, int c_) : r(r_), c(c_) {
        m = vector<vector<T>> (r, vector<T>(c));
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
    matrix res = identity <T> (a.r);
    while(p) {
        if(p % 2 == 1)
            res = res * a;
        a = a * a;
        p /= 2;
    }
    return res;
}

/*
let R be the matrix in row echelon form similar to a.
then this returns a matrix P such that Pa = R.
if a is invertible then R = I and P = a^{-1}.
needs more testing.
to-do: google what this matrix is called when its not inverse lol
*/
template <class T>
matrix <T> reduce(matrix <T> &a) {
    matrix <T> res = identity <T> (a.r);
    int pt = 0;
    for(int j = 0; j < a.c; j++) {
        int pivot = -1;
        for(int i = pt; i < a.r; i++) {
            if(a.m[i][j] != T(0)) {
                pivot = i;
                break;
            }
        }
        if(pivot == -1) continue;
        swap(a.m[pt], a.m[pivot]);
        swap(res.m[pt], res.m[pivot]);
        T inv = T(1) / a.m[pt][j];
        for(int k = 0; k < a.c; k++) {
            a.m[pt][k] *= inv;
            res.m[pt][k] *= inv;
        }
        for(int i = 0; i < a.r; i++) {
            if(i != pt && a.m[i][j] != T(0)) {
                T c = a.m[i][j];
                for(int k = 0; k < a.c; k++) {
                    a.m[i][k] -= c * a.m[pt][k];
                    res.m[i][k] -= c * res.m[pt][k];
                }
            }
        }
        pt++;
    }
    return res;
}

