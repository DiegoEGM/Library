vi z_func(string &s) {
    int n = sz(s);
    int l = 0, r = 0;
    vi z(n);
    for(int i = 1; i < n; i++) {
        if(i <= r)
            z[i] = min(z[i - l], r - i + 1);
        while(i + z[i] < n && s[i + z[i]] == s[z[i]])
            z[i]++;
        if(i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}
