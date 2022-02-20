using db = double; //long double
const db PI = acos(-1.0);
using C = complex<db>;

C complex_mult(C &x, C &y) {
    return C(x.real() * y.real() - x.imag() * y.imag(), x.real() * y.imag() + x.imag() * y.real());
}

void fft(vector <C> &a, bool inv = false) {
    int n = a.size();
    int L = 31 - __builtin_clz(n);

    vector <C> roots(n);
    for(int i = 0; i < n / 2; i++) {
        roots[i + n / 2] = polar(db(1.0),  (inv ? -1.0 : 1.0) * 2.0 * PI * db(i) / db(n));
    }
    for(int i = n / 2 - 1; i >= 1; i--) {
        roots[i] = roots[2 * i];
    }

    vi rev(n);
    for(int i = 0; i < n; i++) {
        rev[i] = rev[i / 2] / 2 + ((i & 1) << (L - 1));
    }
    for(int i = 0; i < n; i++)
        if(i < rev[i])
            swap(a[i], a[rev[i]]);

    for(int len = 1; len < n; len *= 2) {
        for(int i = 0; i < n; i += 2 * len) {
            for(int j = 0; j < len; j++) {
                C z = complex_mult(a[i + j + len], roots[len + j]);
                a[i + j + len] = a[i + j] - z;
                a[i + j] += z;
            }
        }
    }

    if(inv)
        for(int i = 0; i < n; i++)
            a[i] /= db(n);
}

vector <C> conv(vector<C> a, vector <C> b) {
    int N = 1 << (32 - __builtin_clz(sz(a) + sz(b) - 1));
    while(a.size() < N) a.pb(0);
    while(b.size() < N) b.pb(0);
    fft(a);
    fft(b);
    vector <C> c(N);
    for(int i = 0; i < N; i++)
        c[i] = a[i] * b[i];
    fft(c, true);
    return c;
}

//helper function to multiply stuff with int coefs
vi mult(vi &A, vi &B) {
    int n = A.size(), m = B.size();
    vector <C> a(n), b(m), c;
    for(int i = 0; i < n; i++)
        a[i] = A[i];
    for(int i = 0; i < m; i++)
        b[i] = B[i];
    c = conv(a, b);
    vi C(c.size());
    for(int i = 0; i < c.size(); i++) {
        C[i] = int(round(real(c[i])));
    }
    while(C.size() > 1 && C.back() == 0)
        C.pop_back();
    return C;
}

